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
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/equal.hpp>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE rapidmp_parser
#include <boost/test/unit_test.hpp>

#include <rapidmp/parser.hpp>

BOOST_AUTO_TEST_CASE( array_short ) {
  std::vector< char > source;
  std::vector< uint32_t > data{{ 467832, 672348, 14078901 }};
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0x93 ) << *( karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< typename rapidmp::array_type< std::vector< char >::const_iterator >::type >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( parsed.size(), 3 );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 0 ] ), data[ 0 ] );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 1 ] ), data[ 1 ] );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 2 ] ), data[ 2 ] );
}

BOOST_AUTO_TEST_CASE( array16 ) {
  std::vector< char > source;
  std::vector< uint32_t > data{{ 467832, 672348, 14078901 }};
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xdc ) << karma::big_word << *( karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data.size(), data ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< typename rapidmp::array_type< std::vector< char >::const_iterator >::type >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( parsed.size(), 3 );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 0 ] ), data[ 0 ] );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 1 ] ), data[ 1 ] );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 2 ] ), data[ 2 ] );
}

BOOST_AUTO_TEST_CASE( array32 ) {
  std::vector< char > source;
  std::vector< uint32_t > data{{ 467832, 672348, 14078901 }};
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xdd ) << karma::big_dword << *( karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data.size(), data ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< typename rapidmp::array_type< std::vector< char >::const_iterator >::type >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( parsed.size(), 3 );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 0 ] ), data[ 0 ] );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 1 ] ), data[ 1 ] );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 2 ] ), data[ 2 ] );
}

BOOST_AUTO_TEST_CASE( v10_binary8 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc4 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( message.size(), message ) );
  auto iter = source.cbegin();
  BOOST_REQUIRE_THROW( rapidmp::parse_object< rapidmp::version_1_0 >( iter, source.cend() ), rapidmp::invalid_object );
}

BOOST_AUTO_TEST_CASE( v11_binary8 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc4 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( message.size(), message ) );
  auto iter = source.cbegin();
  BOOST_CHECK( boost::equal( message, boost::get< rapidmp::binary< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ).range ) );
}

BOOST_AUTO_TEST_CASE( v10_binary16 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc5 ) << karma::big_word << *karma::char_, boost::fusion::make_vector( message.size(), message ) );
  auto iter = source.cbegin();
  BOOST_REQUIRE_THROW( rapidmp::parse_object< rapidmp::version_1_0 >( iter, source.cend() ), rapidmp::invalid_object );
}

BOOST_AUTO_TEST_CASE( v11_binary16 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc5 ) << karma::big_word << *karma::char_, boost::fusion::make_vector( message.size(), message ) );
  auto iter = source.cbegin();
  BOOST_CHECK( boost::equal( message, boost::get< rapidmp::binary< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ).range ) );
}

BOOST_AUTO_TEST_CASE( v10_binary32 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc6 ) << karma::big_dword << *karma::char_, boost::fusion::make_vector( message.size(), message ) );
  auto iter = source.cbegin();
  BOOST_REQUIRE_THROW( rapidmp::parse_object< rapidmp::version_1_0 >( iter, source.cend() ), rapidmp::invalid_object );
}

BOOST_AUTO_TEST_CASE( v11_binary32 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc6 ) << karma::big_dword << *karma::char_, boost::fusion::make_vector( message.size(), message ) );
  auto iter = source.cbegin();
  BOOST_CHECK( boost::equal( message, boost::get< rapidmp::binary< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ).range ) );
}

BOOST_AUTO_TEST_CASE( bool_true ) {
  std::vector< char > source;
  source.push_back( '\xc3' );
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< bool >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), true );
}

BOOST_AUTO_TEST_CASE( bool_false ) {
  std::vector< char > source;
  source.push_back( '\xc2' );
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< bool >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), false );
}

