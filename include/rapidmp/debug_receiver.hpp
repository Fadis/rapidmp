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

#ifndef RAPIDMP_DEBUG_RECEIVER_HPP
#define RAPIDMP_DEBUG_RECEIVER_HPP

#include <cstdint>

#include <rapidmp/config.hpp> 
#include <rapidmp/type.hpp>

namespace rapidmp {
  template< typename Iterator >
  class debug_receiver {
  public:
    UMP_FUNCTION void begin_array( size_t ) {
      log.push_back( '[' );
    }
    UMP_FUNCTION void end_array() {
      log.push_back( ']' );
    }
    UMP_FUNCTION void begin_pair() {
      log.push_back( '(' );
    }
    UMP_FUNCTION void end_pair() {
      log.push_back( ')' );
    }
    UMP_FUNCTION void begin_struct( size_t ) {
      log.push_back( '{' );
    }
    UMP_FUNCTION void end_struct() {
      log.push_back( '}' );
    }
    UMP_FUNCTION void operator()( uint64_t ) {
      log.push_back( 'u' );
    }
    UMP_FUNCTION void operator()( int64_t ) {
      log.push_back( 'i' );
    }
    UMP_FUNCTION void operator()( float ) {
      log.push_back( 'f' );
    }
    UMP_FUNCTION void operator()( double ) {
      log.push_back( 'd' );
    }
    UMP_FUNCTION void operator()( none_type ) {
      log.push_back( 'n' );
    }
    UMP_FUNCTION void operator()( bool ) {
      log.push_back( 'b' );
    }
    UMP_FUNCTION void operator()( string< Iterator >&& ) {
      log.push_back( 'S' );
    }
    UMP_FUNCTION void operator()( binary< Iterator >&& ) {
      log.push_back( 'B' );
    }
    UMP_FUNCTION void operator()( extension< Iterator >&& ) {
      log.push_back( 'E' );
    }
    const std::string get_log() const {
      return log;
    }
  private:
    std::string log;
  };
}

#endif

