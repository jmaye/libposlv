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

#include "types/TimeDistance.h"

#include "base/BinaryReader.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

TimeDistance::TimeDistance() :
    mChecksum(0) {
}

TimeDistance::TimeDistance(const TimeDistance& other) :
    mTime1(other.mTime1),
    mTime2(other.mTime2),
    mDistanceTag(other.mDistanceTag),
    mTimeType(mTimeType),
    mDistanceType(mDistanceType) {
}

TimeDistance& TimeDistance::operator = (const TimeDistance& other) {
  if (this != &other) {
    mTime1 = other.mTime1;
    mTime2 = other.mTime2;
    mDistanceTag = other.mDistanceTag;
    mTimeType = mTimeType;
    mDistanceType = mDistanceType;
  }
  return *this;
}

TimeDistance::~TimeDistance() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void TimeDistance::read(BinaryReader& stream) {
  stream >> mTime1;
  mChecksum += ((uint16_t*)&mTime1)[0];
  mChecksum += ((uint16_t*)&mTime1)[1];
  mChecksum += ((uint16_t*)&mTime1)[2];
  mChecksum += ((uint16_t*)&mTime1)[3];
  stream >> mTime2;
  mChecksum += ((uint16_t*)&mTime2)[0];
  mChecksum += ((uint16_t*)&mTime2)[1];
  mChecksum += ((uint16_t*)&mTime2)[2];
  mChecksum += ((uint16_t*)&mTime2)[3];
  stream >> mDistanceTag;
  mChecksum += ((uint16_t*)&mDistanceTag)[0];
  mChecksum += ((uint16_t*)&mDistanceTag)[1];
  mChecksum += ((uint16_t*)&mDistanceTag)[2];
  mChecksum += ((uint16_t*)&mDistanceTag)[3];
  stream >> mTimeType;
  stream >> mDistanceType;
  mChecksum += mDistanceType << 8 | mTimeType;
}

void TimeDistance::read(std::istream& stream) {
}

void TimeDistance::write(std::ostream& stream) const {
}

void TimeDistance::read(std::ifstream& stream) {
}

void TimeDistance::write(std::ofstream& stream) const {
  stream << mTime1;
  stream << " ";
  stream << mTime2;
  stream << " ";
  stream << mDistanceTag;
  stream << " ";
  stream << (uint16_t)mTimeType;
  stream << " ";
  stream << (uint16_t)mDistanceType;
  stream << " ";
}

BinaryReader& operator >> (BinaryReader& stream, TimeDistance& obj) {
  obj.read(stream);
  return stream;
}
