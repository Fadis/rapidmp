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
#define BOOST_TEST_MODULE rapidmp_generate_string
#include <boost/test/unit_test.hpp>

#include <rapidmp/generator.hpp>

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

