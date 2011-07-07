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

/** \file VehicleNavigationPerformance.h
    \brief This file defines the VehicleNavigationPerformance class, which
           represents the Vehicle Navigation Performance message from the
           Applanix
  */

#ifndef VEHICLENAVIGATIONPERFORMANCE_H
#define VEHICLENAVIGATIONPERFORMANCE_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class VehicleNavigationPerformance represents the Vehicle Navigation
    Performance message from the Applanix.
    \brief Vehicle Navigation Performance message
  */
class VehicleNavigationPerformance :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  VehicleNavigationPerformance();
  /// Copy constructor
  VehicleNavigationPerformance(const VehicleNavigationPerformance& other);
  /// Assignement operator
  VehicleNavigationPerformance& operator = (const VehicleNavigationPerformance& other);
  /// Destructor
  virtual ~VehicleNavigationPerformance();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual VehicleNavigationPerformance* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 80;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// North position RMS error
  float mNorthPositionRMSError;
  /// East position RMS error
  float mEastPositionRMSError;
  /// Down position RMS error
  float mDownPositionRMSError;
  /// North velocity RMS error
  float mNorthVelocityRMSError;
  /// East velocity RMS error
  float mEastVelocityRMSError;
  /// Down velocity RMS error
  float mDownVelocityRMSError;
  /// Roll RMS error
  float mRollRMSError;
  /// Pitch RMS error
  float mPitchRMSError;
  /// Heading RMS error
  float mHeadingRMSError;
  /// Error ellipsoid semi major
  float mErrorEllipsoidSemiMajor;
  /// Error ellipsoid semi minor
  float mErrorEllipsoidSemiMinor;
  /// Error ellipsoid orientation
  float mErrorEllipsoidOrientation;
  /// Prototype for this group
  static const VehicleNavigationPerformance mProto;
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

#endif // VEHICLENAVIGATIONPERFORMANCE_H
