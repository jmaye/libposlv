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

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

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
    VehicleNavigationSolution& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mLatitude(other.mLatitude),
    mLongitude(other.mLongitude),
    mAltitude(other.mAltitude),
    mNorthVelocity(other.mNorthVelocity),
    mEastVelocity(other.mEastVelocity),
    mDownVelocity(other.mDownVelocity),
    mRoll(other.mRoll),
    mPitch(other.mPitch),
    mHeading(other.mHeading),
    mWanderAngle(other.mWanderAngle),
    mTrackAngle(other.mTrackAngle),
    mSpeed(other.mSpeed),
    mAngularRateLong(other.mAngularRateLong),
    mAngularRateTrans(other.mAngularRateTrans),
    mAngularRateDown(other.mAngularRateDown),
    mAccLong(other.mAccLong),
    mAccTrans(other.mAccTrans),
    mAccDown(other.mAccDown),
    mAlignementStatus(other.mAlignementStatus) {
}

VehicleNavigationSolution& VehicleNavigationSolution::operator =
    (const VehicleNavigationSolution& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    mLatitude = other.mLatitude;
    mLongitude = other.mLongitude;
    mAltitude = other.mAltitude;
    mNorthVelocity = other.mNorthVelocity;
    mEastVelocity = other.mEastVelocity;
    mDownVelocity = other.mDownVelocity;
    mRoll = other.mRoll;
    mPitch = other.mPitch;
    mHeading = other.mHeading;
    mWanderAngle = other.mWanderAngle;
    mTrackAngle = other.mTrackAngle;
    mSpeed = other.mSpeed;
    mAngularRateLong = other.mAngularRateLong;
    mAngularRateTrans = other.mAngularRateTrans;
    mAngularRateDown = other.mAngularRateDown;
    mAccLong = other.mAccLong;
    mAccTrans = other.mAccTrans;
    mAccDown = other.mAccDown;
    mAlignementStatus = other.mAlignementStatus;
  }
  return *this;
}

VehicleNavigationSolution::~VehicleNavigationSolution() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void VehicleNavigationSolution::read(BinaryReader& stream) {
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
}

void VehicleNavigationSolution::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTimeDistance;
  stream << mLatitude;
  stream << mLongitude;
  stream << mAltitude;
  stream << mNorthVelocity;
  stream << mEastVelocity;
  stream << mDownVelocity;
  stream << mRoll;
  stream << mPitch;
  stream << mHeading;
  stream << mWanderAngle;
  stream << mTrackAngle;
  stream << mSpeed;
  stream << mAngularRateLong;
  stream << mAngularRateTrans;
  stream << mAngularRateDown;
  stream << mAccLong;
  stream << mAccTrans;
  stream << mAccDown;
  stream << mAlignementStatus;
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
  return new VehicleNavigationSolution(mProto);
}
