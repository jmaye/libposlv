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

/** \file PrimaryGPSReceiverDGPSStaDB.h
    \brief This file defines the PrimaryGPSReceiverDGPSStaDB class, which
           represents the Primary GPS Receiver DGPS Station Database message
           from the Applanix
  */

#ifndef PRIMARYGPSRECEIVERDGPSSTADB_H
#define PRIMARYGPSRECEIVERDGPSSTADB_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "types/StationRecord.h"
#include "exceptions/IOException.h"

/** The class PrimaryGPSReceiverDGPSStaDB represents the Primary GPS Receiver
    DGPS Station Database message from the Applanix.
    \brief Primary GPS Receiver DGPS Station Database message
  */
class PrimaryGPSReceiverDGPSStaDB :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  PrimaryGPSReceiverDGPSStaDB();
  /// Copy constructor
  PrimaryGPSReceiverDGPSStaDB(const PrimaryGPSReceiverDGPSStaDB& other);
  /// Assignement operator
  PrimaryGPSReceiverDGPSStaDB& operator = (const PrimaryGPSReceiverDGPSStaDB& other);
  /// Destructor
  virtual ~PrimaryGPSReceiverDGPSStaDB();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual PrimaryGPSReceiverDGPSStaDB* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 30;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Station records
  StationRecord maStationRecord[10];
  /// Number of stations
  uint32_t mStationNbr;
  /// Prototype for this group
  static const PrimaryGPSReceiverDGPSStaDB mProto;
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
  virtual void read(POSLVGroupRead& stream) throw (IOException);
  /** @}
    */

};

#endif // PRIMARYGPSRECEIVERDGPSSTADB_H
