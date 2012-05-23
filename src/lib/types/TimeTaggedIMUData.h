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

/** \file TimeTaggedIMUData.h
    \brief This file defines the TimeTaggedIMUData class, which
           represents the Time Tagged IMU Data message from the Applanix
  */

#ifndef TIMETAGGEDIMUDATA_H
#define TIMETAGGEDIMUDATA_H

#include "types/Group.h"
#include "types/TimeDistance.h"

/** The class TimeTaggedIMUData represents the Time Tagged IMU Data message from
    the Applanix.
    \brief Time Tagged IMU Data message
  */
class TimeTaggedIMUData :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  TimeTaggedIMUData();
  /// Copy constructor
  TimeTaggedIMUData(const TimeTaggedIMUData& other);
  /// Assignement operator
  TimeTaggedIMUData& operator = (const TimeTaggedIMUData& other);
  /// Destructor
  virtual ~TimeTaggedIMUData();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual TimeTaggedIMUData* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 60;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// X incremental velocity
  int32_t mXIncrementalVelocity;
  /// Y incremental velocity
  int32_t mYIncrementalVelocity;
  /// Z incremental velocity
  int32_t mZIncrementalVelocity;
  /// X incremental angle
  int32_t mXIncrementalAngle;
  /// Y incremental angle
  int32_t mYIncrementalAngle;
  /// Z incremental angle
  int32_t mZIncrementalAngle;
  /// Data status
  uint8_t mDataStatus;
  /// IMU type
  uint8_t mIMUType;
  /// IMU data rate
  uint8_t mPOSIMUDataRate;
  /// IMU status
  uint16_t mIMUStatus;
  /// Prototype for this group
  static const TimeTaggedIMUData mProto;
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

#endif // TIMETAGGEDIMUDATA_H
