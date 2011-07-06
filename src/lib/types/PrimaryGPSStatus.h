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

/** \file PrimaryGPSStatus.h
    \brief This file defines the PrimaryGPSStatus class, which
           represents the Primary GPS Status message from the Applanix
  */

#ifndef PRIMARYGPSSTATUS_H
#define PRIMARYGPSSTATUS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "types/ChannelStatusData.h"
#include "exceptions/IOException.h"

/** The class PrimaryGPSStatus represents the Primary GPS Status message
    from the Applanix.
    \brief Primary GPS Status message
  */
class PrimaryGPSStatus :
  public Group {
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  PrimaryGPSStatus();
  /// Copy constructor
  PrimaryGPSStatus(const PrimaryGPSStatus& other);
  /// Assignement operator
  PrimaryGPSStatus& operator = (const PrimaryGPSStatus& other);
  /// Destructor
  virtual ~PrimaryGPSStatus();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual PrimaryGPSStatus* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 676;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Navigation solution status
  int8_t mNavigationSolutionStatus;
  /// Numer of tracked satellites
  uint8_t mNumberOfSVTracked;
  /// Number of bytes for channel status
  uint16_t mChannelStatusByteCount;
  /// Channel status data
  ChannelStatusData maChannelStatusData[12];
  /// HDOP
  float mHDOP;
  /// VDOP
  float mVDOP;
  /// DGPS correction latency
  float mDGPSCorrectionLatency;
  /// DGPS reference ID
  uint16_t mDGPSReferenceID;
  /// GPS/UTC week number
  uint32_t mGPSUTCWeekNumber;
  /// GPS time offset
  double mGPSUTCTimeOffset;
  /// Navigation message latency
  float mGPSNavigationMessageLatency;
  /// Geoidal separation
  float mGeoidalSeparation;
  /// Receiver type
  uint16_t mGPSReceiverType;
  /// GPS status
  uint32_t mGPSStatus;
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
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Prototype for this group
  static const PrimaryGPSStatus mProto;
  /** @}
    */

};

#endif // PRIMARYGPSSTATUS_H
