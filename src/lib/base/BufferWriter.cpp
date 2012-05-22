/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "base/BufferWriter.h"

#include <cstring>

#include "exceptions/OutOfBoundException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BufferWriter::BufferWriter(size_t reservedSize) :
    mPos(0) {
  mBuffer.reserve(reservedSize);
}

BufferWriter::~BufferWriter() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

size_t BufferWriter::getPos() const {
  return mPos;
}

void BufferWriter::setPos(size_t pos) {
  if (pos >= mBuffer.size())
    throw OutOfBoundException<size_t>(mPos,
      "BufferWriter::setPos(): invalid position");
  mPos = pos;
}

size_t BufferWriter::getBufferSize() const {
  return mBuffer.size();
}

const char* BufferWriter::getBuffer() const {
  return &mBuffer[0];
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void BufferWriter::writeBuffer(const char* buffer, ssize_t numBytes) {
  mBuffer.insert(mBuffer.begin() + mPos, buffer, buffer + numBytes);
  mPos += numBytes;
}
