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

/** \file BaseGPS1ModemStatus.h
    \brief This file defines the BaseGPS1ModemStatus class, which
           represents the Base GPS 1 Modem Status message from the Applanix
  */

#ifndef BASEGPS1MODEMSTATUS_H
#define BASEGPS1MODEMSTATUS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class BaseGPS1ModemStatus represents the Base GPS 1 Modem Status message
    from the Applanix.
    \brief Base GPS 1 Modem Status message
  */
class BaseGPS1ModemStatus :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  BaseGPS1ModemStatus();
  /// Copy constructor
  BaseGPS1ModemStatus(const BaseGPS1ModemStatus& other);
  /// Assignement operator
  BaseGPS1ModemStatus& operator = (const BaseGPS1ModemStatus& other);
  /// Destructor
  virtual ~BaseGPS1ModemStatus();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual BaseGPS1ModemStatus* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 116;
  /// Time/Distance field of the message
  TimeDistance mTimeDistance;
  /// Modem response
  uint8_t mau8ModemResponse[16];
  /// Modem connection status
  uint8_t mau8ConnectionStatus[48];
  /// Numer of redial per disconnect
  uint32_t mNumberOfRedialsPerDisconnect;
  /// Max number of redials per disconnect
  uint32_t mMaximumNumberOfRedialsPerDisconnect;
  /// Number of disconnects
  uint32_t mNumberOfDisconnects;
  /// Data gap length
  uint32_t mDataGapLength;
  /// Maximum data gap length
  uint32_t mMaximumDataGapLength;
  /// Prototype for this group
  static const BaseGPS1ModemStatus mProto;
 /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const ;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /// Reads from the network
  virtual void read(Connection& stream) throw (IOException);
  /// Reads from the network
  virtual void read(POSLVGroupRead& stream) throw (IOException);
  /** @}
    */

};

#endif // BASEGPS1MODEMSTATUS_H
