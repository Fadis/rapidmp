/****************************************************************************
Copyright (c) 2014 Naomasa Matsubayashi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#ifndef RAPIDMP_GENERATOR_TREE_HPP
#define RAPIDMP_GENERATOR_TREE_HPP

#include <cstdint>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/variant.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/spirit/include/karma.hpp>

#include <rapidmp/config.hpp>
#include <rapidmp/type.hpp>
#include <rapidmp/exceptions.hpp>
#include <rapidmp/generator/core.hpp>

namespace rapidmp {
  template< typename InputIterator, typename OutputIterator >
  UMP_FUNCTION void generate_array( OutputIterator &output, const typename array_type< InputIterator >::type &value );

  template< typename InputIterator, typename OutputIterator >
  UMP_FUNCTION void generate_struct( OutputIterator &output, const typename struct_type< InputIterator >::type &value );

  template< typename Version, typename InputIterator, typename OutputIterator, typename Enable = void >
  class generate_object_visitor : public boost::static_visitor<void> {};

  template< typename Version, typename InputIterator, typename OutputIterator >
  class generate_object_visitor<
    Version, InputIterator, OutputIterator,
    typename boost::enable_if< boost::mpl::equal_to< boost::mpl::bitand_< Version, version_mask >, version_1_0 > >::type
   > : public boost::static_visitor<void> {
  public:
    UMP_FUNCTION generate_object_visitor( OutputIterator &output_ ) : output( output_ ) {}
    UMP_FUNCTION void operator()( uint64_t value ) {
      generate_uint( output, value );
    }
    UMP_FUNCTION void operator()( int64_t value ) {
      generate_int( output, value );
    }
    UMP_FUNCTION void operator()( float value ) {
      generate_float( output, value );
    }
    UMP_FUNCTION void operator()( double value ) {
      generate_float( output, value );
    }
    UMP_FUNCTION void operator()( const none_type & ) {
      generate_none( output );
    }
    UMP_FUNCTION void operator()( bool value ) {
      generate_bool( output, value );
    }
    UMP_FUNCTION void operator()( const string< InputIterator > &value ) {
      generate_str< Version >( output, value );
    }
    UMP_FUNCTION void operator()( const binary< InputIterator > &value ) {
      generate_str< Version >( output, string< InputIterator >( boost::begin( value.range ), boost::end( value.range ) ) );
    }
    UMP_FUNCTION void operator()( const extension< InputIterator > & ) {
      throw not_supported();
    }
    UMP_FUNCTION void operator()( const typename array_type< InputIterator >::type &value ) {
      generate_array< Version, InputIterator, OutputIterator >( output, value );
    }
    UMP_FUNCTION void operator()( const typename struct_type< InputIterator >::type &value ) {
      generate_struct< Version, InputIterator, OutputIterator >( output, value );
    }
  private:
    OutputIterator &output;
  };

  template< typename Version, typename InputIterator, typename OutputIterator >
  class generate_object_visitor<
    Version, InputIterator, OutputIterator,
    typename boost::enable_if< boost::mpl::equal_to< boost::mpl::bitand_< Version, version_mask >, version_1_1 > >::type
  > : public boost::static_visitor<void> {
  public:
    UMP_FUNCTION generate_object_visitor( OutputIterator &output_ ) : output( output_ ) {}
    UMP_FUNCTION void operator()( uint64_t value ) {
      generate_uint( output, value );
    }
    UMP_FUNCTION void operator()( int64_t value ) {
      generate_int( output, value );
    }
    UMP_FUNCTION void operator()( float value ) {
      generate_float( output, value );
    }
    UMP_FUNCTION void operator()( double value ) {
      generate_float( output, value );
    }
    UMP_FUNCTION void operator()( const none_type & ) {
      generate_none( output );
    }
    UMP_FUNCTION void operator()( bool value ) {
      generate_bool( output, value );
    }
    UMP_FUNCTION void operator()( const string< InputIterator > &value ) {
      generate_str< Version >( output, value );
    }
    UMP_FUNCTION void operator()( const binary< InputIterator > &value ) {
      generate_bin( output, value );
    }
    UMP_FUNCTION void operator()( const extension< InputIterator > &value ) {
      generate_ext( output, value );
    }
    UMP_FUNCTION void operator()( const typename array_type< InputIterator >::type &value ) {
      generate_array< Version, InputIterator, OutputIterator >( output, value );
    }
    UMP_FUNCTION void operator()( const typename struct_type< InputIterator >::type &value ) {
      generate_struct< Version, InputIterator, OutputIterator >( output, value );
    }
  private:
    OutputIterator &output;
  };

  template< typename ObjectType >
  struct get_input_iterator {
    typedef typename boost::mpl::at_c< typename ObjectType::types, 7 >::type::range_type::iterator type;
  };
  
  template< typename Version, typename ObjectType, typename OutputIterator >
  UMP_FUNCTION void generate_object( OutputIterator &output, const ObjectType &value ) {
    generate_object_visitor< Version, typename get_input_iterator< ObjectType >::type, OutputIterator > generator( output );
    apply_visitor( generator, value );
  }

  template< typename Version, typename InputIterator, typename OutputIterator >
  UMP_FUNCTION void generate_array( OutputIterator &output, const typename array_type< InputIterator >::type &value ) {
    const size_t length = boost::distance( value );
    if( length < 16u ) {
      *output = '\x90' + length;
      ++output;
    }
    else if( length < 0x10000u ) {
      *output = '\xdc';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 2 > >( output, length );
    }
    else if( length < 0x100000000u ) {
      *output = '\xdd';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 4 > >( output, length );
    }
    else throw too_big();
    generate_object_visitor< Version, InputIterator, OutputIterator > generator( output );
    BOOST_FOREACH( const auto &elem, value )
      apply_visitor( generator, elem );
  }

  template< typename Version, typename InputIterator, typename OutputIterator >
  UMP_FUNCTION void generate_struct( OutputIterator &output, const typename struct_type< InputIterator >::type &value ) {
    const size_t length = boost::distance( value );
    if( length < 16u ) {
      *output = '\x80' + length;
      ++output;
    }
    else if( length < 0x10000u ) {
      *output = '\xde';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 2 > >( output, length );
    }
    else if( length < 0x100000000u ) {
      *output = '\xdf';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 4 > >( output, length );
    }
    else throw too_big();
    generate_object_visitor< Version, InputIterator, OutputIterator > generator( output );
    BOOST_FOREACH( const auto &elem, value ) {
      apply_visitor( generator, elem.first );
      apply_visitor( generator, elem.second );
    }
  }
}

#endif

