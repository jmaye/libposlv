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

/** \file SecondaryGPSStatus.h
    \brief This file defines the SecondaryGPSStatus class, which
           represents the Secondary GPS Status message from the Applanix
  */

#ifndef SECONDARYGPSSTATUS_H
#define SECONDARYGPSSTATUS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "types/ChannelStatusData.h"
#include "exceptions/IOException.h"

/** The class SecondaryGPSStatus represents the Secondary GPS Status message
    from the Applanix.
    \brief Secondary GPS Status message
  */
class SecondaryGPSStatus :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  SecondaryGPSStatus();
  /// Copy constructor
  SecondaryGPSStatus(const SecondaryGPSStatus& other);
  /// Assignement operator
  SecondaryGPSStatus& operator = (const SecondaryGPSStatus& other);
  /// Destructor
  virtual ~SecondaryGPSStatus();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual SecondaryGPSStatus* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 76;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Navigation solution status
  int8_t mNavigationSolutionStatus;
  /// Numer of tracked satellites
  uint8_t mNumberOfSVTracked;
  /// Number of bytes for channel status
  uint16_t mChannelStatusByteCount;
  /// Channel status data
  ChannelStatusData maChannelStatusData[64];
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
  /// Number of channels
  uint32_t mChannelNumber;
  /// Prototype for this group
  static const SecondaryGPSStatus mProto;
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

#endif // SECONDARYGPSSTATUS_H
