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

#include "types/TimeTaggedIMUData.h"

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const TimeTaggedIMUData TimeTaggedIMUData::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

TimeTaggedIMUData::TimeTaggedIMUData() :
    Group(4) {
}

TimeTaggedIMUData::TimeTaggedIMUData(const TimeTaggedIMUData& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mXIncrementalVelocity(other.mXIncrementalVelocity),
    mYIncrementalVelocity(other.mYIncrementalVelocity),
    mZIncrementalVelocity(other.mZIncrementalVelocity),
    mXIncrementalAngle(other.mXIncrementalAngle),
    mYIncrementalAngle(other.mYIncrementalAngle),
    mZIncrementalAngle(other.mZIncrementalAngle),
    mDataStatus(other.mDataStatus),
    mIMUType(other.mIMUType),
    mPOSIMUDataRate(other.mPOSIMUDataRate),
    mIMUStatus(other.mIMUStatus) {
}

TimeTaggedIMUData& TimeTaggedIMUData::operator =
    (const TimeTaggedIMUData& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    mXIncrementalVelocity = other.mXIncrementalVelocity;
    mYIncrementalVelocity = other.mYIncrementalVelocity;
    mZIncrementalVelocity = other.mZIncrementalVelocity;
    mXIncrementalAngle = other.mXIncrementalAngle;
    mYIncrementalAngle = other.mYIncrementalAngle;
    mZIncrementalAngle = other.mZIncrementalAngle;
    mDataStatus = other.mDataStatus;
    mIMUType = other.mIMUType;
    mPOSIMUDataRate = other.mPOSIMUDataRate;
    mIMUStatus = other.mIMUStatus;
  }
  return *this;
}

TimeTaggedIMUData::~TimeTaggedIMUData() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void TimeTaggedIMUData::read(BinaryReader& stream) {
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("TimeTaggedIMUData::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTimeDistance;
  mChecksum += mTimeDistance.mChecksum;
  stream >> mXIncrementalVelocity;
  mChecksum += ((uint16_t*)&mXIncrementalVelocity)[0];
  mChecksum += ((uint16_t*)&mXIncrementalVelocity)[1];
  stream >> mYIncrementalVelocity;
  mChecksum += ((uint16_t*)&mYIncrementalVelocity)[0];
  mChecksum += ((uint16_t*)&mYIncrementalVelocity)[1];
  stream >> mZIncrementalVelocity;
  mChecksum += ((uint16_t*)&mZIncrementalVelocity)[0];
  mChecksum += ((uint16_t*)&mZIncrementalVelocity)[1];
  stream >> mXIncrementalAngle;
  mChecksum += ((uint16_t*)&mXIncrementalAngle)[0];
  mChecksum += ((uint16_t*)&mXIncrementalAngle)[1];
  stream >> mYIncrementalAngle;
  mChecksum += ((uint16_t*)&mYIncrementalAngle)[0];
  mChecksum += ((uint16_t*)&mYIncrementalAngle)[1];
  stream >> mZIncrementalAngle;
  mChecksum += ((uint16_t*)&mZIncrementalAngle)[0];
  mChecksum += ((uint16_t*)&mZIncrementalAngle)[1];
  stream >> mDataStatus;
  stream >> mIMUType;
  mChecksum += mIMUType << 8 | mDataStatus;
  stream >> mPOSIMUDataRate;
  stream >> mIMUStatus;
  mChecksum += ((uint8_t*)&mIMUStatus)[0] << 8 | mPOSIMUDataRate;
  uint8_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("TimeTaggedIMUData::read(): wrong pad");
  mChecksum += pad << 8 | ((uint8_t*)&mIMUStatus)[1];
  mChecksum = 65536 - mChecksum;
}

void TimeTaggedIMUData::read(std::istream& stream) {
}

void TimeTaggedIMUData::write(std::ostream& stream) const {
}

void TimeTaggedIMUData::read(std::ifstream& stream) {
}

void TimeTaggedIMUData::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mXIncrementalVelocity;
  stream << " ";
  stream << mYIncrementalVelocity;
  stream << " ";
  stream << mZIncrementalVelocity;
  stream << " ";
  stream << mXIncrementalAngle;
  stream << " ";
  stream << mYIncrementalAngle;
  stream << " ";
  stream << mZIncrementalAngle;
  stream << " ";
  stream << std::hex << (uint16_t)mDataStatus << std::dec;
  stream << " ";
  stream << (uint16_t)mIMUType;
  stream << " ";
  stream << (uint16_t)mPOSIMUDataRate;
  stream << " ";
  stream << std::hex << mIMUStatus << std::dec;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

TimeTaggedIMUData* TimeTaggedIMUData::clone() const {
  return new TimeTaggedIMUData(*this);
}
