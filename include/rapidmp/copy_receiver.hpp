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

#ifndef RAPIDMP_COPY_RECEIVER_HPP
#define RAPIDMP_COPY_RECEIVER_HPP

#include <cstdint>

#include <rapidmp/config.hpp> 
#include <rapidmp/type.hpp>
#include <rapidmp/generator/event.hpp>

namespace rapidmp {
  template< typename Version, typename OutputIterator >
  class copy_receiver {
  public:
    copy_receiver( OutputIterator &output ) : generator_( output ) {}
    UMP_FUNCTION void begin_array( size_t size ) {
      generator_.begin_array( size );
    }
    UMP_FUNCTION void end_array() {
    }
    UMP_FUNCTION void begin_pair() {
    }
    UMP_FUNCTION void end_pair() {
    }
    UMP_FUNCTION void begin_struct( size_t size ) {
      generator_.begin_struct( size );
    }
    UMP_FUNCTION void end_struct() {
    }
    UMP_FUNCTION void operator()( uint64_t value ) {
      generator_( value );
    }
    UMP_FUNCTION void operator()( int64_t value ) {
      generator_( value );
    }
    UMP_FUNCTION void operator()( float value ) {
      generator_( value );
    }
    UMP_FUNCTION void operator()( double value ) {
      generator_( value );
    }
    UMP_FUNCTION void operator()( const none_type& ) {
      generator_();
    }
    UMP_FUNCTION void operator()() {
      generator_();
    }
    UMP_FUNCTION void operator()( bool value ) {
      generator_( value );
    }
    template< typename InputIterator >
    UMP_FUNCTION void operator()( string< InputIterator > &&value ) {
      generator_( value );
    }
    template< typename InputIterator >
    UMP_FUNCTION void operator()( binary< InputIterator > &&value ) {
      generator_( value );
    }
    template< typename InputIterator >
    UMP_FUNCTION void operator()( extension< InputIterator > &&value ) {
      generator_( value );
    }
  private:
    generator< Version, OutputIterator > generator_;
  };
}

#endif

