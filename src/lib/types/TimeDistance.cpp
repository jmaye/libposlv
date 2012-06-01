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
#include "base/BinaryWriter.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

TimeDistance::TimeDistance() {
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
  stream >> mTime2;
  stream >> mDistanceTag;
  stream >> mTimeType;
  stream >> mDistanceType;
}

void TimeDistance::write(BinaryWriter& stream) const {
  stream << mTime1;
  stream << mTime2;
  stream << mDistanceTag;
  stream << mTimeType;
  stream << mDistanceType;
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

BinaryWriter& operator << (BinaryWriter& stream, const TimeDistance& obj) {
  obj.write(stream);
  return stream;
}
