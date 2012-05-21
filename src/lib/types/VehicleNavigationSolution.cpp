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
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("VehicleNavigationSolution::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTimeDistance;
  mChecksum += mTimeDistance.mChecksum;
  stream >> mLatitude;
  mChecksum += ((uint16_t*)&mLatitude)[0];
  mChecksum += ((uint16_t*)&mLatitude)[1];
  mChecksum += ((uint16_t*)&mLatitude)[2];
  mChecksum += ((uint16_t*)&mLatitude)[3];
  stream >> mLongitude;
  mChecksum += ((uint16_t*)&mLongitude)[0];
  mChecksum += ((uint16_t*)&mLongitude)[1];
  mChecksum += ((uint16_t*)&mLongitude)[2];
  mChecksum += ((uint16_t*)&mLongitude)[3];
  stream >> mAltitude;
  mChecksum += ((uint16_t*)&mAltitude)[0];
  mChecksum += ((uint16_t*)&mAltitude)[1];
  mChecksum += ((uint16_t*)&mAltitude)[2];
  mChecksum += ((uint16_t*)&mAltitude)[3];
  stream >> mNorthVelocity;
  mChecksum += ((uint16_t*)&mNorthVelocity)[0];
  mChecksum += ((uint16_t*)&mNorthVelocity)[1];
  stream >> mEastVelocity;
  mChecksum += ((uint16_t*)&mEastVelocity)[0];
  mChecksum += ((uint16_t*)&mEastVelocity)[1];
  stream >> mDownVelocity;
  mChecksum += ((uint16_t*)&mDownVelocity)[0];
  mChecksum += ((uint16_t*)&mDownVelocity)[1];
  stream >> mRoll;
  mChecksum += ((uint16_t*)&mRoll)[0];
  mChecksum += ((uint16_t*)&mRoll)[1];
  mChecksum += ((uint16_t*)&mRoll)[2];
  mChecksum += ((uint16_t*)&mRoll)[3];
  stream >> mPitch;
  mChecksum += ((uint16_t*)&mPitch)[0];
  mChecksum += ((uint16_t*)&mPitch)[1];
  mChecksum += ((uint16_t*)&mPitch)[2];
  mChecksum += ((uint16_t*)&mPitch)[3];
  stream >> mHeading;
  mChecksum += ((uint16_t*)&mHeading)[0];
  mChecksum += ((uint16_t*)&mHeading)[1];
  mChecksum += ((uint16_t*)&mHeading)[2];
  mChecksum += ((uint16_t*)&mHeading)[3];
  stream >> mWanderAngle;
  mChecksum += ((uint16_t*)&mWanderAngle)[0];
  mChecksum += ((uint16_t*)&mWanderAngle)[1];
  mChecksum += ((uint16_t*)&mWanderAngle)[2];
  mChecksum += ((uint16_t*)&mWanderAngle)[3];
  stream >> mTrackAngle;
  mChecksum += ((uint16_t*)&mTrackAngle)[0];
  mChecksum += ((uint16_t*)&mTrackAngle)[1];
  stream >> mSpeed;
  mChecksum += ((uint16_t*)&mSpeed)[0];
  mChecksum += ((uint16_t*)&mSpeed)[1];
  stream >> mAngularRateLong;
  mChecksum += ((uint16_t*)&mAngularRateLong)[0];
  mChecksum += ((uint16_t*)&mAngularRateLong)[1];
  stream >> mAngularRateTrans;
  mChecksum += ((uint16_t*)&mAngularRateTrans)[0];
  mChecksum += ((uint16_t*)&mAngularRateTrans)[1];
  stream >> mAngularRateDown;
  mChecksum += ((uint16_t*)&mAngularRateDown)[0];
  mChecksum += ((uint16_t*)&mAngularRateDown)[1];
  stream >> mAccLong;
  mChecksum += ((uint16_t*)&mAccLong)[0];
  mChecksum += ((uint16_t*)&mAccLong)[1];
  stream >> mAccTrans;
  mChecksum += ((uint16_t*)&mAccTrans)[0];
  mChecksum += ((uint16_t*)&mAccTrans)[1];
  stream >> mAccDown;
  mChecksum += ((uint16_t*)&mAccDown)[0];
  mChecksum += ((uint16_t*)&mAccDown)[1];
  stream >> mAlignementStatus;
  uint8_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("VehicleNavigationSolution::read(): wrong pad");
  mChecksum += pad << 8 | mAlignementStatus;
  mChecksum = 65536 - mChecksum;
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
