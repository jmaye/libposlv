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

/** \file POSLVData.h
    \brief This file defines the POSLVData class which implements the
           Ethernet Real-Time and Logging Data communication with the POS LV
  */

#ifndef POSLVDATA_H
#define POSLVDATA_H

#include "base/TCPConnectionClient.h"
#include "com/POSLVGroupRead.h"

/** The POSLVData class implements the Ethernet Real-Time and Logging Data
    communication with the Applanix POS LV device.
    \brief Applanix POS LV Ethernet Real-Time and Logging
  */
class POSLVData :
  public TCPConnectionClient,
  public POSLVGroupRead {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the connection with the given parameters
  POSLVData(const std::string& serverIP, uint16_t port,
    double timeout = 2.5);
  /// Destructor
  virtual ~POSLVData();
  /** @}
    */

protected:
  /** \name Protected constructors
    @{
    */
  /// Copy constructor
  POSLVData(const POSLVData& other);
  /// Assignment operator
  POSLVData& operator = (const POSLVData& other);
  /** @}
    */

  /** \name Protected methods
    @{
    */
  /// Reads a buffer of bytes
  virtual void readBuffer(uint8_t* au8Buffer, ssize_t nbBytes);
  /** @}
    */

};

#endif // POSLVDATA_H
