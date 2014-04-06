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

#ifndef RAPIDMP_GENERATOR_EVENT_HPP
#define RAPIDMP_GENERATOR_EVENT_HPP

#include <cstdint>
#include <algorithm>
#include <stack>
#include <boost/utility/enable_if.hpp>
#include <boost/type_traits.hpp>

#include <rapidmp/config.hpp>
#include <rapidmp/type.hpp>
#include <rapidmp/exceptions.hpp>
#include <rapidmp/generator/core.hpp>

namespace rapidmp {
  struct unexpected_event {};
  template< typename Version, typename OutputIterator >
  class generator {
  public:
    generator( OutputIterator &output_ ) : output( output_ ) {
      left.push( 1u );
    }
    template< typename T >
    UMP_FUNCTION void operator()(
      const T &value,
      typename boost::enable_if<
        boost::mpl::and_<
          boost::is_integral< T >,
          boost::is_unsigned< T >
        >
      >::type* = 0
    ) {
      pre_event();
      generate_uint( output, uint64_t( value ) );
      post_event();
    }
    template< typename T >
    UMP_FUNCTION void operator()(
      const T &value,
      typename boost::enable_if<
        boost::mpl::and_<
          boost::is_integral< T >,
          boost::mpl::not_< boost::is_unsigned< T > >
        >
      >::type* = 0
    ) {
      pre_event();
      generate_int( output, int64_t( value ) );
      post_event();
    }
    UMP_FUNCTION void operator()(
      float value
    ) {
      pre_event();
      generate_float( output, value );
      post_event();
    }
    UMP_FUNCTION void operator()(
      double value
    ) {
      pre_event();
      generate_float( output, value );
      post_event();
    }
    UMP_FUNCTION void operator()() {
      pre_event();
      generate_none( output );
      post_event();
    }
    UMP_FUNCTION void operator()(
      bool value
    ) {
      pre_event();
      generate_bool( output, value );
      post_event();
    }
    template< typename InputIterator >
    UMP_FUNCTION void operator()(
      const string< InputIterator > &value
    ) {
      pre_event();
      generate_str< Version >( output, value );
      post_event();
    }
 
    template< typename InputIterator, typename Version_ = Version >
    UMP_FUNCTION void operator()(
      const binary< InputIterator > &value,
      typename boost::enable_if< boost::mpl::equal_to< boost::mpl::bitand_< Version_, version_mask >, version_1_0 > >::type* = 0
    ) {
      pre_event();
      generate_str< Version >( output, string< InputIterator >( boost::begin( value.range ), boost::end( value.range ) ) );
      post_event();
    }
    template< typename InputIterator, typename Version_ = Version >
    UMP_FUNCTION void operator()(
      const binary< InputIterator > &value,
      typename boost::enable_if< boost::mpl::equal_to< boost::mpl::bitand_< Version_, version_mask >, version_1_1 > >::type* = 0
    ) {
      pre_event();
      generate_bin( output, value );
      post_event();
    }
 
    template< typename InputIterator, typename Version_ = Version >
    UMP_FUNCTION void operator()(
      const extension< InputIterator > &value,
      typename boost::enable_if< boost::mpl::equal_to< boost::mpl::bitand_< Version_, version_mask >, version_1_1 > >::type* = 0
    ) {
      pre_event();
      generate_ext( output, value );
      post_event();
    }

    UMP_FUNCTION void begin_array( size_t length ) {
      pre_event();
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
      left.push( length );
      post_event();
    }
    UMP_FUNCTION void end_array() {
    }
    UMP_FUNCTION void begin_struct( size_t length ) {
      pre_event();
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
      left.push( length * 2 );
      post_event();
    }
    UMP_FUNCTION void end_struct() {
    }
  private:
    void pre_event() {
      if( left.top() == 0u )
        throw unexpected_event();
    }
    void post_event() {
      --left.top();
      if( left.top() == 0 )
        if( left.size() > 1u )
          left.pop();
    }
    std::stack< size_t > left;
    OutputIterator &output;
  };

}

#endif

