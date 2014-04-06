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
#include <boost/range/counting_range.hpp>
#include <boost/range/algorithm/for_each.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/fusion/adapted/std_pair.hpp>
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN
#define BOOST_TEST_MODULE rapidmp_generator_event
#include <boost/test/unit_test.hpp>

#include <rapidmp/generator/event.hpp>

BOOST_AUTO_TEST_CASE( v10_short_array ) {
  const std::vector< char > expected{{
    '\x93', '\xce', '\x00', '\x07', '\x23', '\x78', '\xce', '\x00',
    '\x0a', '\x42', '\x5c', '\xce', '\x00', '\xd6', '\xd3', '\xb5'
  }};
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_.begin_array( 3u );
  generator_( 467832u );
  generator_( 672348u );
  generator_( 14078901u );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v10_array16 ) {
  const std::vector< char > expected{{
    '\xdc', '\x00', '\x11', '\x00', '\x01', '\x02', '\x03', '\x04',
    '\x05', '\x06', '\x07', '\x08', '\x09', '\x0A', '\x0B', '\x0C',
    '\x0D', '\x0E', '\x0F', '\x10'
  }};
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_.begin_array( 0x11u );
  boost::for_each( boost::counting_range( 0ull, 0x11ull ), [&]( uint64_t value ) { generator_( value ); } );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v10_array32 ) {
  std::vector< char > expected{{
    '\xdd', '\x00', '\x01', '\x00', '\x01'
  }};
  expected.resize( 65537+5 );
  std::fill( std::next( expected.begin(), 5 ), expected.end(), 6 );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_.begin_array( 65537u );
  boost::for_each( boost::counting_range( 0ull, 65537ull ), [&]( uint64_t ) { generator_( 6u ); } );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v10_short_binary ) {
  const std::vector< char > expected{{
    '\xa3', 'a', 'a', 'a'
  }};
  const std::vector< char > data( std::next( expected.begin(), 1 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::binary< std::vector< char >::const_iterator >( data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v10_binary16 ) {
  std::vector< char > expected{{
    '\xda', '\x00', '\x20'
  }};
  boost::for_each( boost::counting_range( 0ull, 32ull ), [&]( uint64_t ) { expected.push_back( 'a' ); } );
  const std::vector< char > data( std::next( expected.begin(), 3 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::binary< std::vector< char >::const_iterator >( data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v10_binary32 ) {
  std::vector< char > expected{{
    '\xdb', '\x00', '\x01', '\x00', '\x00'
  }};
  boost::for_each( boost::counting_range( 0ull, 65536ull ), [&]( uint64_t ) { expected.push_back( 'a' ); } );
  const std::vector< char > data( std::next( expected.begin(), 5 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::binary< std::vector< char >::const_iterator >( data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_binary8 ) {
  std::vector< char > expected{{
    '\xc4', '\x03', 'a', 'a', 'a'
  }};
  const std::vector< char > data( std::next( expected.begin(), 2 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::binary< std::vector< char >::const_iterator >( data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_binary16 ) {
  std::vector< char > expected{{
    '\xc5', '\x01', '\x00'
  }};
  boost::for_each( boost::counting_range( 0ull, 256ull ), [&]( uint64_t ) { expected.push_back( 'a' ); } );
  const std::vector< char > data( std::next( expected.begin(), 3 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::binary< std::vector< char >::const_iterator >( data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_binary32 ) {
  std::vector< char > expected{{
    '\xc6', '\x00', '\x01', '\x00', '\x00'
  }};
  boost::for_each( boost::counting_range( 0ull, 65536ull ), [&]( uint64_t ) { expected.push_back( 'a' ); } );
  const std::vector< char > data( std::next( expected.begin(), 5 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::binary< std::vector< char >::const_iterator >( data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( bool_true ) {
  std::vector< char > expected{{
    '\xc3'
  }};
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( true );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( bool_false ) {
  std::vector< char > expected{{
    '\xc2'
  }};
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( false );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_fixext1 ) {
  std::vector< char > expected{{
    '\xd4', '\x0e', 'H'
  }};
  const std::vector< char > data( std::next( expected.begin(), 2 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::extension< std::vector< char >::const_iterator >( 14, data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_fixext2 ) {
  std::vector< char > expected{{
    '\xd5', '\x0e', 'H', 'e'
  }};
  const std::vector< char > data( std::next( expected.begin(), 2 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::extension< std::vector< char >::const_iterator >( 14, data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_fixext4 ) {
  std::vector< char > expected{{
    '\xd6', '\x0e', 'H', 'e', 'l', 'l'
  }};
  const std::vector< char > data( std::next( expected.begin(), 2 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::extension< std::vector< char >::const_iterator >( 14, data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_fixext8 ) {
  std::vector< char > expected{{
    '\xd7', '\x0e', 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W'
  }};
  const std::vector< char > data( std::next( expected.begin(), 2 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::extension< std::vector< char >::const_iterator >( 14, data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_fixext16 ) {
  std::vector< char > expected{{
    '\xd8', '\x0e', 'H', 'e', 'l', 'l', 'o', ',', ' ', 'W', 'o', 'r', 'l', 'd', '!', '1', '2', '3'
  }};
  const std::vector< char > data( std::next( expected.begin(), 2 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::extension< std::vector< char >::const_iterator >( 14, data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_extension8 ) {
  std::vector< char > expected{{
    '\xc7', '\x11', '\x0e'
  }};
  expected.resize( 20 );
  std::fill( std::next( expected.begin(), 3 ), expected.end(), 81 );
  const std::vector< char > data( std::next( expected.begin(), 3 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::extension< std::vector< char >::const_iterator >( 14, data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_extension16 ) {
  std::vector< char > expected{{
    '\xc8', '\x01', '\x00', '\x0e'
  }};
  expected.resize( 256+4 );
  std::fill( std::next( expected.begin(), 4 ), expected.end(), 81 );
  const std::vector< char > data( std::next( expected.begin(), 4 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::extension< std::vector< char >::const_iterator >( 14, data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_extension32 ) {
  std::vector< char > expected{{
    '\xc9', '\x00', '\x01', '\x00', '\x00', '\x0e'
  }};
  expected.resize( 65536+6 );
  std::fill( std::next( expected.begin(), 6 ), expected.end(), 81 );
  const std::vector< char > data( std::next( expected.begin(), 6 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::extension< std::vector< char >::const_iterator >( 14, data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( float32 ) {
  const std::vector< char > expected{{
    '\xca', '\x3f', '\x9e', '\x06', '\x4b'
  }};
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( 1.234567f );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( float64 ) {
  const std::vector< char > expected{{
    '\xcb', '\x40', '\x02', '\xc3', '\xf3', '\x4c', '\x93', '\x56', '\x89', 
  }};
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( 2.34567890 );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( int_short ) {
  std::vector< char > expected{{ '\xfd' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( -3 );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( int8 ) {
  std::vector< char > expected{{ '\xd0', '\x90' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( -112 );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( int16 ) {
  std::vector< char > expected{{ '\xd1', '\xea', '\xcf' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( -5425 );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( int32 ) {
  std::vector< char > expected{{ '\xd2', '\xfb', '\x22', '\x22', '\xe7' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( -81648921 );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( int64 ) {
  std::vector< char > expected{{ '\xd3', '\xc9', '\x35', '\xd1', '\x31', '\x36', '\xe6', '\x1c', '\xd2' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( -3948019489015718702ll );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( none ) {
  std::vector< char > expected{{ '\xc0' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_();
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( v10_short_string ) {
  const std::vector< char > expected{{
    '\xa3', 'a', 'a', 'a'
  }};
  const std::vector< char > data( std::next( expected.begin(), 1 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::string< std::vector< char >::const_iterator >( data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v10_string16 ) {
  std::vector< char > expected{{
    '\xda', '\x00', '\x20'
  }};
  boost::for_each( boost::counting_range( 0ull, 32ull ), [&]( uint64_t ) { expected.push_back( 'a' ); } );
  const std::vector< char > data( std::next( expected.begin(), 3 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::string< std::vector< char >::const_iterator >( data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v10_string32 ) {
  std::vector< char > expected{{
    '\xdb', '\x00', '\x01', '\x00', '\x00'
  }};
  boost::for_each( boost::counting_range( 0ull, 65536ull ), [&]( uint64_t ) { expected.push_back( 'a' ); } );
  const std::vector< char > data( std::next( expected.begin(), 5 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::string< std::vector< char >::const_iterator >( data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_short_string ) {
  const std::vector< char > expected{{
    '\xa3', 'a', 'a', 'a'
  }};
  const std::vector< char > data( std::next( expected.begin(), 1 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::string< std::vector< char >::const_iterator >( data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}


BOOST_AUTO_TEST_CASE( v11_string8 ) {
  std::vector< char > expected{{
    '\xd9', '\x20',
  }};
  boost::for_each( boost::counting_range( 0ull, 32ull ), [&]( uint64_t ) { expected.push_back( 'a' ); } );
  const std::vector< char > data( std::next( expected.begin(), 2 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::string< std::vector< char >::const_iterator >( data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_string16 ) {
  std::vector< char > expected{{
    '\xda', '\x01', '\x00'
  }};
  boost::for_each( boost::counting_range( 0ull, 256ull ), [&]( uint64_t ) { expected.push_back( 'a' ); } );
  const std::vector< char > data( std::next( expected.begin(), 3 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::string< std::vector< char >::const_iterator >( data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v11_string32 ) {
  std::vector< char > expected{{
    '\xdb', '\x00', '\x01', '\x00', '\x00'
  }};
  boost::for_each( boost::counting_range( 0ull, 65536ull ), [&]( uint64_t ) { expected.push_back( 'a' ); } );
  const std::vector< char > data( std::next( expected.begin(), 5 ), expected.end() );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_1, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( rapidmp::string< std::vector< char >::const_iterator >( data.cbegin(), data.cend() ) );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v10_short_struct ) {
  const std::vector< char > expected{{
    '\x83', '\x00', '\x01', '\x02', '\x03', '\x04', '\x05'
  }};
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_.begin_struct( 3u );
  generator_( 0u );
  generator_( 1u );
  generator_( 2u );
  generator_( 3u );
  generator_( 4u );
  generator_( 5u );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v10_struct16 ) {
  const std::vector< char > expected{{
    '\xde', '\x00', '\x11',
    '\x00', '\x01', '\x02', '\x03', '\x04', '\x05', '\x06', '\x07',
    '\x08', '\x09', '\x0a', '\x0b', '\x0c', '\x0d', '\x0e', '\x0f',
    '\x10', '\x11', '\x12', '\x13', '\x14', '\x15', '\x16', '\x17',
    '\x18', '\x19', '\x1a', '\x1b', '\x1c', '\x1d', '\x1e', '\x1f',
    '\x20', '\x21'
  }};
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_.begin_struct( 0x11u );
  boost::for_each( boost::counting_range( 0ull, 0x22ull ), [&]( uint64_t value ) { generator_( value ); } );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( v10_struct32 ) {
  std::vector< char > expected{{
    '\xdf', '\x00', '\x01', '\x00', '\x00'
  }};
  expected.resize( 65536*2+5 );
  std::fill( std::next( expected.begin(), 5 ), expected.end(), 6 );
  std::vector< char > result;
  auto oiter = std::back_inserter( result );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_.begin_struct( 65536u );
  boost::for_each( boost::counting_range( 0ull, 65536ull*2 ), [&]( uint64_t ) { generator_( 6u ); } );
  BOOST_CHECK( boost::equal( expected, result ) );
}

BOOST_AUTO_TEST_CASE( uint_short ) {
  std::vector< char > expected{{ '\x10' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( 0x10ull );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( uint8 ) {
  std::vector< char > expected{{ '\xcc', '\xae' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( 0xaeull );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( uint16 ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( uint64_t( 0xabcdull ) );
  std::vector< char > expected{{ '\xcd', '\xab', '\xcd' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( 0xabcdull );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( uint32 ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( uint64_t( 0x12345678ull ) );
  std::vector< char > expected{{ '\xce', '\x12', '\x34', '\x56', '\x78' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( 0x12345678ull );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

BOOST_AUTO_TEST_CASE( uint64 ) {
  rapidmp::object_type< std::vector< char >::const_iterator >::type source( uint64_t( 0x1234567812345678ull ) );
  std::vector< char > expected{{ '\xcf', '\x12', '\x34', '\x56', '\x78', '\x12', '\x34', '\x56', '\x78' }};
  std::vector< char > dest;
  std::back_insert_iterator< std::vector< char > > oiter = std::back_inserter( dest );
  rapidmp::generator< rapidmp::version_1_0, std::back_insert_iterator< std::vector< char > > > generator_( oiter );
  generator_( 0x1234567812345678ull );
  BOOST_CHECK( boost::equal( expected, dest ) );
}

