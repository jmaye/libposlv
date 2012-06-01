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

/** \file BinaryLogReader.h
    \brief This file defines the BinaryLogReader class intended for reading
           Applanix packets from binary files.
  */

#ifndef BINARYLOGREADER_H
#define BINARYLOGREADER_H

#include <iosfwd>

#include "sensor/POSLVReader.h"

/** The BinaryLogReader class implements a binary log reader.
    \brief Binary log reader for Applanix packets
  */
class BinaryLogReader :
  public POSLVReader {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  BinaryLogReader(const BinaryLogReader& other);
  /// Assignment operator
  BinaryLogReader& operator = (const BinaryLogReader& other);
  /** @}W
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the object
  BinaryLogReader(std::istream& stream);
  /// Destructor
  virtual ~BinaryLogReader();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Performs read on the stream
  virtual void read(char* buffer, size_t numBytes);
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Stream object
  std::istream& mStream;
  /** @}
    */

};

#endif // BINARYLOGREADER_H
