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

#ifndef RAPIDMP_PARSER_PYTHON_HPP
#define RAPIDMP_PARSER_PYTHON_HPP

#include <cstdint>
#include <boost/foreach.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/python.hpp>

#include <rapidmp/config.hpp> 
#include <rapidmp/type.hpp>
#include <rapidmp/exceptions.hpp>
#include <rapidmp/convert_endian.hpp>
#include <rapidmp/parser/core.hpp>

namespace rapidmp {
  template< typename Version, typename Iterator >
  UMP_FUNCTION boost::python::object parse_object(
    Iterator &iter, const Iterator &end,
    typename boost::enable_if<
      boost::mpl::or_<
        boost::mpl::equal_to< Version, version_1_0 >,
        boost::mpl::equal_to< Version, version_1_0_raw_as_string >
      >
     >::type* = 0
   );
  template< typename Version, typename Iterator >
  UMP_FUNCTION boost::python::object parse_object(
    Iterator &iter, const Iterator &end,
    typename boost::enable_if<
      boost::mpl::equal_to< Version, version_1_0_raw_as_binary >
     >::type* = 0
   );
  template< typename Version, typename Iterator >
  UMP_FUNCTION boost::python::object parse_object(
    Iterator &iter, const Iterator &end,
    typename boost::enable_if<
      boost::mpl::equal_to< boost::mpl::bitand_< Version, version_mask >, version_1_1 >
     >::type* = 0
   );

  template< typename Version, typename Iterator >
  UMP_FUNCTION boost::python::object parse_short_struct( uint8_t head, Iterator &iter, const Iterator &end ) {
    const size_t size = head & 0xf;
    boost::python::dict dict;
    for( size_t index = 0u; index != size; ++index ) {
      if( iter == end )
        throw unexpected_end();
      const boost::python::object key( parse_object< Version >( iter, end ) );
      if( iter == end )
        throw unexpected_end();
      dict[ key ] = parse_object< Version >( iter, end );
    }
    return boost::python::object( std::move( dict ) );
  }

  template< typename Version, typename Iterator >
  UMP_FUNCTION boost::python::object parse_short_array( uint8_t head, Iterator &iter, const Iterator &end ) {
    const size_t size = head & 0xf;
    boost::python::list list;
    for( size_t index = 0u; index != size; ++index ) {
      if( iter == end )
        throw unexpected_end();
      list.append( parse_object< Version >( iter, end ) );
    }
    return boost::python::object( std::move( list ) );
  }
  
  template< typename Version, typename Length, typename Iterator >
  UMP_FUNCTION boost::python::object parse_array( Iterator &iter, const Iterator &end ) {
    const size_t size = convert_endian< Length >( iter, end );
    boost::python::list list;
    for( size_t index = 0; index != size; ++index ) {
      if( iter == end )
        throw unexpected_end();
      list.append( parse_object< Version >( iter, end ) );
    }
    return boost::python::object( std::move( list ) );
  }

  template< typename Version, typename Length, typename Iterator >
  UMP_FUNCTION boost::python::object parse_struct( Iterator &iter, const Iterator &end ) {
    const size_t size = convert_endian< Length >( iter, end );
    boost::python::dict dict;
    for( size_t index = 0u; index != size; ++index ) {
      if( iter == end )
        throw unexpected_end();
      typename boost::python::object &&key( parse_object< Version >( iter, end ) );
      if( iter == end )
        throw unexpected_end();
      dict[ key ] = parse_object< Version >( iter, end );
    }
    return boost::python::object( std::move( dict ) );
  }

  template< typename Iterator >
  UMP_FUNCTION boost::python::str rapidmp2python(
    const string< Iterator > &value,
    typename boost::enable_if<
      boost::is_pointer< Iterator >
    >::type* = 0
  ) {
    return boost::python::str(
      reinterpret_cast< const char* >( boost::begin( value.range ) ),
      reinterpret_cast< const char* >( boost::end( value.range ) )
    );
  }

