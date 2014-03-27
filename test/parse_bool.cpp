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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE rapidmp_parser_bool
#include <boost/test/unit_test.hpp>

#include <rapidmp/parser.hpp>

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

