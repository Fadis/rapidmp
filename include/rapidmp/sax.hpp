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

#ifndef RAPIDMP_SAX_HPP
#define RAPIDMP_SAX_HPP

#include <cstdint>
#include <boost/foreach.hpp>
#include <boost/spirit/include/qi.hpp>

#include <rapidmp/config.hpp> 
#include <rapidmp/type.hpp>
#include <rapidmp/exceptions.hpp>
#include <rapidmp/convert_endian.hpp>
#include <rapidmp/parser.hpp>

namespace rapidmp {
  template< typename Version, typename Iterator, typename Receiver >
  UMP_FUNCTION void parse_object(
    Iterator &iter, const Iterator &end, Receiver &receiver,
    typename boost::enable_if<
      boost::mpl::or_<
        boost::mpl::equal_to< Version, version_1_0 >,
        boost::mpl::equal_to< Version, version_1_0_raw_as_string >
      >
     >::type* = 0
   );

  template< typename Version, typename Iterator, typename Receiver >
  UMP_FUNCTION void parse_object(
    Iterator &iter, const Iterator &end, Receiver &receiver,
    typename boost::enable_if<
      boost::mpl::equal_to< Version, version_1_0_raw_as_binary >
     >::type* = 0
   );

  template< typename Version, typename Iterator, typename Receiver >
  UMP_FUNCTION void parse_object(
    Iterator &iter, const Iterator &end, Receiver &receiver,
    typename boost::enable_if<
      boost::mpl::equal_to< boost::mpl::bitand_< Version, version_mask >, version_1_1 >
     >::type* = 0
   );

  template< typename Version, typename Iterator, typename Receiver >
  UMP_FUNCTION void parse_short_struct( uint8_t head, Iterator &iter, const Iterator &end, Receiver &receiver ) {
    const size_t size = head & 0xf;
    receiver.begin_struct( size );
    for( size_t index = 0u; index != size; ++index ) {
      if( iter == end )
        throw unexpected_end();
      receiver.begin_pair();
      parse_object< Version >( iter, end, receiver );
      if( iter == end )
        throw unexpected_end();
      parse_object< Version >( iter, end, receiver );
      receiver.end_pair();
    }
    receiver.end_struct();
  }

  template< typename Version, typename Iterator, typename Receiver >
  UMP_FUNCTION void parse_short_array( uint8_t head, Iterator &iter, const Iterator &end, Receiver &receiver ) {
    const size_t size = head & 0xf;
    receiver.begin_array( size );
    for( size_t index = 0u; index != size; ++index ) {
      if( iter == end )
        throw unexpected_end();
      parse_object< Version >( iter, end, receiver );
    }
    receiver.end_array();
  }

  template< typename Version, typename Length, typename Iterator, typename Receiver >
  UMP_FUNCTION void parse_array( Iterator &iter, const Iterator &end, Receiver &receiver ) {
    const size_t size = convert_endian< Length >( iter, end );
    receiver.begin_array( size );
    for( size_t index = 0u; index != size; ++index ) {
      if( iter == end )
        throw unexpected_end();
      parse_object< Version >( iter, end, receiver );
    }
    receiver.end_array();
  }

  template< typename Version, typename Length, typename Iterator, typename Receiver >
  UMP_FUNCTION void parse_struct( Iterator &iter, const Iterator &end, Receiver &receiver ) {
    const size_t size = convert_endian< Length >( iter, end );
    receiver.begin_struct( size );
    for( size_t index = 0u; index != size; ++index ) {
      if( iter == end )
        throw unexpected_end();
      receiver.begin_pair();
      parse_object< Version >( iter, end, receiver );
      if( iter == end )
        throw unexpected_end();
      parse_object< Version >( iter, end, receiver );
      receiver.end_pair();
    }
    receiver.end_struct();
  }

