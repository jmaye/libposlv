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

#include "types/TimeTaggedDMIData.h"

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const TimeTaggedDMIData TimeTaggedDMIData::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

TimeTaggedDMIData::TimeTaggedDMIData() :
    Group(15) {
}

TimeTaggedDMIData::TimeTaggedDMIData(const TimeTaggedDMIData& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mSignedDistanceTraveled(other.mSignedDistanceTraveled),
    mUnsignedDistanceTraveled(other.mUnsignedDistanceTraveled),
    mDMIScaleFactor(other.mDMIScaleFactor),
    mDataStatus(other.mDataStatus),
    mDMIType(other.mDMIType),
    mDMIDataRate(other.mDMIDataRate) {
}

TimeTaggedDMIData& TimeTaggedDMIData::operator =
    (const TimeTaggedDMIData& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    mSignedDistanceTraveled = other.mSignedDistanceTraveled;
    mUnsignedDistanceTraveled = other.mUnsignedDistanceTraveled;
    mDMIScaleFactor = other.mDMIScaleFactor;
    mDataStatus = other.mDataStatus;
    mDMIType = other.mDMIType;
    mDMIDataRate = other.mDMIDataRate;
  }
  return *this;
}

TimeTaggedDMIData::~TimeTaggedDMIData() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void TimeTaggedDMIData::read(BinaryReader& stream) {
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("TimeTaggedDMIData::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTimeDistance;
  mChecksum += mTimeDistance.mChecksum;
  stream >> mSignedDistanceTraveled;
  mChecksum += ((uint16_t*)&mSignedDistanceTraveled)[0];
  mChecksum += ((uint16_t*)&mSignedDistanceTraveled)[1];
  mChecksum += ((uint16_t*)&mSignedDistanceTraveled)[2];
  mChecksum += ((uint16_t*)&mSignedDistanceTraveled)[3];
  stream >> mUnsignedDistanceTraveled;
  mChecksum += ((uint16_t*)&mUnsignedDistanceTraveled)[0];
  mChecksum += ((uint16_t*)&mUnsignedDistanceTraveled)[1];
  mChecksum += ((uint16_t*)&mUnsignedDistanceTraveled)[2];
  mChecksum += ((uint16_t*)&mUnsignedDistanceTraveled)[3];
  stream >> mDMIScaleFactor;
  mChecksum += mDMIScaleFactor;
  stream >> mDataStatus;
  stream >> mDMIType;
  mChecksum += mDMIType << 8 | mDataStatus;
  stream >> mDMIDataRate;
  uint8_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("TimeTaggedDMIData::read(): wrong pad");
  mChecksum += pad << 8 | mDMIDataRate;
  mChecksum = 65536 - mChecksum;
}

void TimeTaggedDMIData::read(std::istream& stream) {
}

void TimeTaggedDMIData::write(std::ostream& stream) const {
}

void TimeTaggedDMIData::read(std::ifstream& stream) {
}

void TimeTaggedDMIData::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mSignedDistanceTraveled;
  stream << " ";
  stream << mUnsignedDistanceTraveled;
  stream << " ";
  stream << mDMIScaleFactor;
  stream << " ";
  stream << (uint16_t)mDataStatus;
  stream << " ";
  stream << (uint16_t)mDMIType;
  stream << " ";
  stream << (uint16_t)mDMIDataRate;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

TimeTaggedDMIData* TimeTaggedDMIData::clone() const {
  return new TimeTaggedDMIData(*this);
}
