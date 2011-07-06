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

/** \file VersionStatistics.h
    \brief This file defines the VersionStatistics class, which
           represents the Version Statistics message from the Applanix
  */

#ifndef VERSIONSTATISTICS_H
#define VERSIONSTATISTICS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class VersionStatistics represents the Version Statistics message from
    the Applanix.
    \brief Version Statistics message
  */
class VersionStatistics :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  VersionStatistics();
  /// Copy constructor
  VersionStatistics(const VersionStatistics& other);
  /// Assignement operator
  VersionStatistics& operator = (const VersionStatistics& other);
  /// Destructor
  virtual ~VersionStatistics();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual VersionStatistics* clone() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 332;
  /// Time/Distance field of the message
  TimeDistance mTimeDistance;
  /// Version of the stystem
  uint8_t mau8SystemVersion[120];
  /// Primary GPS version
  uint8_t mau8PrimaryGPSVersion[80];
  /// Secondary GPS version
  uint8_t mau8SecondaryGPSversion[80];
  /// Total hours of use
  float mTotalHours;
  /// Number of runs
  uint32_t mNumberOfRuns;
  /// Average length of run
  float mAverageLengthOfRun;
  /// Longest run
  float mLongestRun;
  /// Current run
  float mCurrentRun;
  /// Prototype for this group
  static const VersionStatistics mProto;
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

};

#endif // VERSIONSTATISTICS_H
