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

#ifndef RAPIDMP_PARSER_HPP
#define RAPIDMP_PARSER_HPP

#include <cstdint>
#include <boost/foreach.hpp>
#include <boost/spirit/include/qi.hpp>

#include <rapidmp/config.hpp> 
#include <rapidmp/type.hpp>
#include <rapidmp/exceptions.hpp>
#include <rapidmp/convert_endian.hpp>

namespace rapidmp {
  template< typename Version, typename Iterator >
  UMP_FUNCTION typename object_type< Iterator >::type parse_object(
    Iterator &iter, const Iterator &end,
    typename boost::enable_if<
      boost::mpl::or_<
        boost::mpl::equal_to< Version, version_1_0 >,
        boost::mpl::equal_to< Version, version_1_0_raw_as_string >
      >
     >::type* = 0
   );
  template< typename Version, typename Iterator >
  UMP_FUNCTION typename object_type< Iterator >::type parse_object(
    Iterator &iter, const Iterator &end,
    typename boost::enable_if<
      boost::mpl::equal_to< Version, version_1_0_raw_as_binary >
     >::type* = 0
   );
  template< typename Version, typename Iterator >
  UMP_FUNCTION typename object_type< Iterator >::type parse_object(
    Iterator &iter, const Iterator &end,
    typename boost::enable_if<
      boost::mpl::equal_to< boost::mpl::bitand_< Version, version_mask >, version_1_1 >
     >::type* = 0
   );

  template< typename Version, typename Iterator >
  UMP_FUNCTION typename struct_type< Iterator >::type parse_short_struct( uint8_t head, Iterator &iter, const Iterator &end ) {
    const size_t size = head & 0xf;
    typename struct_type< Iterator >::type result;
    result.reserve( size );
    for( size_t index = 0u; index != size; ++index ) {
      if( iter == end )
        throw unexpected_end();
      typename object_type< Iterator >::type &&key( std::move( parse_object< Version >( iter, end ) ) );
      if( iter == end )
        throw unexpected_end();
      result.emplace_back( key, std::move( parse_object< Version >( iter, end ) ) );
    }
    return std::move( result );
  }

  template< typename Version, typename Iterator >
  UMP_FUNCTION typename array_type< Iterator >::type parse_short_array( uint8_t head, Iterator &iter, const Iterator &end ) {
    const size_t size = head & 0xf;
    typename array_type< Iterator >::type result;
    result.reserve( size );
    for( size_t index = 0u; index != size; ++index ) {
      if( iter == end )
        throw unexpected_end();
      result.emplace_back(
        std::move( parse_object< Version >( iter, end ) )
      );
    }
    return std::move( result );
  }
  
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

  template< typename Version, typename Length, typename Iterator >
  UMP_FUNCTION typename array_type< Iterator >::type parse_array( Iterator &iter, const Iterator &end ) {
    const size_t size = convert_endian< Length >( iter, end );
    typename array_type< Iterator >::type result;
    result.reserve( size );
    for( size_t index = 0; index != size; ++index ) {
      if( iter == end )
        throw unexpected_end();
      result.emplace_back(
        std::move( parse_object< Version >( iter, end ) )
      );
    }
    return std::move( result );
  }

  template< typename Version, typename Length, typename Iterator >
  UMP_FUNCTION typename struct_type< Iterator >::type parse_struct( Iterator &iter, const Iterator &end ) {
    const size_t size = convert_endian< Length >( iter, end );
    typename struct_type< Iterator >::type result;
    result.reserve( size );
    for( size_t index = 0u; index != size; ++index ) {
      if( iter == end )
        throw unexpected_end();
      typename object_type< Iterator >::type &&key( std::move( parse_object< Version >( iter, end ) ) );
      if( iter == end )
        throw unexpected_end();
      result.emplace_back( key, std::move( parse_object< Version >( iter, end ) ) );
    }
    return std::move( result );
  }
  
