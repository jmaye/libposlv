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

/** \file Auxiliary2GPSStatus.h
    \brief This file defines the Auxiliary2GPSStatus class, which represents the
           Auxiliary 2 GPS Status message from the Applanix
  */

#ifndef AUXILIARY2GPSSTATUS_H
#define AUXILIARY2GPSSTATUS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "types/ChannelStatusData.h"
#include "exceptions/IOException.h"

/** The class Auxiliary2GPSStatus represents the Auxiliary 2 GPS Status message
    from the Applanix.
    \brief Auxiliary 2 GPS Status message
  */
class Auxiliary2GPSStatus :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  Auxiliary2GPSStatus();
  /// Copy constructor
  Auxiliary2GPSStatus(const Auxiliary2GPSStatus& other);
  /// Assignement operator
  Auxiliary2GPSStatus& operator = (const Auxiliary2GPSStatus& other);
  /// Destructor
  virtual ~Auxiliary2GPSStatus();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual Auxiliary2GPSStatus* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 72;
  /// Time/Distance field of the message
  TimeDistance mTimeDistance;
  /// Navigation solution status of the message
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
  /// NMEA message received
  uint16_t mNMEAMessageReceived;
  /// Aux 1/2 in use
  uint8_t mAux12InUse;
  /// Number of channels
  uint32_t mChannelNumber;
  /// Prototype for this group
  static const Auxiliary2GPSStatus mProto;
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

#endif // AUXILIARY2GPSSTATUS_H