  template< typename Iterator >
  UMP_FUNCTION boost::python::str rapidmp2python(
    const string< Iterator > &value,
    typename boost::enable_if<
      boost::mpl::not_< boost::is_pointer< Iterator > >
    >::type* = 0
  ) {
    const std::vector< char > temp( boost::begin( value.range ), boost::end( value.range ) );
    return boost::python::str(
      reinterpret_cast< const char* >( temp.data() ),
      reinterpret_cast< const char* >( temp.data() + temp.size() )
    );
  }

#if PY_MAJOR_VERSION >= 3
  template< typename Iterator >
  UMP_FUNCTION boost::python::object rapidmp2python(
    const binary< Iterator > &value,
    typename boost::enable_if<
      boost::is_pointer< Iterator >
    >::type* = 0
  ) {
    PyObject *raw = PyBytes_FromStringAndSize(
      reinterpret_cast< const char* >( boost::begin( value.range ) ),
      boost::size( value.range )
    );
    return boost::python::object( boost::python::handle<>( raw ) );
  }

  template< typename Iterator >
  UMP_FUNCTION boost::python::object rapidmp2python(
    const binary< Iterator > &value,
    typename boost::enable_if<
      boost::mpl::not_< boost::is_pointer< Iterator > >
    >::type* = 0
  ) {
    const std::vector< char > temp( boost::begin( value.range ), boost::end( value.range ) );
    PyObject *raw = PyBytes_FromStringAndSize(
      reinterpret_cast< const char* >( boost::begin( temp ) ),
      boost::size( temp )
    );
    return boost::python::object( boost::python::handle<>( raw ) );
  }
#else
  template< typename Iterator >
  UMP_FUNCTION boost::python::str rapidmp2python(
    const binary< Iterator > &value,
    typename boost::enable_if<
      boost::is_pointer< Iterator >
    >::type* = 0
  ) {
    return boost::python::str(
      reinterpret_cast< const char* >( boost::begin( value.range ) ),
      reinterpret_cast< const char* >( boost::end( value.range ) )
    );
  }

  template< typename Iterator >
  UMP_FUNCTION boost::python::str rapidmp2python(
    const binary< Iterator > &value,
    typename boost::enable_if<
      boost::mpl::not_< boost::is_pointer< Iterator > >
    >::type* = 0
  ) {
    const std::vector< char > temp( boost::begin( value.range ), boost::end( value.range ) );
    return boost::python::str(
      reinterpret_cast< const char* >( temp.data() ),
      reinterpret_cast< const char* >( temp.data() + temp.size() )
    );
  }
#endif

