/*
  Copyright (c) 2014 Arduino.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "RingBuffer.h"
#include <string.h>

#include <Arduino.h>

template <class T>
RingBuffer<T>::RingBuffer( void )
{
    memset( _aucBuffer, 0, SERIAL_BUFFER_SIZE*sizeof(T)) ;
    clear();
}

template <class T>
void RingBuffer<T>::store_char( uint8_t c )
{
  uint32_t mask = noInterrupts();
  int i = nextIndex(_iHead);

  // if we should be storing the received character into the location
  // just before the tail (meaning that the head would advance to the
  // current location of the tail), we're about to overflow the buffer
  // and so we don't write the character or advance the head.
  if ( i != _iTail )
  {
    _aucBuffer[_iHead] = c ;
    _iHead = i ;
  }
  interrupts(mask);
}

template <class T>
void RingBuffer<T>::store( T c )
{
  uint32_t mask = noInterrupts();
  int i = nextIndex(_iHead);
  _aucBuffer[_iHead] = c ;
  _iHead = i ;
  interrupts(mask);
}

template <class T>
void RingBuffer<T>::clear()
{
	_iHead = 0;
	_iTail = 0;
}

template <class T>
int RingBuffer<T>::read_char()
{
	uint32_t mask = noInterrupts();
	if(_iTail == _iHead)
		return -1;

	T value = _aucBuffer[_iTail];
	_iTail = nextIndex(_iTail);

	interrupts(mask);
	return value;
}

template <class T>
int RingBuffer<T>::available()
{
	int delta = (_iHead - _iTail);

	if(delta < 0)
		return SERIAL_BUFFER_SIZE + delta;
	else
		return delta;
}

template <class T>
int RingBuffer<T>::peek()
{
	if(_iTail == _iHead)
		return -1;

	return _aucBuffer[_iTail];
}

template <class T>
int RingBuffer<T>::peekHead(int offset)
{
	if(available() < offset)
		return -1;

	int ix = _iHead - (offset + 1);
	if(ix < 0)
		return _aucBuffer[SERIAL_BUFFER_SIZE + ix];

	return _aucBuffer[ix];
}

template <class T>
int RingBuffer<T>::nextIndex(int index)
{
	return (uint32_t)(index + 1) % (SERIAL_BUFFER_SIZE);
}

template <class T>
bool RingBuffer<T>::isFull()
{
	return (nextIndex(_iHead) == _iTail);
}
