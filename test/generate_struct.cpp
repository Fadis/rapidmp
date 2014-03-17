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
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE rapidmp_generate_struct
#include <boost/test/unit_test.hpp>

#include <rapidmp/generator.hpp>

BOOST_AUTO_TEST_CASE( short_struct ) {
  typedef std::pair< uint8_t, float > pair;
  std::vector< pair > data{{ pair( 1, 2.0f ), pair( 3, 4.0f ), pair( 5, 6.0f ) }};
  std::vector< std::pair< rapidmp::object_type< std::vector< char >::const_iterator >::type, rapidmp::object_type< std::vector< char >::const_iterator >::type > > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( const pair &value ) {
    return std::make_pair(
      rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value.first ) ),
      rapidmp::object_type< std::vector< char >::const_iterator >::type( value.second )
    );
  } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0x83 ) << *( karma::byte_ << karma::byte_( 0xca ) << karma::big_bin_float ), data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( struct16 ) {
  typedef std::pair< uint8_t, float > pair;
  std::vector< pair > data( 30 );
  std::fill( data.begin(), data.end(), pair( 1, 2.0f ) );
  std::vector< std::pair< rapidmp::object_type< std::vector< char >::const_iterator >::type, rapidmp::object_type< std::vector< char >::const_iterator >::type > > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( const pair &value ) {
    return std::make_pair(
      rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value.first ) ),
      rapidmp::object_type< std::vector< char >::const_iterator >::type( value.second )
    );
  } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0xde ) << karma::big_word( data.size() ) << *( karma::byte_ << karma::byte_( 0xca ) << karma::big_bin_float ), data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( struct32 ) {
  typedef std::pair< uint8_t, float > pair;
  std::vector< pair > data( 65537 );
  std::fill( data.begin(), data.end(), pair( 1, 2.0f ) );
  std::vector< std::pair< rapidmp::object_type< std::vector< char >::const_iterator >::type, rapidmp::object_type< std::vector< char >::const_iterator >::type > > mparray;
  std::transform( data.begin(), data.end(), std::back_inserter( mparray ), []( const pair &value ) {
    return std::make_pair(
      rapidmp::object_type< std::vector< char >::const_iterator >::type( uint64_t( value.first ) ),
      rapidmp::object_type< std::vector< char >::const_iterator >::type( value.second )
    );
  } );
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( mparray );
  std::vector< char > expected;
  namespace karma = boost::spirit::karma;
  karma::generate( std::back_inserter( expected ), karma::byte_( 0xdf ) << karma::big_dword( data.size() ) << *( karma::byte_ << karma::byte_( 0xca ) << karma::big_bin_float ), data );
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generate_object( oiter, source );
  BOOST_CHECK( boost::equal( expected, dest ) );
}
