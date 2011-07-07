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

/** \file POSLVEthernet.h
    \brief This file defines the POSLVEthernet class which implements the
           Ethernet Real-Time and Logging Data communication with the POS LV
  */

#ifndef POSLVETHERNET_H
#define POSLVETHERNET_H

#include "base/TCPConnectionClient.h"
#include "com/POSLVGroupRead.h"

/** The POSLVEthernet class implements the Ethernet Real-Time and Logging Data
    communication with the Applanix POS LV device.
    \brief Applanix POS LV Ethernet Real-Time and Logging
  */
class POSLVEthernet :
  public TCPConnectionClient,
  public POSLVGroupRead {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the connection with the given parameters
  POSLVEthernet(const std::string& serverIP, uint16_t port,
    double timeout = 2.5);
  /// Destructor
  virtual ~POSLVEthernet();
  /** @}
    */

protected:
  /** \name Protected constructors
    @{
    */
  /// Copy constructor
  POSLVEthernet(const POSLVEthernet& other);
  /// Assignment operator
  POSLVEthernet& operator = (const POSLVEthernet& other);
  /** @}
    */

  /** \name Protected methods
    @{
    */
  virtual void readBuffer(uint8_t* au8Buffer, ssize_t nbBytes);
  /// Reads the start of a group
  void readStartGroup();
  /// Reads the end of a group
  std::string readEndGroup();
  /** @}
    */

};

#endif // POSLVETHERNET_H
