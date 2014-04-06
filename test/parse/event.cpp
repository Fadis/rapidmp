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
#define BOOST_TEST_MODULE rapidmp_sax
#include <boost/test/unit_test.hpp>

#include <rapidmp/parser/event.hpp>
#include <rapidmp/debug_receiver.hpp>

BOOST_AUTO_TEST_CASE( array_short ) {
  std::vector< char > source;
  std::vector< uint32_t > data{{ 467832, 672348, 14078901 }};
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0x93 ) << *( karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data ) );
  auto iter = source.cbegin();
  rapidmp::debug_receiver< std::vector< char >::const_iterator > receiver;
  rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend(), receiver );
  BOOST_CHECK_EQUAL( receiver.get_log(), std::string( "[uuu]" ) );
}

BOOST_AUTO_TEST_CASE( array16 ) {
  std::vector< char > source;
  std::vector< uint32_t > data{{ 467832, 672348, 14078901 }};
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xdc ) << karma::big_word << *( karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data.size(), data ) );
  auto iter = source.cbegin();
  rapidmp::debug_receiver< std::vector< char >::const_iterator > receiver;
  rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend(), receiver );
  BOOST_CHECK_EQUAL( receiver.get_log(), std::string( "[uuu]" ) );
}

BOOST_AUTO_TEST_CASE( array32 ) {
  std::vector< char > source;
  std::vector< uint32_t > data{{ 467832, 672348, 14078901 }};
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xdd ) << karma::big_dword << *( karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data.size(), data ) );
  auto iter = source.cbegin();
  rapidmp::debug_receiver< std::vector< char >::const_iterator > receiver;
  rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend(), receiver );
  BOOST_CHECK_EQUAL( receiver.get_log(), std::string( "[uuu]" ) );
}

BOOST_AUTO_TEST_CASE( struct_short ) {
  std::vector< char > source;
  typedef std::pair< uint32_t, uint32_t > pair;
  std::vector< pair > data{{ pair( 467832, 8923611 ), pair( 672348, 567829 ), pair( 14078901, 247 ) }};
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0x83 ) << *( karma::byte_( 0xce ) << karma::big_dword << karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data ) );
  auto iter = source.cbegin();
  rapidmp::debug_receiver< std::vector< char >::const_iterator > receiver;
  rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend(), receiver );
  BOOST_CHECK_EQUAL( receiver.get_log(), std::string( "{uuuuuu}" ) );
}

BOOST_AUTO_TEST_CASE( struct16 ) {
  std::vector< char > source;
  typedef std::pair< uint32_t, uint32_t > pair;
  std::vector< pair > data{{ pair( 467832, 8923611 ), pair( 672348, 567829 ), pair( 14078901, 247 ) }};
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xde ) << karma::big_word << *( karma::byte_( 0xce ) << karma::big_dword << karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data.size(), data ) );
  auto iter = source.cbegin();
  rapidmp::debug_receiver< std::vector< char >::const_iterator > receiver;
  rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend(), receiver );
  BOOST_CHECK_EQUAL( receiver.get_log(), std::string( "{uuuuuu}" ) );
}

BOOST_AUTO_TEST_CASE( struct32 ) {
  std::vector< char > source;
  typedef std::pair< uint32_t, uint32_t > pair;
  std::vector< pair > data{{ pair( 467832, 8923611 ), pair( 672348, 567829 ), pair( 14078901, 247 ) }};
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( source ), karma::byte_( 0xdf ) << karma::big_dword << *( karma::byte_( 0xce ) << karma::big_dword << karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data.size(), data ) );
  auto iter = source.cbegin();
  rapidmp::debug_receiver< std::vector< char >::const_iterator > receiver;
  rapidmp::parse_object< rapidmp::version_1_1 >( iter, source.cend(), receiver );
  BOOST_CHECK_EQUAL( receiver.get_log(), std::string( "{uuuuuu}" ) );
}


