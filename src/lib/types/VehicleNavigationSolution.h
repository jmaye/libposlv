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
  /// Latitude
  double mLatitude;
  /// Longitude
  double mLongitude;
  /// Altitude
  double mAltitude;
  /// North velocity
  float mNorthVelocity;
  /// East velocity
  float mEastVelocity;
  /// Down velocity
  float mDownVelocity;
  /// Roll
  double mRoll;
  /// Pitch
  double mPitch;
  /// Heading
  double mHeading;
  /// Wander angel
  double mWanderAngle;
  /// Track angle
  float mTrackAngle;
  /// Speed
  float mSpeed;
  /// Angular rate longitude
  float mAngularRateLong;
  /// Angular rate transverse
  float mAngularRateTrans;
  /// Angular rate down
  float mAngularRateDown;
  /// Acceleration longitude
  float mAccLong;
  /// Acceleration transverse
  float mAccTrans;
  /// Acceleration down
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
  /** @}
    */

};

#endif // VEHICLENAVIGATIONSOLUTION_H
