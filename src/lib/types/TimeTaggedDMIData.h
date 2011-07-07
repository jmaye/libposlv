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

/** \file TimeTaggedDMIData.h
    \brief This file defines the TimeTaggedDMIData class, which
           represents the Time Tagged DMI Data message from the Applanix
  */

#ifndef TIMETAGGEDDMIDATA_H
#define TIMETAGGEDDMIDATA_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class TimeTaggedDMIData represents the Time Tagged DMI Data message from
    the Applanix.
    \brief Time Tagged DMI Data message
  */
class TimeTaggedDMIData :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  TimeTaggedDMIData();
  /// Copy constructor
  TimeTaggedDMIData(const TimeTaggedDMIData& other);
  /// Assignement operator
  TimeTaggedDMIData& operator = (const TimeTaggedDMIData& other);
  /// Destructor
  virtual ~TimeTaggedDMIData();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual TimeTaggedDMIData* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 52;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Signed distance traveled
  double mSignedDistanceTraveled;
  /// Unsigned distance traveled
  double mUnsignedDistanceTraveled;
  /// DMI scale factor
  uint16_t mDMIScaleFactor;
  /// Data status
  uint8_t mDataStatus;
  /// DMI type
  uint8_t mDMIType;
  /// DMI data rate
  uint8_t mDMIDataRate;
  /// Prototype for this group
  static const TimeTaggedDMIData mProto;
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

#endif // TIMETAGGEDDMIDATA_H
