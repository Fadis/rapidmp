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
#define BOOST_TEST_MODULE rapidmp_parser_array
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

