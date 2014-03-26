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
#define BOOST_TEST_MODULE rapidmp_generate_int
#include <boost/test/unit_test.hpp>

#include <rapidmp/generator.hpp>

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