  template< typename Version, typename Iterator >
  UMP_FUNCTION typename object_type< Iterator >::type parse_object(
    Iterator &iter, const Iterator &end,
    typename boost::enable_if<
      boost::mpl::or_<
        boost::mpl::equal_to< Version, version_1_0 >,
        boost::mpl::equal_to< Version, version_1_0_raw_as_string >
      >
     >::type* = 0
   ) {
    if( iter == end )
      throw unexpected_end();
    const uint8_t head = *iter;
    ++iter;
    if( head < 0x80u ) {
      return static_cast< uint64_t >( head );
    }
    else if( head < 0xc0u ) {
      if( head < 0x90u )
        return std::move( parse_short_struct< Version >( head, iter, end ) );
      else if( head < 0xa0u )
        return std::move( parse_short_array< Version >( head, iter, end ) );
      else
        return std::move( parse_short_string( head, iter, end ) );
    }
    else if( head < 0xe0u ) {
      switch( head ) {
        case 0xc0u:
          return none;
        case 0xc2u:
          return false;
        case 0xc3u:
          return true;
        case 0xcau:
          return parse_float32< Iterator >( iter, end );
        case 0xcbu:
          return parse_float64< Iterator >( iter, end );
        case 0xccu:
          return parse_uint< boost::mpl::size_t< 1 >, Iterator >( iter, end );
        case 0xcdu:
          return parse_uint< boost::mpl::size_t< 2 >, Iterator >( iter, end );
        case 0xceu:
          return parse_uint< boost::mpl::size_t< 4 >, Iterator >( iter, end );
        case 0xcfu:
          return parse_uint< boost::mpl::size_t< 8 >, Iterator >( iter, end );
        case 0xd0u:
          return parse_int< boost::mpl::size_t< 1 >, Iterator >( iter, end );
        case 0xd1u:
          return parse_int< boost::mpl::size_t< 2 >, Iterator >( iter, end );
        case 0xd2u:
          return parse_int< boost::mpl::size_t< 4 >, Iterator >( iter, end );
        case 0xd3u:
          return parse_int< boost::mpl::size_t< 8 >, Iterator >( iter, end );
        case 0xdau:
          return std::move( parse_str< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xdbu:
          return std::move( parse_str< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xdcu:
          return std::move( parse_array< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xddu:
          return std::move( parse_array< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xdeu:
          return std::move( parse_struct< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xdfu:
          return std::move( parse_struct< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        default:
          throw invalid_object();
      };
    }
    else {
      return -static_cast< int64_t >( 0x100u - static_cast< uint32_t >( head ) );
    }
    throw invalid_object();
  }

  template< typename Version, typename Iterator >
  UMP_FUNCTION typename object_type< Iterator >::type parse_object(
    Iterator &iter, const Iterator &end,
    typename boost::enable_if<
      boost::mpl::equal_to< Version, version_1_0_raw_as_binary >
     >::type* = 0
   ) {
    if( iter == end )
      throw unexpected_end();
    const uint8_t head = *iter;
    ++iter;
    if( head < 0x80u ) {
      return static_cast< uint64_t >( head );
    }
    else if( head < 0xc0u ) {
      if( head < 0x90u )
        return std::move( parse_short_struct< Version >( head, iter, end ) );
      else if( head < 0xa0u )
        return std::move( parse_short_array< Version >( head, iter, end ) );
      else
        return std::move( parse_short_bin( head, iter, end ) );
    }
    else if( head < 0xe0u ) {
      switch( head ) {
        case 0xc0u:
          return none;
        case 0xc2u:
          return false;
        case 0xc3u:
          return true;
        case 0xcau:
          return parse_float32< Iterator >( iter, end );
        case 0xcbu:
          return parse_float64< Iterator >( iter, end );
        case 0xccu:
          return parse_uint< boost::mpl::size_t< 1 >, Iterator >( iter, end );
        case 0xcdu:
          return parse_uint< boost::mpl::size_t< 2 >, Iterator >( iter, end );
        case 0xceu:
          return parse_uint< boost::mpl::size_t< 4 >, Iterator >( iter, end );
        case 0xcfu:
          return parse_uint< boost::mpl::size_t< 8 >, Iterator >( iter, end );
        case 0xd0u:
          return parse_int< boost::mpl::size_t< 1 >, Iterator >( iter, end );
        case 0xd1u:
          return parse_int< boost::mpl::size_t< 2 >, Iterator >( iter, end );
        case 0xd2u:
          return parse_int< boost::mpl::size_t< 4 >, Iterator >( iter, end );
        case 0xd3u:
          return parse_int< boost::mpl::size_t< 8 >, Iterator >( iter, end );
        case 0xdau:
          return std::move( parse_bin< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xdbu:
          return std::move( parse_bin< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xdcu:
          return std::move( parse_array< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xddu:
          return std::move( parse_array< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xdeu:
          return std::move( parse_struct< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xdfu:
          return std::move( parse_struct< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        default:
          throw invalid_object();
      };
    }
    else {
      return -static_cast< int64_t >( 0x100u - static_cast< uint32_t >( head ) );
    }
    throw invalid_object();
  }

  template< typename Version, typename Iterator >
  UMP_FUNCTION typename object_type< Iterator >::type parse_object(
    Iterator &iter, const Iterator &end,
    typename boost::enable_if<
      boost::mpl::equal_to< boost::mpl::bitand_< Version, version_mask >, version_1_1 >
     >::type* = 0
   ) {
    if( iter == end )
      throw unexpected_end();
    const uint8_t head = *iter;
    ++iter;
    if( head < 0x80u ) {
      return static_cast< uint64_t >( head );
    }
    else if( head < 0xc0u ) {
      if( head < 0x90u )
        return std::move( parse_short_struct< Version >( head, iter, end ) );
      else if( head < 0xa0u )
        return std::move( parse_short_array< Version >( head, iter, end ) );
      else
        return std::move( parse_short_string( head, iter, end ) );
    }
    else if( head < 0xe0u ) {
      switch( head ) {
        case 0xc0u:
          return none;
        case 0xc2u:
          return false;
        case 0xc3u:
          return true;
        case 0xc4u:
          return std::move( parse_bin< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
        case 0xc5u:
          return std::move( parse_bin< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xc6u:
          return std::move( parse_bin< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xc7u:
          return std::move( parse_ext< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
        case 0xc8u:
          return std::move( parse_ext< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xc9u:
          return std::move( parse_ext< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xcau:
          return parse_float32< Iterator >( iter, end );
        case 0xcbu:
          return parse_float64< Iterator >( iter, end );
        case 0xccu:
          return parse_uint< boost::mpl::size_t< 1 >, Iterator >( iter, end );
        case 0xcdu:
          return parse_uint< boost::mpl::size_t< 2 >, Iterator >( iter, end );
        case 0xceu:
          return parse_uint< boost::mpl::size_t< 4 >, Iterator >( iter, end );
        case 0xcfu:
          return parse_uint< boost::mpl::size_t< 8 >, Iterator >( iter, end );
        case 0xd0u:
          return parse_int< boost::mpl::size_t< 1 >, Iterator >( iter, end );
        case 0xd1u:
          return parse_int< boost::mpl::size_t< 2 >, Iterator >( iter, end );
        case 0xd2u:
          return parse_int< boost::mpl::size_t< 4 >, Iterator >( iter, end );
        case 0xd3u:
          return parse_int< boost::mpl::size_t< 8 >, Iterator >( iter, end );
        case 0xd4u:
          return parse_fixext< boost::mpl::size_t< 1 >, Iterator >( iter, end );
        case 0xd5u:
          return parse_fixext< boost::mpl::size_t< 2 >, Iterator >( iter, end );
        case 0xd6u:
          return parse_fixext< boost::mpl::size_t< 4 >, Iterator >( iter, end );
        case 0xd7u:
          return parse_fixext< boost::mpl::size_t< 8 >, Iterator >( iter, end );
        case 0xd8u:
          return parse_fixext< boost::mpl::size_t< 16 >, Iterator >( iter, end );
        case 0xd9u:
          return std::move( parse_str< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
        case 0xdau:
          return std::move( parse_str< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xdbu:
          return std::move( parse_str< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xdcu:
          return std::move( parse_array< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xddu:
          return std::move( parse_array< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xdeu:
          return std::move( parse_struct< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xdfu:
          return std::move( parse_struct< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        default:
          throw invalid_object();
      };
    }
    else {
      return -static_cast< int64_t >( 0x100u - static_cast< uint32_t >( head ) );
    }
    throw invalid_object();
  }
}

#endif

