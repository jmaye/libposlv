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

/** \file BinaryLogWriter.h
    \brief This file defines the BinaryLogWriter class intended for writing
           Applanix packets to binary files.
  */

#ifndef BINARYLOGWRITER_H
#define BINARYLOGWRITER_H

#include <iosfwd>

#include "sensor/POSLVWriter.h"

/** The BinaryLogWriter class implements a binary log writer.
    \brief Binary log writer for Applanix packets
  */
class BinaryLogWriter :
  public POSLVWriter {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  BinaryLogWriter(const BinaryLogWriter& other);
  /// Assignment operator
  BinaryLogWriter& operator = (const BinaryLogWriter& other);
  /** @}W
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the object
  BinaryLogWriter(std::ostream& stream);
  /// Destructor
  virtual ~BinaryLogWriter();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Performs write on the stream
  virtual void write(const char* buffer, size_t numBytes);
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Stream object
  std::ostream& mStream;
  /** @}
    */

};

#endif // BINARYLOGWRITER_H