  template< typename Version, typename Iterator, typename Receiver >
  UMP_FUNCTION void parse_object(
    Iterator &iter, const Iterator &end, Receiver &receiver,
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
      receiver( static_cast< uint64_t >( head ) );
      return;
    }
    else if( head < 0xc0u ) {
      if( head < 0x90u )
        parse_short_struct< Version >( head, iter, end, receiver );
      else if( head < 0xa0u )
        parse_short_array< Version >( head, iter, end, receiver );
      else
        parse_short_string( head, iter, end, receiver );
      return;
    }
    else if( head < 0xe0u ) {
      switch( head ) {
        case 0xc0u:
          receiver( none );
          return;
        case 0xc2u:
          receiver( false );
          return;
        case 0xc3u:
          receiver( true );
          return;
        case 0xcau:
          receiver( parse_float32< Iterator >( iter, end ) );
          return;
        case 0xcbu:
          receiver( parse_float64< Iterator >( iter, end ) );
          return;
        case 0xccu:
          receiver( parse_uint< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
          return;
        case 0xcdu:
          receiver( parse_uint< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
          return;
        case 0xceu:
          receiver( parse_uint< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
          return;
        case 0xcfu:
          receiver( parse_uint< boost::mpl::size_t< 8 >, Iterator >( iter, end ) );
          return;
        case 0xd0u:
          receiver( parse_int< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
          return;
        case 0xd1u:
          receiver( parse_int< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
          return;
        case 0xd2u:
          receiver( parse_int< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
          return;
        case 0xd3u:
          receiver( parse_int< boost::mpl::size_t< 8 >, Iterator >( iter, end ) );
          return;
        case 0xdau:
          receiver( std::move( parse_str< boost::mpl::size_t< 2 >, Iterator >( iter, end ) ) );
          return;
        case 0xdbu:
          receiver( std::move( parse_str< boost::mpl::size_t< 4 >, Iterator >( iter, end ) ) );
          return;
        case 0xdcu:
          parse_array< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end, receiver );
          return;
        case 0xddu:
          parse_array< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end, receiver );
          return;
        case 0xdeu:
          parse_struct< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end, receiver );
          return;
        case 0xdfu:
          parse_struct< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end, receiver );
          return;
        default:
          throw invalid_object();
      };
    }
    else {
      receiver( -static_cast< int64_t >( 0x100u - static_cast< uint32_t >( head ) ) );
      return;
    }
    throw invalid_object();
  }


  template< typename Version, typename Iterator, typename Receiver >
  UMP_FUNCTION void parse_object(
    Iterator &iter, const Iterator &end, Receiver &receiver,
    typename boost::enable_if<
      boost::mpl::equal_to< Version, version_1_0_raw_as_binary >
     >::type* = 0
   ) {
    if( iter == end )
      throw unexpected_end();
    const uint8_t head = *iter;
    ++iter;
    if( head < 0x80u ) {
      receiver( static_cast< uint64_t >( head ) );
      return;
    }
    else if( head < 0xc0u ) {
      if( head < 0x90u )
        parse_short_struct< Version >( head, iter, end, receiver );
      else if( head < 0xa0u )
        parse_short_array< Version >( head, iter, end, receiver );
      else
        parse_short_bin( head, iter, end, receiver );
      return;
    }
    else if( head < 0xe0u ) {
      switch( head ) {
        case 0xc0u:
          receiver( none );
          return;
        case 0xc2u:
          receiver( false );
          return;
        case 0xc3u:
          receiver( true );
          return;
        case 0xcau:
          receiver( parse_float32< Iterator >( iter, end ) );
          return;
        case 0xcbu:
          receiver( parse_float64< Iterator >( iter, end ) );
          return;
        case 0xccu:
          receiver( parse_uint< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
          return;
        case 0xcdu:
          receiver( parse_uint< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
          return;
        case 0xceu:
          receiver( parse_uint< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
          return;
        case 0xcfu:
          receiver( parse_uint< boost::mpl::size_t< 8 >, Iterator >( iter, end ) );
          return;
        case 0xd0u:
          receiver( parse_int< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
          return;
        case 0xd1u:
          receiver( parse_int< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
          return;
        case 0xd2u:
          receiver( parse_int< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
          return;
        case 0xd3u:
          receiver( parse_int< boost::mpl::size_t< 8 >, Iterator >( iter, end ) );
          return;
        case 0xdau:
          receiver( std::move( parse_bin< boost::mpl::size_t< 2 >, Iterator >( iter, end ) ) );
          return;
        case 0xdbu:
          receiver( std::move( parse_bin< boost::mpl::size_t< 4 >, Iterator >( iter, end ) ) );
          return;
        case 0xdcu:
          parse_array< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end, receiver );
          return;
        case 0xddu:
          parse_array< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end, receiver );
          return;
        case 0xdeu:
          parse_struct< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end, receiver );
          return;
        case 0xdfu:
          parse_struct< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end, receiver );
          return;
        default:
          throw invalid_object();
      };
    }
    else {
      receiver( -static_cast< int64_t >( 0x100u - static_cast< uint32_t >( head ) ) );
      return;
    }
    throw invalid_object();
  }

  template< typename Version, typename Iterator, typename Receiver >
  UMP_FUNCTION void parse_object(
    Iterator &iter, const Iterator &end, Receiver &receiver,
    typename boost::enable_if<
      boost::mpl::equal_to< boost::mpl::bitand_< Version, version_mask >, version_1_1 >
     >::type* = 0
   ) {
    if( iter == end )
      throw unexpected_end();
    const uint8_t head = *iter;
    ++iter;
    if( head < 0x80u ) {
      receiver( static_cast< uint64_t >( head ) );
      return;
    }
    else if( head < 0xc0u ) {
      if( head < 0x90u )
        parse_short_struct< Version >( head, iter, end, receiver );
      else if( head < 0xa0u )
        parse_short_array< Version >( head, iter, end, receiver );
      else
        receiver( std::move( parse_short_string( head, iter, end ) ) );
      return;
    }
    else if( head < 0xe0u ) {
      switch( head ) {
        case 0xc0u:
          receiver( none );
          return;
        case 0xc2u:
          receiver( false );
          return;
        case 0xc3u:
          receiver( true );
          return;
        case 0xc4u:
          receiver( std::move( parse_bin< boost::mpl::size_t< 1 >, Iterator >( iter, end ) ) );
          return;
        case 0xc5u:
          receiver( std::move( parse_bin< boost::mpl::size_t< 2 >, Iterator >( iter, end ) ) );
          return;
        case 0xc6u:
          receiver( std::move( parse_bin< boost::mpl::size_t< 4 >, Iterator >( iter, end ) ) );
          return;
        case 0xc7u:
          receiver( std::move( parse_ext< boost::mpl::size_t< 1 >, Iterator >( iter, end ) ) );
          return;
        case 0xc8u:
          receiver( std::move( parse_ext< boost::mpl::size_t< 2 >, Iterator >( iter, end ) ) );
          return;
        case 0xc9u:
          receiver( std::move( parse_ext< boost::mpl::size_t< 4 >, Iterator >( iter, end ) ) );
          return;
        case 0xcau:
          receiver( parse_float32< Iterator >( iter, end ) );
          return;
        case 0xcbu:
          receiver( parse_float64< Iterator >( iter, end ) );
          return;
        case 0xccu:
          receiver( parse_uint< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
          return;
        case 0xcdu:
          receiver( parse_uint< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
          return;
        case 0xceu:
          receiver( parse_uint< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
          return;
        case 0xcfu:
          receiver( parse_uint< boost::mpl::size_t< 8 >, Iterator >( iter, end ) );
          return;
        case 0xd0u:
          receiver( parse_int< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
          return;
        case 0xd1u:
          receiver( parse_int< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
          return;
        case 0xd2u:
          receiver( parse_int< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
          return;
        case 0xd3u:
          receiver( parse_int< boost::mpl::size_t< 8 >, Iterator >( iter, end ) );
          return;
        case 0xd4u:
          receiver( parse_fixext< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
          return;
        case 0xd5u:
          receiver( parse_fixext< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
          return;
        case 0xd6u:
          receiver( parse_fixext< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
          return;
        case 0xd7u:
          receiver( parse_fixext< boost::mpl::size_t< 8 >, Iterator >( iter, end ) );
          return;
        case 0xd8u:
          receiver( parse_fixext< boost::mpl::size_t< 16 >, Iterator >( iter, end ) );
          return;
        case 0xd9u:
          receiver( std::move( parse_str< boost::mpl::size_t< 1 >, Iterator >( iter, end ) ) );
          return;
        case 0xdau:
          receiver( std::move( parse_str< boost::mpl::size_t< 2 >, Iterator >( iter, end ) ) );
          return;
        case 0xdbu:
          receiver( std::move( parse_str< boost::mpl::size_t< 4 >, Iterator >( iter, end ) ) );
          return;
        case 0xdcu:
          parse_array< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end, receiver );
          return;
        case 0xddu:
          parse_array< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end, receiver );
          return;
        case 0xdeu:
          parse_struct< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end, receiver );
          return;
        case 0xdfu:
          parse_struct< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end, receiver );
          return;
        default:
          throw invalid_object();
      };
    }
    else {
      receiver( -static_cast< int64_t >( 0x100u - static_cast< uint32_t >( head ) ) );
      return;
    }
    throw invalid_object();
  }
}

#endif

