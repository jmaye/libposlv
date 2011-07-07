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

#include "types/VehicleNavigationSolution.h"

#include "com/POSLVGroupRead.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const VehicleNavigationSolution VehicleNavigationSolution::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

VehicleNavigationSolution::VehicleNavigationSolution() :
  Group(1) {
}

VehicleNavigationSolution::VehicleNavigationSolution(const
  VehicleNavigationSolution &other) :
  Group(other) {
}

VehicleNavigationSolution& VehicleNavigationSolution::operator =
  (const VehicleNavigationSolution& other) {
  this->Group::operator=(other);
  return *this;
}

VehicleNavigationSolution::~VehicleNavigationSolution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void VehicleNavigationSolution::read(POSLVGroupRead& stream)
  throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("VehicleNavigationSolution::read(): wrong byte count");

  stream >> mTimeDistance;
  stream >> mLatitude;
  stream >> mLongitude;
  stream >> mAltitude;
  stream >> mNorthVelocity;
  stream >> mEastVelocity;
  stream >> mDownVelocity;
  stream >> mRoll;
  stream >> mPitch;
  stream >> mHeading;
  stream >> mWanderAngle;
  stream >> mTrackAngle;
  stream >> mSpeed;
  stream >> mAngularRateLong;
  stream >> mAngularRateTrans;
  stream >> mAngularRateDown;
  stream >> mAccLong;
  stream >> mAccTrans;
  stream >> mAccDown;
  stream >> mAlignementStatus;

  uint8_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("VehicleNavigationSolution::read(): wrong pad");
}

void VehicleNavigationSolution::read(std::istream& stream) {
}

void VehicleNavigationSolution::write(std::ostream& stream) const {
}

void VehicleNavigationSolution::read(std::ifstream& stream) {
}

void VehicleNavigationSolution::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mLatitude;
  stream << " ";
  stream << mLongitude;
  stream << " ";
  stream << mAltitude;
  stream << " ";
  stream << mNorthVelocity;
  stream << " ";
  stream << mEastVelocity;
  stream << " ";
  stream << mDownVelocity;
  stream << " ";
  stream << mRoll;
  stream << " ";
  stream << mPitch;
  stream << " ";
  stream << mHeading;
  stream << " ";
  stream << mWanderAngle;
  stream << " ";
  stream << mTrackAngle;
  stream << " ";
  stream << mSpeed;
  stream << " ";
  stream << mAngularRateLong;
  stream << " ";
  stream << mAngularRateTrans;
  stream << " ";
  stream << mAngularRateDown;
  stream << " ";
  stream << mAccLong;
  stream << " ";
  stream << mAccTrans;
  stream << " ";
  stream << mAccDown;
  stream << " ";
  stream << (uint16_t)mAlignementStatus;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

VehicleNavigationSolution* VehicleNavigationSolution::clone() const {
  return new VehicleNavigationSolution(*this);
}