BOOST_AUTO_TEST_CASE( v10_fixext1 ) {
  std::vector< char > source;
  const std::string message( "H" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd4 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  BOOST_REQUIRE_THROW( rapidmp::parse_object< rapidmp::version_1_0 >( iter, source.cend() ), rapidmp::invalid_object );
}

BOOST_AUTO_TEST_CASE( v11_fixext1 ) {
  std::vector< char > source;
  const std::string message( "H" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd4 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( v10_fixext2 ) {
  std::vector< char > source;
  const std::string message( "He" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd5 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  BOOST_REQUIRE_THROW( rapidmp::parse_object< rapidmp::version_1_0 >( iter, source.cend() ), rapidmp::invalid_object );
}

BOOST_AUTO_TEST_CASE( v11_fixext2 ) {
  std::vector< char > source;
  const std::string message( "He" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd5 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( v10_fixext4 ) {
  std::vector< char > source;
  const std::string message( "Hell" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd6 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  BOOST_REQUIRE_THROW( rapidmp::parse_object< rapidmp::version_1_0 >( iter, source.cend() ), rapidmp::invalid_object );
}

BOOST_AUTO_TEST_CASE( v11_fixext4 ) {
  std::vector< char > source;
  const std::string message( "Hell" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd6 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( v10_fixext8 ) {
  std::vector< char > source;
  const std::string message( "Hello, W" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd7 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  BOOST_REQUIRE_THROW( rapidmp::parse_object< rapidmp::version_1_0 >( iter, source.cend() ), rapidmp::invalid_object );
}

BOOST_AUTO_TEST_CASE( v11_fixext8 ) {
  std::vector< char > source;
  const std::string message( "Hello, W" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd7 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( v10_fixext16 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!123" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd8 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  BOOST_REQUIRE_THROW( rapidmp::parse_object< rapidmp::version_1_0 >( iter, source.cend() ), rapidmp::invalid_object );
}

BOOST_AUTO_TEST_CASE( v11_fixext16 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!123" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd8 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( v10_extension8 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc7 ) << karma::byte_ << karma::byte_ << *karma::char_, boost::fusion::make_vector( message.size(), 14, message ) );
  auto iter = source.cbegin();
  BOOST_REQUIRE_THROW( rapidmp::parse_object< rapidmp::version_1_0 >( iter, source.cend() ), rapidmp::invalid_object );
}

BOOST_AUTO_TEST_CASE( v11_extension8 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc7 ) << karma::byte_ << karma::byte_ << *karma::char_, boost::fusion::make_vector( message.size(), 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( v10_extension16 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc8 ) << karma::big_word << karma::byte_ << *karma::char_, boost::fusion::make_vector( message.size(), 14, message ) );
  auto iter = source.cbegin();
  BOOST_REQUIRE_THROW( rapidmp::parse_object< rapidmp::version_1_0 >( iter, source.cend() ), rapidmp::invalid_object );
}

BOOST_AUTO_TEST_CASE( v11_extension16 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc8 ) << karma::big_word << karma::byte_ << *karma::char_, boost::fusion::make_vector( message.size(), 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( v10_extension32 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc9 ) << karma::big_dword << karma::byte_ << *karma::char_, boost::fusion::make_vector( message.size(), 14, message ) );
  auto iter = source.cbegin();
  BOOST_REQUIRE_THROW( rapidmp::parse_object< rapidmp::version_1_0 >( iter, source.cend() ), rapidmp::invalid_object );
}


BOOST_AUTO_TEST_CASE( v11_extension32 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc9 ) << karma::big_dword << karma::byte_ << *karma::char_, boost::fusion::make_vector( message.size(), 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( float32 ) {
  std::vector< char > source;
  source.push_back( '\xca' );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::big_bin_float, 1.234567f );
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< float >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), 1.234567f );
}

BOOST_AUTO_TEST_CASE( float64 ) {
  std::vector< char > source;
  source.push_back( '\xcb' );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::big_bin_double, 2.3456789 );
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< double >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), 2.3456789 );
}

BOOST_AUTO_TEST_CASE( int_short ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source;
  source.push_back( -5 );
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< int64_t >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), -5ll );
}

BOOST_AUTO_TEST_CASE( int8 ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source{{ '\xd0', -125 }};
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< int64_t >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), -125ll );
}

BOOST_AUTO_TEST_CASE( int16 ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source{{ '\xd1', '\xff', -125 }};
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< int64_t >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), -125ll );
}

BOOST_AUTO_TEST_CASE( int32 ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source{{ '\xd2', '\xff', '\xff', '\xff', -125 }};
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< int64_t >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), -125ll );
}

BOOST_AUTO_TEST_CASE( int64 ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source{{ '\xd3', '\xff', '\xff', '\xff', '\xff', '\xff', '\xff', '\xff', -125 }};
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< int64_t >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), -125ll );
}

BOOST_AUTO_TEST_CASE( none ) {
  std::vector< char > source;
  source.push_back( '\xc0' );
  auto iter = source.cbegin();
  BOOST_CHECK( boost::get< rapidmp::none_type >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ) == rapidmp::none_type() );
}

