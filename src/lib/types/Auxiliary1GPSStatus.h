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

/** \file Auxiliary1GPSStatus.h
    \brief This file defines the Auxiliary1GPSStatus class, which
           represents the Auxiliary 1 GPS Status message from the Applanix
  */

#ifndef AUXILIARY1GPSSTATUS_H
#define AUXILIARY1GPSSTATUS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "types/ChannelStatusData.h"

/** The class Auxiliary1GPSStatus represents the Auxiliary 1 GPS Status message
    from the Applanix.
    \brief Auxiliary 1 GPS Status message
  */
class Auxiliary1GPSStatus :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  Auxiliary1GPSStatus();
  /// Copy constructor
  Auxiliary1GPSStatus(const Auxiliary1GPSStatus& other);
  /// Assignement operator
  Auxiliary1GPSStatus& operator = (const Auxiliary1GPSStatus& other);
  /// Destructor
  virtual ~Auxiliary1GPSStatus();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual Auxiliary1GPSStatus* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 72;
  /// Read byte count
  uint16_t mReadByteCount;
  /// Time/Distance field of the message
  TimeDistance mTimeDistance;
  /// Navigation solution status of the message
  int8_t mNavigationSolutionStatus;
  /// Numer of tracked satellites
  uint8_t mNumberOfSVTracked;
  /// Number of bytes for channel status
  uint16_t mChannelStatusByteCount;
  /// Channel status data
  ChannelStatusData* mChannelStatusData;
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
  /// Prototype of this group
  static const Auxiliary1GPSStatus mProto;
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
  virtual void read(BinaryReader& stream);
  /// Writes to the network
  virtual void write(BinaryWriter& stream) const;
  /** @}
    */

};

#endif // AUXILIARY1GPSSTATUS_H
