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

#include <vector>
#include <boost/spirit/include/karma.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE rapidmp_generate
#include <boost/test/unit_test.hpp>

#include <rapidmp/generator/generator.hpp>

BOOST_AUTO_TEST_CASE( v10_short_array ) {
  std::vector< uint32_t > data{{ 467832, 672348, 14078901 }};
  std::vector< rapidmp::object_type< std::vector< char >::const_iterator >::type > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( uint32_t value ) { return rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value ) ); } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0x93 ) << *( karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data ) );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_0 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v10_array16 ) {
  std::vector< uint32_t > data( 30000 );
  std::fill( data.begin(), data.end(), 6 );
  std::vector< rapidmp::object_type< std::vector< char >::const_iterator >::type > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( uint32_t value ) { return rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value ) ); } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0xdc ) << karma::big_word( data.size() ) << *( karma::byte_ ), boost::fusion::make_vector( data ) );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_0 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v10_array32 ) {
  std::vector< uint32_t > data( 65537 );
  std::fill( data.begin(), data.end(), 6 );
  std::vector< rapidmp::object_type< std::vector< char >::const_iterator >::type > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( uint32_t value ) { return rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value ) ); } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0xdd ) << karma::big_dword( data.size() ) << *( karma::byte_ ), boost::fusion::make_vector( data ) );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_0 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_short_array ) {
  std::vector< uint32_t > data{{ 467832, 672348, 14078901 }};
  std::vector< rapidmp::object_type< std::vector< char >::const_iterator >::type > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( uint32_t value ) { return rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value ) ); } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0x93 ) << *( karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data ) );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_array16 ) {
  std::vector< uint32_t > data( 30000 );
  std::fill( data.begin(), data.end(), 6 );
  std::vector< rapidmp::object_type< std::vector< char >::const_iterator >::type > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( uint32_t value ) { return rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value ) ); } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0xdc ) << karma::big_word( data.size() ) << *( karma::byte_ ), boost::fusion::make_vector( data ) );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_array32 ) {
  std::vector< uint32_t > data( 65537 );
  std::fill( data.begin(), data.end(), 6 );
  std::vector< rapidmp::object_type< std::vector< char >::const_iterator >::type > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( uint32_t value ) { return rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value ) ); } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0xdd ) << karma::big_dword( data.size() ) << *( karma::byte_ ), boost::fusion::make_vector( data ) );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v10_short_binary ) {
  std::vector< char > vdata( 10 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::binary< std::vector< char >::const_iterator >( vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xa0' + vdata.size() ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_0 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v10_binary16 ) {
  std::vector< char > vdata( 30000 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::binary< std::vector< char >::const_iterator >( vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xda' ) << karma::big_word( vdata.size() ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_0 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v10_binary32 ) {
  std::vector< char > vdata( 65537 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::binary< std::vector< char >::const_iterator >( vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xdb' ) << karma::big_dword( vdata.size() ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_0 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_binary8 ) {
  std::vector< char > vdata( 200 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::binary< std::vector< char >::const_iterator >( vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xc4' ) << karma::byte_( vdata.size() ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_binary16 ) {
  std::vector< char > vdata( 30000 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::binary< std::vector< char >::const_iterator >( vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xc5' ) << karma::big_word( vdata.size() ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_binary32 ) {
  std::vector< char > vdata( 65537 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::binary< std::vector< char >::const_iterator >( vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xc6' ) << karma::big_dword( vdata.size() ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( bool_true ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( true );
  std::vector< char > expected{{ '\xc3' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( bool_false ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( false );
  std::vector< char > expected{{ '\xc2' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v10_extension ) {
  std::string data( "H" );
  std::vector< char > vdata( data.begin(), data.end() );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::extension< std::vector< char >::const_iterator >( 14, vdata.cbegin(), vdata.cend() ) );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  BOOST_REQUIRE_THROW( rapidmp::generate_object< rapidmp::version_1_0 >( oiter, source ), rapidmp::not_supported );
}

BOOST_AUTO_TEST_CASE( v11_fixext1 ) {
  std::string data( "H" );
  std::vector< char > vdata( data.begin(), data.end() );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::extension< std::vector< char >::const_iterator >( 14, vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xd4' ) << karma::byte_( 14 ) << *karma::char_, data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_fixext2 ) {
  std::string data( "He" );
  std::vector< char > vdata( data.begin(), data.end() );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::extension< std::vector< char >::const_iterator >( 14, vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xd5' ) << karma::byte_( 14 ) << *karma::char_, data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_fixext4 ) {
  std::string data( "Hell" );
  std::vector< char > vdata( data.begin(), data.end() );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::extension< std::vector< char >::const_iterator >( 14, vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xd6' ) << karma::byte_( 14 ) << *karma::char_, data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_fixext8 ) {
  std::string data( "Hello, W" );
  std::vector< char > vdata( data.begin(), data.end() );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::extension< std::vector< char >::const_iterator >( 14, vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xd7' ) << karma::byte_( 14 ) << *karma::char_, data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_fixext16 ) {
  std::string data( "Hello, World!123" );
  std::vector< char > vdata( data.begin(), data.end() );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::extension< std::vector< char >::const_iterator >( 14, vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xd8' ) << karma::byte_( 14 ) << *karma::char_, data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_extension8 ) {
  std::vector< char > vdata( 200 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::extension< std::vector< char >::const_iterator >( 14, vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xc7' ) << karma::byte_( vdata.size() ) << karma::byte_( 14 ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_extension16 ) {
  std::vector< char > vdata( 30000 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::extension< std::vector< char >::const_iterator >( 14, vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xc8' ) << karma::big_word( vdata.size() ) << karma::byte_( 14 ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_extension32 ) {
  std::vector< char > vdata( 65537 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::extension< std::vector< char >::const_iterator >( 14, vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xc9' ) << karma::big_dword( vdata.size() ) << karma::byte_( 14 ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( float32 ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( 1.234567f );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0xca ) << karma::big_bin_float, 1.234567f );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( float64 ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( double( 2.3456789 ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0xcb ) << karma::big_bin_double, 2.3456789 );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( int_short ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( int64_t( -3 ) );
  std::vector< char > expected{{ '\xfd' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( int8 ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( int64_t( -112 ) );
  std::vector< char > expected{{ '\xd0', '\x90' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( int16 ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( int64_t( -5425 ) );
  std::vector< char > expected{{ '\xd1', '\xea', '\xcf' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( int32 ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( int64_t( -81648921 ) );
  std::vector< char > expected{{ '\xd2', '\xfb', '\x22', '\x22', '\xe7' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( int64 ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( int64_t( -3948019489015718702 ) );
  std::vector< char > expected{{ '\xd3', '\xc9', '\x35', '\xd1', '\x31', '\x36', '\xe6', '\x1c', '\xd2' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( none ) {
  rapidmp::none_type none;
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( none );
  std::vector< char > expected{{ '\xc0' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v10_short_string ) {
  std::string data( "Hello, World!" );
  std::vector< char > vdata( data.begin(), data.end() );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::string< std::vector< char >::const_iterator >( vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xa0' + data.size() ) << *karma::char_, data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_0 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v10_string16 ) {
  std::vector< char > vdata( 200 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::string< std::vector< char >::const_iterator >( vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xda' ) << karma::big_word( vdata.size() ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_0 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v10_string32 ) {
  std::vector< char > vdata( 65537 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::string< std::vector< char >::const_iterator >( vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xdb' ) << karma::big_dword( vdata.size() ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_0 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_short_string ) {
  std::string data( "Hello, World!" );
  std::vector< char > vdata( data.begin(), data.end() );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::string< std::vector< char >::const_iterator >( vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xa0' + data.size() ) << *karma::char_, data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_string8 ) {
  std::vector< char > vdata( 200 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::string< std::vector< char >::const_iterator >( vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xd9' ) << karma::byte_( vdata.size() ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_string16 ) {
  std::vector< char > vdata( 30000 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::string< std::vector< char >::const_iterator >( vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xda' ) << karma::big_word( vdata.size() ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_string32 ) {
  std::vector< char > vdata( 65537 );
  std::fill( vdata.begin(), vdata.end(), 'a' );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( rapidmp::string< std::vector< char >::const_iterator >( vdata.cbegin(), vdata.cend() ) );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( '\xdb' ) << karma::big_dword( vdata.size() ) << *karma::char_, vdata );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v10_short_struct ) {
  typedef std::pair< uint8_t, float > pair;
  std::vector< pair > data{{ pair( 1, 2.0f ), pair( 3, 4.0f ), pair( 5, 6.0f ) }};
  std::vector< std::pair< rapidmp::object_type< std::vector< char >::const_iterator >::type, rapidmp::object_type< std::vector< char >::const_iterator >::type > > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( const pair &value ) {
    return std::make_pair(
      rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value.first ) ),
      rapidmp::object_type< std::vector< char >::const_iterator >::type( value.second )
    );
  } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0x83 ) << *( karma::byte_ << karma::byte_( 0xca ) << karma::big_bin_float ), data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_0 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v10_struct16 ) {
  typedef std::pair< uint8_t, float > pair;
  std::vector< pair > data( 30 );
  std::fill( data.begin(), data.end(), pair( 1, 2.0f ) );
  std::vector< std::pair< rapidmp::object_type< std::vector< char >::const_iterator >::type, rapidmp::object_type< std::vector< char >::const_iterator >::type > > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( const pair &value ) {
    return std::make_pair(
      rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value.first ) ),
      rapidmp::object_type< std::vector< char >::const_iterator >::type( value.second )
    );
  } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0xde ) << karma::big_word( data.size() ) << *( karma::byte_ << karma::byte_( 0xca ) << karma::big_bin_float ), data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_0 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v10_struct32 ) {
  typedef std::pair< uint8_t, float > pair;
  std::vector< pair > data( 65537 );
  std::fill( data.begin(), data.end(), pair( 1, 2.0f ) );
  std::vector< std::pair< rapidmp::object_type< std::vector< char >::const_iterator >::type, rapidmp::object_type< std::vector< char >::const_iterator >::type > > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( const pair &value ) {
    return std::make_pair(
      rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value.first ) ),
      rapidmp::object_type< std::vector< char >::const_iterator >::type( value.second )
    );
  } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0xdf ) << karma::big_dword( data.size() ) << *( karma::byte_ << karma::byte_( 0xca ) << karma::big_bin_float ), data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_0 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_short_struct ) {
  typedef std::pair< uint8_t, float > pair;
  std::vector< pair > data{{ pair( 1, 2.0f ), pair( 3, 4.0f ), pair( 5, 6.0f ) }};
  std::vector< std::pair< rapidmp::object_type< std::vector< char >::const_iterator >::type, rapidmp::object_type< std::vector< char >::const_iterator >::type > > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( const pair &value ) {
    return std::make_pair(
      rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value.first ) ),
      rapidmp::object_type< std::vector< char >::const_iterator >::type( value.second )
    );
  } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0x83 ) << *( karma::byte_ << karma::byte_( 0xca ) << karma::big_bin_float ), data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_struct16 ) {
  typedef std::pair< uint8_t, float > pair;
  std::vector< pair > data( 30 );
  std::fill( data.begin(), data.end(), pair( 1, 2.0f ) );
  std::vector< std::pair< rapidmp::object_type< std::vector< char >::const_iterator >::type, rapidmp::object_type< std::vector< char >::const_iterator >::type > > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( const pair &value ) {
    return std::make_pair(
      rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value.first ) ),
      rapidmp::object_type< std::vector< char >::const_iterator >::type( value.second )
    );
  } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0xde ) << karma::big_word( data.size() ) << *( karma::byte_ << karma::byte_( 0xca ) << karma::big_bin_float ), data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v11_struct32 ) {
  typedef std::pair< uint8_t, float > pair;
  std::vector< pair > data( 65537 );
  std::fill( data.begin(), data.end(), pair( 1, 2.0f ) );
  std::vector< std::pair< rapidmp::object_type< std::vector< char >::const_iterator >::type, rapidmp::object_type< std::vector< char >::const_iterator >::type > > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( const pair &value ) {
    return std::make_pair(
      rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value.first ) ),
      rapidmp::object_type< std::vector< char >::const_iterator >::type( value.second )
    );
  } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0xdf ) << karma::big_dword( data.size() ) << *( karma::byte_ << karma::byte_( 0xca ) << karma::big_bin_float ), data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( uint_short ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( uint64_t( 0x10ull ) );
  std::vector< char > expected{{ '\x10' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( uint8 ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( uint64_t( 0xaeull ) );
  std::vector< char > expected{{ '\xcc', '\xae' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( uint16 ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( uint64_t( 0xabcdull ) );
  std::vector< char > expected{{ '\xcd', '\xab', '\xcd' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( uint32 ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( uint64_t( 0x12345678ull ) );
  std::vector< char > expected{{ '\xce', '\x12', '\x34', '\x56', '\x78' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( uint64 ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( uint64_t( 0x1234567812345678ull ) );
  std::vector< char > expected{{ '\xcf', '\x12', '\x34', '\x56', '\x78', '\x12', '\x34', '\x56', '\x78' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object< rapidmp::version_1_1 >( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