BOOST_AUTO_TEST_CASE( string_short ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  source.push_back( '\xa0' + message.size() );
  boost::copy( message, std::back_inserter( source ) );
  auto iter = source.cbegin();
  BOOST_CHECK( boost::equal( message, boost::get< rapidmp::string< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ).range ) );
}

BOOST_AUTO_TEST_CASE( string8 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd9 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( message.size(), message ) );
  auto iter = source.cbegin();
  BOOST_CHECK( boost::equal( message, boost::get< rapidmp::string< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ).range ) );
}

BOOST_AUTO_TEST_CASE( string16 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xda ) << karma::big_word << *karma::char_, boost::fusion::make_vector( message.size(), message ) );
  auto iter = source.cbegin();
  BOOST_CHECK( boost::equal( message, boost::get< rapidmp::string< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ).range ) );
}

BOOST_AUTO_TEST_CASE( string32 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xdb ) << karma::big_dword << *karma::char_, boost::fusion::make_vector( message.size(), message ) );
  auto iter = source.cbegin();
  BOOST_CHECK( boost::equal( message, boost::get< rapidmp::string< std::vector< char >::const_iterator > >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ).range ) );
}

BOOST_AUTO_TEST_CASE( struct_short ) {
  std::vector< char > source;
  typedef std::pair< uint32_t, uint32_t > pair;
  std::vector< pair > data{{ pair( 467832, 8923611 ), pair( 672348, 567829 ), pair( 14078901, 247 ) }};
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0x83 ) << *( karma::byte_( 0xce ) << karma::big_dword << karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< typename rapidmp::struct_type< std::vector< char >::const_iterator >::type >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( parsed.size(), 3 );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 0 ].first ), data[ 0 ].first );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 0 ].second ), data[ 0 ].second );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 1 ].first ), data[ 1 ].first );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 1 ].second ), data[ 1 ].second );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 2 ].first ), data[ 2 ].first );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 2 ].second ), data[ 2 ].second );
}

BOOST_AUTO_TEST_CASE( struct16 ) {
  std::vector< char > source;
  typedef std::pair< uint32_t, uint32_t > pair;
  std::vector< pair > data{{ pair( 467832, 8923611 ), pair( 672348, 567829 ), pair( 14078901, 247 ) }};
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xde ) << karma::big_word << *( karma::byte_( 0xce ) << karma::big_dword << karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data.size(), data ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< typename rapidmp::struct_type< std::vector< char >::const_iterator >::type >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( parsed.size(), 3 );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 0 ].first ), data[ 0 ].first );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 0 ].second ), data[ 0 ].second );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 1 ].first ), data[ 1 ].first );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 1 ].second ), data[ 1 ].second );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 2 ].first ), data[ 2 ].first );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 2 ].second ), data[ 2 ].second );
}

BOOST_AUTO_TEST_CASE( struct32 ) {
  std::vector< char > source;
  typedef std::pair< uint32_t, uint32_t > pair;
  std::vector< pair > data{{ pair( 467832, 8923611 ), pair( 672348, 567829 ), pair( 14078901, 247 ) }};
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xdf ) << karma::big_dword << *( karma::byte_( 0xce ) << karma::big_dword << karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data.size(), data ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< typename rapidmp::struct_type< std::vector< char >::const_iterator >::type >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( parsed.size(), 3 );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 0 ].first ), data[ 0 ].first );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 0 ].second ), data[ 0 ].second );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 1 ].first ), data[ 1 ].first );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 1 ].second ), data[ 1 ].second );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 2 ].first ), data[ 2 ].first );
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( parsed[ 2 ].second ), data[ 2 ].second );
}

BOOST_AUTO_TEST_CASE( uint_short ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source;
  source.push_back( 10 );
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), 10ull );
}

BOOST_AUTO_TEST_CASE( uint8 ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source{{ '\xcc', '\x0a' }};
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), 10ull );
}

BOOST_AUTO_TEST_CASE( uint16 ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source{{ '\xcd', '\x00', '\x0a' }};
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), 10ull );
}

BOOST_AUTO_TEST_CASE( uint32 ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source{{ '\xce', '\x00', '\x00', '\x00', '\x0a' }};
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), 10ull );
}

BOOST_AUTO_TEST_CASE( uint64 ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source{{ '\xcf', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x00', '\x0a' }};
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< uint64_t >( rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend() ) ), 10ull );
}

