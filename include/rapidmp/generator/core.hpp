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

#ifndef RAPIDMP_GENERATOR_CORE_HPP
#define RAPIDMP_GENERATOR_CORE_HPP

#include <cstdint>
#include <algorithm>
#include <boost/foreach.hpp>
#include <boost/variant.hpp>
#include <boost/variant/recursive_variant.hpp>
#include <boost/spirit/include/karma.hpp>

#include <rapidmp/config.hpp>
#include <rapidmp/type.hpp>
#include <rapidmp/exceptions.hpp>

namespace rapidmp {
  template< typename Length >
  UMP_FUNCTION decltype( boost::spirit::karma::byte_ )
  get_karma_rule_for_the_integer(
    typename boost::enable_if< boost::mpl::equal_to< Length, boost::mpl::size_t< 1 > > >::type* = 0
  ) {
    return boost::spirit::karma::byte_;
  }

  template< typename Length >
  UMP_FUNCTION decltype( boost::spirit::karma::big_word )
  get_karma_rule_for_the_integer(
    typename boost::enable_if< boost::mpl::equal_to< Length, boost::mpl::size_t< 2 > > >::type* = 0
  ) {
    return boost::spirit::karma::big_word;
  }

  template< typename Length >
  UMP_FUNCTION decltype( boost::spirit::karma::big_dword )
  get_karma_rule_for_the_integer(
    typename boost::enable_if< boost::mpl::equal_to< Length, boost::mpl::size_t< 4 > > >::type* = 0
  ) {
    return boost::spirit::karma::big_dword;
  }
  
  template< typename Length >
  UMP_FUNCTION decltype( boost::spirit::karma::big_qword )
  get_karma_rule_for_the_integer(
    typename boost::enable_if< boost::mpl::equal_to< Length, boost::mpl::size_t< 8 > > >::type* = 0
  ) {
    return boost::spirit::karma::big_qword;
  }

  template< typename Length, typename Iterator >
  UMP_FUNCTION void generate_uint_in_the_length(
    Iterator &output, uint64_t value
  ) {
    namespace karma = boost::spirit::karma;
    if( !karma::generate( output, get_karma_rule_for_the_integer< Length >(), value ) )
      throw overflow();
  }

  template< typename Iterator >
  UMP_FUNCTION void generate_uint( Iterator &output, uint64_t value ) {
    if( value < 0x80ull ) {
      *output = value;
      ++output;
    }
    else if( value < 0x100ull ) {
      *output = '\xcc';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 1 > >( output, value );
    }
    else if( value < 0x10000ull ) {
      *output = '\xcd' ;
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 2 > >( output, value );
    }
    else if( value < 0x100000000ull ) {
      *output = '\xce';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 4 > >( output, value );
    }
    else {
      *output = '\xcf';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 8 > >( output, value );
    }
  }

  template< typename Length, typename Iterator >
  UMP_FUNCTION void generate_int_in_the_length(
    Iterator &output, int64_t value
  ) {
    namespace karma = boost::spirit::karma;
    if( !karma::generate( output, get_karma_rule_for_the_integer< Length >(), static_cast< typename boost::uint_t< Length::value * 8 >::exact >( value ) ) )
      throw overflow();
  }
  template< typename Iterator >
  UMP_FUNCTION void generate_int( Iterator &output, int64_t value ) {
    if( value <= -0x100000000ll || value >= 0x100000000ll ) {
      *output = '\xd3';
      ++output;
      generate_int_in_the_length< boost::mpl::size_t< 8 > >( output, value );
    }
    else if( value <= -0x10000ll || value >= 0x10000ll ) {
      *output = '\xd2';
      ++output;
      generate_int_in_the_length< boost::mpl::size_t< 4 > >( output, value );
    }
    else if( value <= -0x100ll || value >= 0x100ll ) {
      *output = '\xd1';
      ++output;
      generate_int_in_the_length< boost::mpl::size_t< 2 > >( output, value );
    }
    else if( value >= 0  || value < -32 ) {
      *output = '\xd0';
      ++output;
      generate_int_in_the_length< boost::mpl::size_t< 1 > >( output, value );
    }
    else {
      *output = value;
      ++output;
    }
  }

