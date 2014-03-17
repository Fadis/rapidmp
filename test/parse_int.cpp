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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE rapidmp_parser_int
#include <boost/test/unit_test.hpp>

#include <rapidmp/parser.hpp>

BOOST_AUTO_TEST_CASE( int_short ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source;
  source.push_back( -5 );
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< int64_t >( rapidmp::parse_object( iter, source.cend() ) ), -5ll );
}

BOOST_AUTO_TEST_CASE( int8 ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source{{ '\xd0', -125 }};
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< int64_t >( rapidmp::parse_object( iter, source.cend() ) ), -125ll );
}

BOOST_AUTO_TEST_CASE( int16 ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source{{ '\xd1', '\xff', -125 }};
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< int64_t >( rapidmp::parse_object( iter, source.cend() ) ), -125ll );
}

BOOST_AUTO_TEST_CASE( int32 ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source{{ '\xd2', '\xff', '\xff', '\xff', -125 }};
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< int64_t >( rapidmp::parse_object( iter, source.cend() ) ), -125ll );
}

BOOST_AUTO_TEST_CASE( int64 ) {
  typedef rapidmp::object_type< std::vector< char >::const_iterator >::type mp;
  std::vector< char > source{{ '\xd3', '\xff', '\xff', '\xff', '\xff', '\xff', '\xff', '\xff', -125 }};
  auto iter = source.cbegin();
  BOOST_CHECK_EQUAL( boost::get< int64_t >( rapidmp::parse_object( iter, source.cend() ) ), -125ll );
}

