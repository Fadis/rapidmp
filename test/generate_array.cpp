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
#define BOOST_TEST_MODULE rapidmp_generate_array
#include <boost/test/unit_test.hpp>

#include <rapidmp/generator.hpp>

BOOST_AUTO_TEST_CASE( short_array ) {
  std::vector< uint32_t > data{{ 467832, 672348, 14078901 }};
  std::vector< rapidmp::object_type< std::vector< char >::const_iterator >::type > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( uint32_t value ) { return rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value ) ); } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0x93 ) << *( karma::byte_( 0xce ) << karma::big_dword ), boost::fusion::make_vector( data ) );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( array16 ) {
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
  rapidmp::generate_object( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( array32 ) {
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
  rapidmp::generate_object( oiter, source );
  std::cout << dest.size() << std::endl;
  std::cout << expected.size() << std::endl;
  BOOST_CHECK( boost::equal( expected, dest ) );
}
