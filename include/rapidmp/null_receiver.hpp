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

#ifndef RAPIDMP_NULL_RECEIVER_HPP
#define RAPIDMP_NULL_RECEIVER_HPP

#include <cstdint>

#include <rapidmp/config.hpp> 
#include <rapidmp/type.hpp>

namespace rapidmp {
  template< typename Iterator >
  class null_receiver {
  public:
    UMP_FUNCTION void begin_array( size_t ) {}
    UMP_FUNCTION void end_array() {}
    UMP_FUNCTION void begin_struct( size_t ) {}
    UMP_FUNCTION void end_struct() {}
    UMP_FUNCTION void operator()( uint64_t ) {}
    UMP_FUNCTION void operator()( int64_t ) {}
    UMP_FUNCTION void operator()( float ) {}
    UMP_FUNCTION void operator()( double ) {}
    UMP_FUNCTION void operator()() {}
    UMP_FUNCTION void operator()( bool ) {}
    UMP_FUNCTION void operator()( string< Iterator >&& ) {}
    UMP_FUNCTION void operator()( binary< Iterator >&& ) {}
    UMP_FUNCTION void operator()( extension< Iterator >&& ) {}
  };
}

#endif

