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

/** \file POSLVReader.h
    \brief This file defines the POSLVReader class which is an interface for
           reading groups and messages from the Applanix device.
  */

#ifndef POSLVREADER_H
#define POSLVREADER_H

#include <string>

#include <boost/shared_ptr.hpp>

#include "base/BinaryReader.h"

class Packet;

/** The POSLVReader class is an interface for reading groups and messages from
    the Applanix device.
    \brief Applanix POS LV reading interface for groups and messages
  */
class POSLVReader :
  public BinaryReader {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  POSLVReader(const POSLVReader& other);
  /// Assignment operator
  POSLVReader& operator = (const POSLVReader& other);
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  POSLVReader();
  /// Destructor
  virtual ~POSLVReader();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Reads a packet from the Applanix device
  boost::shared_ptr<Packet> readPacket();
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Reads the start string
  std::string readStartString();
  /// Reads the end string
  std::string readEndString();
  /** @}
    */

};

#endif // POSLVREADER_H
