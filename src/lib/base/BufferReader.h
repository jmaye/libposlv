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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file BufferReader.h
    \brief This file defines the BufferReader class which allows reading binary
           data from a byte buffer.
  */

#ifndef BUFFERREADER_H
#define BUFFERREADER_H

#include <vector>

#include "base/BinaryReader.h"

/** The BufferReader class allows for reading binary data from a byte buffer.
    \brief Buffer reader
  */
class BufferReader :
  public BinaryReader {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  BufferReader(const BufferReader& other);
  /// Assignment operator
  BufferReader& operator = (const BufferReader& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs object
  BufferReader(const char* buffer, size_t size);
  /// Destructor
  virtual ~BufferReader();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Get the position in the buffer
  size_t getPos() const;
  /// Set the position in the buffer
  void setPos(size_t pos);
  /// Returns the buffer size
  size_t getBufferSize() const;
  /// Returns the remaining size to read
  size_t getReadLeft() const;
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Reads a buffer of byte
  virtual void readBuffer(char* buffer, ssize_t numBytes);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Associated byte array
  std::vector<char> mBuffer;
  /// Position of the reader
  size_t mPos;
  /** @}
    */

};

#endif // BUFFERREADER_H
