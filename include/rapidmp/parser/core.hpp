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

#ifndef RAPIDMP_PARSER_CORE_HPP
#define RAPIDMP_PARSER_CORE_HPP

#include <cstdint>
#include <boost/foreach.hpp>
#include <boost/spirit/include/qi.hpp>

#include <rapidmp/config.hpp> 
#include <rapidmp/type.hpp>
#include <rapidmp/exceptions.hpp>
#include <rapidmp/convert_endian.hpp>

namespace rapidmp {
  template< typename Iterator >
  UMP_FUNCTION string< Iterator > parse_short_string( uint8_t head, Iterator &iter, const Iterator &end ) {
    const size_t size = head & 0x1f;
    const auto strbegin = iter;
    if( size_t( std::distance( iter, end ) ) < size )
      throw unexpected_end();
    const auto strend = std::next( iter, size );
    iter = strend;
    return string< Iterator >( strbegin, strend );
  }

  template< typename Iterator >
  UMP_FUNCTION string< Iterator > parse_short_bin( uint8_t head, Iterator &iter, const Iterator &end ) {
    const size_t size = head & 0x1f;
    const auto strbegin = iter;
    if( size_t( std::distance( iter, end ) ) < size )
      throw unexpected_end();
    const auto strend = std::next( iter, size );
    iter = strend;
    return binary< Iterator >( strbegin, strend );
  }

  template< typename Length, typename Iterator >
  UMP_FUNCTION binary< Iterator > parse_bin( Iterator &iter, const Iterator &end ) {
    const size_t size = convert_endian< Length >( iter, end );
    const auto strbegin = iter;
    if( size_t( std::distance( iter, end ) ) < size )
      throw unexpected_end();
    const auto strend = std::next( iter, size );
    iter = strend;
    return binary< Iterator >( strbegin, strend );
  }

  template< typename Length, typename Iterator >
  UMP_FUNCTION extension< Iterator > parse_ext( Iterator &iter, const Iterator &end ) {
    const size_t size = convert_endian< Length >( iter, end );
    if( size_t( std::distance( iter, end ) ) < size + 1ull )
      throw unexpected_end();
    const size_t type = *iter;
    ++iter;
    const auto strbegin = iter;
    const auto strend = std::next( iter, size );
    iter = strend;
    return extension< Iterator >( type, strbegin, strend );
  }

  template< typename Iterator >
  UMP_FUNCTION float parse_float32( Iterator &iter, const Iterator &end ) {
    if( std::distance( iter, end ) < 4 )
      throw unexpected_end();
    namespace qi = boost::spirit::qi;
    float result;
    static const auto rule = qi::big_bin_float;
    if( !qi::parse( iter, end, rule, result ) )
      throw invalid_float();
    return result;
  }

  template< typename Iterator >
  UMP_FUNCTION double parse_float64( Iterator &iter, const Iterator &end ) {
    namespace qi = boost::spirit::qi;
    double result;
    static const auto rule = qi::big_bin_double;
    if( !qi::parse( iter, end, rule, result ) )
      throw invalid_float();
    return result;
  }

  template< typename Length, typename Iterator >
  UMP_FUNCTION uint64_t parse_uint( Iterator &iter, const Iterator &end ) {
    return static_cast< uint64_t >( convert_endian< Length >( iter, end ) );
  }

  template< typename Length, typename Iterator >
  UMP_FUNCTION int64_t parse_int( Iterator &iter, const Iterator &end ) {
    const auto value = convert_endian< Length >( iter, end );
    typedef typename boost::uint_t<
      Length::value * 8u
    >::exact unsigned_type;
    typedef typename boost::int_t<
      Length::value * 8u
    >::exact result_type;
    const auto max = typename boost::uint_t< Length::value * 8u >::exact(
      boost::integer_traits< result_type >::const_max
    );
    const auto umax = typename boost::uint_t< Length::value * 8u >::exact(
      boost::integer_traits< unsigned_type >::const_max
    );
    return static_cast< int64_t >(
      ( value > max )? ( -result_type( umax - value ) - 1 ) : result_type( value ) );
  }
  template< typename Length, typename Iterator >
  UMP_FUNCTION extension< Iterator > parse_fixext( Iterator &iter, const Iterator &end ) {
    const uint64_t type = convert_endian< boost::mpl::size_t< 1 > >( iter, end );
    const auto strbegin = iter;
    if( size_t( std::distance( iter, end ) ) < size_t( Length::value ) )
      throw unexpected_end();
    const auto strend = std::next( iter, Length::value );
    iter = strend;
    return extension< Iterator >( type, strbegin, strend );
  }

  template< typename Length, typename Iterator >
  UMP_FUNCTION string< Iterator > parse_str( Iterator &iter, const Iterator &end ) {
    const size_t size = convert_endian< Length >( iter, end );
    const auto strbegin = iter;
    if( size_t( std::distance( iter, end ) ) < size )
      throw unexpected_end();
    const auto strend = std::next( iter, size );
    iter = strend;
    return string< Iterator >( strbegin, strend );
  }
}

#endif

