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

/** \file POSLVDisplay.h
    \brief This file defines the POSLVDisplay class intended for displaying
           Applanix POS LV data
  */

#ifndef POSLVDISPLAY_H
#define POSLVDISPLAY_H

#include "base/UDPConnectionServer.h"
#include "com/POSLVGroupRead.h"

#include <queue>

/** The POSLVDisplay class implements the UDP communication with the Applanix
    POS LV device, mainly intended for displaying data in a GUI.
    \brief Applanix POS LV display
  */
class POSLVDisplay :
  public UDPConnectionServer,
  public POSLVGroupRead {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the connection with the given parameters
  POSLVDisplay(uint16_t port = 5600, double timeout = 2.5);
  /// Destructor
  virtual ~POSLVDisplay();
  /** @}
    */

protected:
  /** \name Protected constructors
    @{
    */
  /// Copy constructor
  POSLVDisplay(const POSLVDisplay& other);
  /// Assignment operator
  POSLVDisplay& operator = (const POSLVDisplay& other);
  /** @}
    */

  /** \name Protected methods
    @{
    */
  /// Reads a buffer of bytes
  virtual void readBuffer(uint8_t* au8Buffer, ssize_t nbBytes);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Max packet size
  static const size_t mMaxPacketSize = 1500;
  /// Buffer for storing UDP bytes
  std::queue<uint8_t> mBytesBuffer;
  /// Buffer for fetching UDP packets
  uint8_t mPacketsBuffer[mMaxPacketSize];
  /** @}
    */

};

#endif // POSLVDISPLAY_H
