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

/** \file POSLVWriter.h
    \brief This file defines the POSLVWriter class which is an interface
           for all messages writing to the Applanix device.
  */

#ifndef POSLVWRITER_H
#define POSLVWRITER_H

#include <memory>

#include "base/BinaryWriter.h"

class Packet;

/** The POSLVWriter class is an interface for all messages writing to the
    Applanix device.
    \brief Applanix POS LV writing interface for messages
  */
class POSLVWriter :
  public BinaryWriter {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  POSLVWriter(const POSLVWriter& other);
  /// Assignment operator
  POSLVWriter& operator = (const POSLVWriter& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  POSLVWriter();
  /// Destructor
  virtual ~POSLVWriter();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Writes a packet to the Applanix device
  void writePacket(std::shared_ptr<Packet> packet);
  /** @}
    */

protected:

};

#endif // POSLVWRITER
