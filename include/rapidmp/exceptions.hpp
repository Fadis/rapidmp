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

#ifndef RAPIDMP_EXCEPTIONS_HPP
#define RAPIDMP_EXCEPTIONS_HPP

#include <exception>

namespace rapidmp {
  struct unexpected_end : public std::invalid_argument {
    unexpected_end() : std::invalid_argument( "rapidmp: unexpected end" ) {}
  };
  struct invalid_float : public std::invalid_argument {
    invalid_float() : std::invalid_argument( "rapidmp: invalid float" ) {}
  };
  struct invalid_object : public std::invalid_argument {
    invalid_object() : std::invalid_argument( "rapidmp: invalid object" ) {}
  };
  struct too_big : public std::out_of_range {
    too_big() : std::out_of_range( "rapidmp: too big" ) {}
  };
  struct overflow : public std::overflow_error {
    overflow() : std::overflow_error( "rapidmp: overflow" ) {}
  };
}

#endif

