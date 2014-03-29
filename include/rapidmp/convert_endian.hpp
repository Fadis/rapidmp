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

#ifndef RAPIDMP_CONVERT_ENDIAN_HPP
#define RAPIDMP_CONVERT_ENDIAN_HPP

#include <cstdint>
#include <boost/spirit/include/qi.hpp>

#include <rapidmp/config.hpp> 
#include <rapidmp/type.hpp>
#include <rapidmp/exceptions.hpp>

namespace rapidmp {
  template< typename Length >
  UMP_FUNCTION decltype( boost::spirit::qi::byte_ )
  get_qi_rule_for_the_integer(
    typename boost::enable_if< boost::mpl::equal_to< Length, boost::mpl::size_t< 1 > > >::type* = 0
  ) {
    return boost::spirit::qi::byte_;
  }

  template< typename Length >
  UMP_FUNCTION decltype( boost::spirit::qi::big_word )
  get_qi_rule_for_the_integer(
    typename boost::enable_if< boost::mpl::equal_to< Length, boost::mpl::size_t< 2 > > >::type* = 0
  ) {
    return boost::spirit::qi::big_word;
  }

  template< typename Length >
  UMP_FUNCTION decltype( boost::spirit::qi::big_dword )
  get_qi_rule_for_the_integer(
    typename boost::enable_if< boost::mpl::equal_to< Length, boost::mpl::size_t< 4 > > >::type* = 0
  ) {
    return boost::spirit::qi::big_dword;
  }
  
  template< typename Length >
  UMP_FUNCTION decltype( boost::spirit::qi::big_qword )
  get_qi_rule_for_the_integer(
    typename boost::enable_if< boost::mpl::equal_to< Length, boost::mpl::size_t< 8 > > >::type* = 0
  ) {
    return boost::spirit::qi::big_qword;
  }

  template< typename Length, typename Iterator >
  UMP_FUNCTION uint8_t convert_endian(
    Iterator &iter, const Iterator &end,
    typename boost::enable_if< boost::mpl::equal_to< Length, boost::mpl::size_t< 1 > > >::type* = 0
  ) {
    if( iter == end )
      throw unexpected_end();
    uint8_t value = *iter;
    ++iter;
    return value;
  }

  template< typename Length, typename Iterator >
  UMP_FUNCTION typename boost::uint_t< Length::value * 8u >::exact convert_endian(
    Iterator &iter, const Iterator &end,
    typename boost::enable_if< boost::mpl::not_equal_to< Length, boost::mpl::size_t< 1 > > >::type* = 0
  ) {
    namespace qi = boost::spirit::qi;
    typename boost::uint_t< Length::value * 8u >::exact result;
    static const auto rule = get_qi_rule_for_the_integer< Length >();
    if( !qi::parse( iter, end, rule, result ) )
      throw unexpected_end();
    return result;
  }
}

#endif

