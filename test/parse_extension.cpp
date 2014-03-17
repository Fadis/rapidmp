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
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/algorithm/equal.hpp>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE rapidmp_parser_extension
#include <boost/test/unit_test.hpp>

#include <rapidmp/parser.hpp>

BOOST_AUTO_TEST_CASE( fixext1 ) {
  std::vector< char > source;
  const std::string message( "H" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd4 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( fixext2 ) {
  std::vector< char > source;
  const std::string message( "He" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd5 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( fixext4 ) {
  std::vector< char > source;
  const std::string message( "Hell" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd6 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( fixext8 ) {
  std::vector< char > source;
  const std::string message( "Hello, W" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd7 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( fixext16 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!123" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xd8 ) << karma::byte_ << *karma::char_, boost::fusion::make_vector( 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( extension8 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc7 ) << karma::byte_ << karma::byte_ << *karma::char_, boost::fusion::make_vector( message.size(), 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}


BOOST_AUTO_TEST_CASE( extension16 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc8 ) << karma::big_word << karma::byte_ << *karma::char_, boost::fusion::make_vector( message.size(), 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

BOOST_AUTO_TEST_CASE( extension32 ) {
  std::vector< char > source;
  const std::string message( "Hello, World!" );
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xc9 ) << karma::big_dword << karma::byte_ << *karma::char_, boost::fusion::make_vector( message.size(), 14, message ) );
  auto iter = source.cbegin();
  const auto parsed = boost::get< rapidmp::extension< std::vector< char >::const_iterator > >( rapidmp::parse_object( iter, source.cend() ) );
  BOOST_CHECK_EQUAL( uint8_t( 14 ), parsed.type );
  BOOST_CHECK( boost::equal( message, parsed.range ) );
}

