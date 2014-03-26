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

#ifndef RAPIDMP_TYPE_HPP
#define RAPIDMP_TYPE_HPP

#include <cstdint>
#include <vector>
#include <boost/range/iterator_range.hpp>
#include <boost/variant.hpp>
#include <boost/variant/recursive_variant.hpp>

#include <rapidmp/config.hpp>

namespace rapidmp {
  typedef boost::mpl::size_t< 1 > version_1_0;
  typedef boost::mpl::size_t< 2 > version_1_1;

  struct none_type {
    bool operator==( const none_type& ) const { return true; }
    bool operator!=( const none_type& ) const { return false; }
  };
  none_type none;
  template< typename Iterator >
  struct string {
    typedef boost::iterator_range< Iterator > range_type;
    string() {}
    UMP_FUNCTION string( const Iterator &begin, const Iterator &end ) : range( begin, end ) {}
    boost::iterator_range< Iterator > range;
    bool operator==( const string< Iterator > &r ) const { return boost::equal( range, r.range ); }
    bool operator!=( const string< Iterator > &r ) const { return !boost::equal( range, r.range ); }
  };
  template< typename Iterator >
  struct binary {
    typedef boost::iterator_range< Iterator > range_type;
    UMP_FUNCTION binary() {}
    UMP_FUNCTION binary( const Iterator &begin, const Iterator &end ) : range( begin, end ) {}
    boost::iterator_range< Iterator > range;
    bool operator==( const binary< Iterator > &r ) const { return boost::equal( range, r.range ); }
    bool operator!=( const binary< Iterator > &r ) const { return !boost::equal( range, r.range ); }
  };
  template< typename Iterator >
  struct extension {
    typedef boost::iterator_range< Iterator > range_type;
    UMP_FUNCTION extension() {}
    UMP_FUNCTION extension( uint8_t type_, const Iterator &begin, const Iterator &end ) : type( type_ ), range( begin, end ) {}
    uint8_t type;
    boost::iterator_range< Iterator > range;
    bool operator==( const extension< Iterator > &r ) const { return type == r.type && boost::equal( range, r.range ); }
    bool operator!=( const extension< Iterator > &r ) const { return !( type == r.type && boost::equal( range, r.range ) ); }
  };
  template< typename Iterator >
  struct object_type {
    typedef typename boost::make_recursive_variant<
      uint64_t,
      int64_t,
      float,
      double,
      none_type,
      bool,
      string< Iterator >,
      binary< Iterator >,
      extension< Iterator >,
      std::vector< boost::recursive_variant_ >,
      std::vector< std::pair< boost::recursive_variant_, boost::recursive_variant_ > >
    >::type type;
  };
  template< typename Iterator >
  struct array_type {
    typedef std::vector<
      typename object_type< Iterator >::type
    > type;
  };
  template< typename Iterator >
  struct struct_type {
    typedef std::vector<
      std::pair<
        typename object_type< Iterator >::type,
        typename object_type< Iterator >::type
      >
    > type;
  };
}

#endif

