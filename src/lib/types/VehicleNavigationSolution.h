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

/** \file VehicleNavigationSolution.h
    \brief This file defines the VehicleNavigationSolution class, which
           represents the Vehicle Navigation Solution message from the Applanix
  */

#ifndef VEHICLENAVIGATIONSOLUTION_H
#define VEHICLENAVIGATIONSOLUTION_H

#include "types/Group.h"
#include "types/TimeDistance.h"

/** The class VehicleNavigationSolution represents the Vehicle Navigation
    Solution message from the Applanix.
    \brief Vehicle Navigation Solution message
  */
class VehicleNavigationSolution :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  VehicleNavigationSolution();
  /// Copy constructor
  VehicleNavigationSolution(const VehicleNavigationSolution& other);
  /// Assignement operator
  VehicleNavigationSolution& operator =
    (const VehicleNavigationSolution& other);
  /// Destructor
  virtual ~VehicleNavigationSolution();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual VehicleNavigationSolution* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 132;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Latitude [deg]
  double mLatitude;
  /// Longitude [deg]
  double mLongitude;
 /// Altitude [m], ellipsoid height
  double mAltitude;
  /// North velocity [m/s]
  float mNorthVelocity;
  /// East velocity [m/s]
  float mEastVelocity;
  /// Down velocity [m/s]
  float mDownVelocity;
  /// Roll [deg], NED, [-180, 180]
  double mRoll;
  /// Pitch [deg], NED, [-90, 90]
  double mPitch;
  /// Heading [deg], NED, [0, 360]
  double mHeading;
  /// Wander angle [deg], NED, [-180, 180]
  double mWanderAngle;
  /// Track angle [deg], NED, [0, 360]
  float mTrackAngle;
  /// Speed [m/s]
  float mSpeed;
  /// Angular rate longitudinal [deg/s]
  float mAngularRateLong;
  /// Angular rate transverse [deg/s]
  float mAngularRateTrans;
  /// Angular rate down [deg/s]
  float mAngularRateDown;
  /// Acceleration longitudinal [m/s^2]
  float mAccLong;
  /// Acceleration transverse [m/s^2]
  float mAccTrans;
  /// Acceleration down [m/s^2]
  float mAccDown;
  /// Alignment status
  uint8_t mAlignementStatus;
  /// Prototype for this group
  static const VehicleNavigationSolution mProto;
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

#endif // VEHICLENAVIGATIONSOLUTION_H
