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
#define BOOST_TEST_MODULE rapidmp_parser_struct
#include <boost/test/unit_test.hpp>

#include <rapidmp/parser.hpp>

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

BOOST_AUTO_TEST_CASE( array16 ) {
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

BOOST_AUTO_TEST_CASE( array32 ) {
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

