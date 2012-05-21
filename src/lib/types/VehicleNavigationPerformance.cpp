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

#include "types/VehicleNavigationPerformance.h"

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const VehicleNavigationPerformance VehicleNavigationPerformance::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

VehicleNavigationPerformance::VehicleNavigationPerformance() :
    Group(2) {
}

VehicleNavigationPerformance::VehicleNavigationPerformance(const
    VehicleNavigationPerformance& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mNorthPositionRMSError(other.mNorthPositionRMSError),
    mEastPositionRMSError(other.mEastPositionRMSError),
    mDownPositionRMSError(other.mDownPositionRMSError),
    mNorthVelocityRMSError(other.mNorthVelocityRMSError),
    mEastVelocityRMSError(other.mEastVelocityRMSError),
    mDownVelocityRMSError(other.mDownVelocityRMSError),
    mRollRMSError(other.mRollRMSError),
    mPitchRMSError(other.mPitchRMSError),
    mHeadingRMSError(other.mHeadingRMSError),
    mErrorEllipsoidSemiMajor(other.mErrorEllipsoidSemiMajor),
    mErrorEllipsoidSemiMinor(other.mErrorEllipsoidSemiMinor),
    mErrorEllipsoidOrientation(other.mErrorEllipsoidOrientation) {
}

VehicleNavigationPerformance& VehicleNavigationPerformance::operator =
    (const VehicleNavigationPerformance& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    mNorthPositionRMSError = other.mNorthPositionRMSError;
    mEastPositionRMSError = other.mEastPositionRMSError;
    mDownPositionRMSError = other.mDownPositionRMSError;
    mNorthVelocityRMSError = other.mNorthVelocityRMSError;
    mEastVelocityRMSError = other.mEastVelocityRMSError;
    mDownVelocityRMSError = other.mDownVelocityRMSError;
    mRollRMSError = other.mRollRMSError;
    mPitchRMSError = other.mPitchRMSError;
    mHeadingRMSError = other.mHeadingRMSError;
    mErrorEllipsoidSemiMajor = other.mErrorEllipsoidSemiMajor;
    mErrorEllipsoidSemiMinor = other.mErrorEllipsoidSemiMinor;
    mErrorEllipsoidOrientation = other.mErrorEllipsoidOrientation;
  }
  return *this;
}

VehicleNavigationPerformance::~VehicleNavigationPerformance() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void VehicleNavigationPerformance::read(BinaryReader& stream) {
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("VehicleNavigationPerformance::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTimeDistance;
  mChecksum += mTimeDistance.mChecksum;
  stream >> mNorthPositionRMSError;
  mChecksum += ((uint16_t*)&mNorthPositionRMSError)[0];
  mChecksum += ((uint16_t*)&mNorthPositionRMSError)[1];
  stream >> mEastPositionRMSError;
  mChecksum += ((uint16_t*)&mEastPositionRMSError)[0];
  mChecksum += ((uint16_t*)&mEastPositionRMSError)[1];
  stream >> mDownPositionRMSError;
  mChecksum += ((uint16_t*)&mDownPositionRMSError)[0];
  mChecksum += ((uint16_t*)&mDownPositionRMSError)[1];
  stream >> mNorthVelocityRMSError;
  mChecksum += ((uint16_t*)&mNorthVelocityRMSError)[0];
  mChecksum += ((uint16_t*)&mNorthVelocityRMSError)[1];
  stream >> mEastVelocityRMSError;
  mChecksum += ((uint16_t*)&mEastVelocityRMSError)[0];
  mChecksum += ((uint16_t*)&mEastVelocityRMSError)[1];
  stream >> mDownVelocityRMSError;
  mChecksum += ((uint16_t*)&mDownVelocityRMSError)[0];
  mChecksum += ((uint16_t*)&mDownVelocityRMSError)[1];
  stream >> mRollRMSError;
  mChecksum += ((uint16_t*)&mRollRMSError)[0];
  mChecksum += ((uint16_t*)&mRollRMSError)[1];
  stream >> mPitchRMSError;
  mChecksum += ((uint16_t*)&mPitchRMSError)[0];
  mChecksum += ((uint16_t*)&mPitchRMSError)[1];
  stream >> mHeadingRMSError;
  mChecksum += ((uint16_t*)&mHeadingRMSError)[0];
  mChecksum += ((uint16_t*)&mHeadingRMSError)[1];
  stream >> mErrorEllipsoidSemiMajor;
  mChecksum += ((uint16_t*)&mErrorEllipsoidSemiMajor)[0];
  mChecksum += ((uint16_t*)&mErrorEllipsoidSemiMajor)[1];
  stream >> mErrorEllipsoidSemiMinor;
  mChecksum += ((uint16_t*)&mErrorEllipsoidSemiMinor)[0];
  mChecksum += ((uint16_t*)&mErrorEllipsoidSemiMinor)[1];
  stream >> mErrorEllipsoidOrientation;
  mChecksum += ((uint16_t*)&mErrorEllipsoidOrientation)[0];
  mChecksum += ((uint16_t*)&mErrorEllipsoidOrientation)[1];
  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("VehicleNavigationPerformance::read(): wrong pad");
  mChecksum += pad;
  mChecksum = 65536 - mChecksum;
}

void VehicleNavigationPerformance::read(std::istream& stream) {
}

void VehicleNavigationPerformance::write(std::ostream& stream) const {
}

void VehicleNavigationPerformance::read(std::ifstream& stream) {
}

void VehicleNavigationPerformance::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mNorthPositionRMSError;
  stream << " ";
  stream << mEastPositionRMSError;
  stream << " ";
  stream << mDownPositionRMSError;
  stream << " ";
  stream << mNorthVelocityRMSError;
  stream << " ";
  stream << mEastVelocityRMSError;
  stream << " ";
  stream << mDownVelocityRMSError;
  stream << " ";
  stream << mRollRMSError;
  stream << " ";
  stream << mPitchRMSError;
  stream << " ";
  stream << mHeadingRMSError;
  stream << " ";
  stream << mErrorEllipsoidSemiMajor;
  stream << " ";
  stream << mErrorEllipsoidSemiMinor;
  stream << " ";
  stream << mErrorEllipsoidOrientation;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

VehicleNavigationPerformance* VehicleNavigationPerformance::clone() const {
  return new VehicleNavigationPerformance(*this);
}
