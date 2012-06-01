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

/** \file RawIMUData.h
    \brief This file defines the RawIMUData class, which
           represents the Raw IMU Data message from the Applanix
  */

#ifndef RAWIMUDATA_H
#define RAWIMUDATA_H

#include "types/Group.h"
#include "types/TimeDistance.h"

/** The class RawIMUData represents the Raw IMU Data message from the Applanix.
    \brief Raw IMU Data message
  */
class RawIMUData :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  RawIMUData();
  /// Copy constructor
  RawIMUData(const RawIMUData& other);
  /// Assignement operator
  RawIMUData& operator = (const RawIMUData& other);
  /// Destructor
  virtual ~RawIMUData();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual RawIMUData* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Byte count
  uint16_t mByteCount;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// IMU header
  uint8_t mIMUHeader[6];
  /// Variable message length
  uint16_t mVariableMsgByteCount;
  /// Raw data
  uint8_t* mIMURawData;
  /// Checksum
  uint16_t mDataChecksum;
  /// Prototype for this group
  static const RawIMUData mProto;
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

#endif // RAWIMUDATA_H