  template< typename Version, typename Iterator >
  UMP_FUNCTION boost::python::object parse_object(
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
      return boost::python::object( static_cast< uint64_t >( head ) );
    }
    else if( head < 0xc0u ) {
      if( head < 0x90u )
        return parse_short_struct< Version >( head, iter, end );
      else if( head < 0xa0u )
        return parse_short_array< Version >( head, iter, end );
      else
        return rapidmp2python( parse_short_string( head, iter, end ) );
    }
    else if( head < 0xe0u ) {
      switch( head ) {
        case 0xc0u:
          return boost::python::object();
        case 0xc2u:
          return boost::python::object( false );
        case 0xc3u:
          return boost::python::object( true );
        case 0xcau:
          return boost::python::object( parse_float32< Iterator >( iter, end ) );
        case 0xcbu:
          return boost::python::object( parse_float64< Iterator >( iter, end ) );
        case 0xccu:
          return boost::python::object( parse_uint< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
        case 0xcdu:
          return boost::python::object( parse_uint< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xceu:
          return boost::python::object( parse_uint< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xcfu:
          return boost::python::object( parse_uint< boost::mpl::size_t< 8 >, Iterator >( iter, end ) );
        case 0xd0u:
          return boost::python::object( parse_int< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
        case 0xd1u:
          return boost::python::object( parse_int< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xd2u:
          return boost::python::object( parse_int< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xd3u:
          return boost::python::object( parse_int< boost::mpl::size_t< 8 >, Iterator >( iter, end ) );
        case 0xdau:
          return rapidmp2python( parse_str< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xdbu:
          return rapidmp2python( parse_str< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xdcu:
          return parse_array< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end );
        case 0xddu:
          return parse_array< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end );
        case 0xdeu:
          return parse_struct< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end );
        case 0xdfu:
          return parse_struct< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end );
        default:
          throw invalid_object();
      };
    }
    else {
      return boost::python::object( -static_cast< int64_t >( 0x100u - static_cast< uint32_t >( head ) ) );
    }
    throw invalid_object();
  }

  template< typename Version, typename Iterator >
  UMP_FUNCTION boost::python::object parse_object(
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
        return  parse_short_struct< Version >( head, iter, end );
      else if( head < 0xa0u )
        return  parse_short_array< Version >( head, iter, end );
      else
        return  rapidmp2python( parse_short_bin( head, iter, end ) );
    }
    else if( head < 0xe0u ) {
      switch( head ) {
        case 0xc0u:
          return boost::python::object();
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
          return  rapidmp2python( parse_bin< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xdbu:
          return  rapidmp2python( parse_bin< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xdcu:
          return  parse_array< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end );
        case 0xddu:
          return  parse_array< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end );
        case 0xdeu:
          return  parse_struct< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end );
        case 0xdfu:
          return  parse_struct< Version, boost::mpl::size_t< 4 >, Iterator >( iter, end );
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
  UMP_FUNCTION boost::python::object parse_object(
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
      return boost::python::object( static_cast< uint64_t >( head ) );
    }
    else if( head < 0xc0u ) {
      if( head < 0x90u )
        return std::move( parse_short_struct< Version >( head, iter, end ) );
      else if( head < 0xa0u )
        return std::move( parse_short_array< Version >( head, iter, end ) );
      else
        return rapidmp2python( parse_short_string( head, iter, end ) );
    }
    else if( head < 0xe0u ) {
      switch( head ) {
        case 0xc0u:
          return boost::python::object();
        case 0xc2u:
          return boost::python::object( false );
        case 0xc3u:
          return boost::python::object( true );
        case 0xc4u:
          return  rapidmp2python( parse_bin< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
        case 0xc5u:
          return  rapidmp2python( parse_bin< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xc6u:
          return  rapidmp2python( parse_bin< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        /*case 0xc7u:
          return  parse_ext< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
        case 0xc8u:
          return  parse_ext< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xc9u:
          return  parse_ext< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );*/
        case 0xcau:
          return boost::python::object( parse_float32< Iterator >( iter, end ) );
        case 0xcbu:
          return boost::python::object( parse_float64< Iterator >( iter, end ) );
        case 0xccu:
          return boost::python::object( parse_uint< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
        case 0xcdu:
          return boost::python::object( parse_uint< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xceu:
          return boost::python::object( parse_uint< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xcfu:
          return boost::python::object( parse_uint< boost::mpl::size_t< 8 >, Iterator >( iter, end ) );
        case 0xd0u:
          return boost::python::object( parse_int< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
        case 0xd1u:
          return boost::python::object( parse_int< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xd2u:
          return boost::python::object( parse_int< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xd3u:
          return boost::python::object( parse_int< boost::mpl::size_t< 8 >, Iterator >( iter, end ) );
        /*case 0xd4u:
          return parse_fixext< boost::mpl::size_t< 1 >, Iterator >( iter, end );
        case 0xd5u:
          return parse_fixext< boost::mpl::size_t< 2 >, Iterator >( iter, end );
        case 0xd6u:
          return parse_fixext< boost::mpl::size_t< 4 >, Iterator >( iter, end );
        case 0xd7u:
          return parse_fixext< boost::mpl::size_t< 8 >, Iterator >( iter, end );
        case 0xd8u:
          return parse_fixext< boost::mpl::size_t< 16 >, Iterator >( iter, end );*/
        case 0xd9u:
          return rapidmp2python( parse_str< boost::mpl::size_t< 1 >, Iterator >( iter, end ) );
        case 0xdau:
          return rapidmp2python( parse_str< boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
        case 0xdbu:
          return rapidmp2python( parse_str< boost::mpl::size_t< 4 >, Iterator >( iter, end ) );
        case 0xdcu:
          return std::move(  parse_array< Version, boost::mpl::size_t< 2 >, Iterator >( iter, end ) );
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
      return boost::python::object( -static_cast< int64_t >( 0x100u - static_cast< uint32_t >( head ) ) );
    }
    throw invalid_object();
  }
}

#endif