  template< typename Version, typename InputIterator, typename OutputIterator >
  UMP_FUNCTION void generate_str(
    OutputIterator &output, const string< InputIterator > &value,
    typename boost::enable_if< boost::mpl::equal_to< boost::mpl::bitand_< Version, version_mask >, version_1_0 > >::type* = 0
  ) {
    const size_t length = boost::distance( value.range );
    if( length < 32u ) {
      *output = '\xa0' + length;
      ++output;
    }
    else if( length < 0x10000u ) {
      *output = '\xda';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 2 > >( output, length );
    }
    else if( length < 0x100000000u ) {
      *output = '\xdb';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 4 > >( output, length );
    }
    else throw too_big();
    std::copy( boost::begin( value.range ), boost::end( value.range ), output );
  }

  template< typename Version, typename InputIterator, typename OutputIterator >
  UMP_FUNCTION void generate_str(
    OutputIterator &output, const string< InputIterator > &value,
    typename boost::enable_if< boost::mpl::equal_to< boost::mpl::bitand_< Version, version_mask >, version_1_1 > >::type* = 0
  ) {
    const size_t length = boost::distance( value.range );
    if( length < 32u ) {
      *output = '\xa0' + length;
      ++output;
    }
    else if( length < 0x100u ) {
      *output = '\xd9';
      ++output;
      generate_int_in_the_length< boost::mpl::size_t< 1 > >( output, length );
    }
    else if( length < 0x10000u ) {
      *output = '\xda';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 2 > >( output, length );
    }
    else if( length < 0x100000000u ) {
      *output = '\xdb';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 4 > >( output, length );
    }
    else throw too_big();
    std::copy( boost::begin( value.range ), boost::end( value.range ), output );
  }


  template< typename InputIterator, typename OutputIterator >
  UMP_FUNCTION void generate_bin( OutputIterator &output, const binary< InputIterator > &value ) {
    const size_t length = boost::distance( value.range );
    if( length < 0x100u ) {
      *output = '\xc4';
      ++output;
      generate_int_in_the_length< boost::mpl::size_t< 1 > >( output, length );
    }
    else if( length < 0x10000u ) {
      *output = '\xc5';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 2 > >( output, length );
    }
    else if( length < 0x100000000u ) {
      *output = '\xc6';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 4 > >( output, length );
    }
    else throw too_big();
    std::copy( boost::begin( value.range ), boost::end( value.range ), output );
  }

  template< typename InputIterator, typename OutputIterator >
  UMP_FUNCTION void generate_ext( OutputIterator &output, const extension< InputIterator > &value ) {
    const size_t length = boost::distance( value.range );
    if( length == 1 ) {
      *output = '\xd4';
      ++output;
    }
    else if( length == 2 ) {
      *output = '\xd5';
      ++output;
    }
    else if( length == 4 ) {
      *output = '\xd6';
      ++output;
    }
    else if( length == 8 ) {
      *output = '\xd7';
      ++output;
    }
    else if( length == 16 ) {
      *output = '\xd8';
      ++output;
    }
    else if( length < 0x100u ) {
      *output = '\xc7';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 1 > >( output, length );
    }
    else if( length < 0x10000u ) {
      *output = '\xc8';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 2 > >( output, length );
    }
    else if( length < 0x100000000u ) {
      *output = '\xc9';
      ++output;
      generate_uint_in_the_length< boost::mpl::size_t< 4 > >( output, length );
    }
    else throw too_big();
    generate_uint_in_the_length< boost::mpl::size_t< 1 > >( output, value.type );
    std::copy( boost::begin( value.range ), boost::end( value.range ), output );
  }

  template< typename OutputIterator >
  UMP_FUNCTION void generate_float( OutputIterator &output, float value ) {
    *output = '\xca';
    ++output;
    namespace karma = boost::spirit::karma;
    if( !karma::generate( output, karma::big_bin_float, value ) )
      throw invalid_float();
  }

  template< typename OutputIterator >
  UMP_FUNCTION void generate_float( OutputIterator &output, double value ) {
    *output = '\xcb';
    ++output;
    namespace karma = boost::spirit::karma;
    if( !karma::generate( output, karma::big_bin_double, value ) )
      throw invalid_float();
  }

  template< typename OutputIterator >
  UMP_FUNCTION void generate_none( OutputIterator &output ) {
    *output = '\xc0';
    ++output;
  }

  template< typename OutputIterator >
  UMP_FUNCTION void generate_bool( OutputIterator &output, bool value ) {
    *output = value ? '\xc3' : '\xc2';
    ++output;
  }
}

#endif

