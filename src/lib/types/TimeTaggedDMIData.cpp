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

#include "com/Connection.h"

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
  Group(other) {
}

TimeTaggedDMIData& TimeTaggedDMIData::operator =
  (const TimeTaggedDMIData& other) {
  this->Group::operator=(other);
  return *this;
}

TimeTaggedDMIData::~TimeTaggedDMIData() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void TimeTaggedDMIData::read(Connection& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("TimeTaggedDMIData::read(): wrong byte count");

  stream >> mTimeDistance;
  stream >> mSignedDistanceTraveled;
  stream >> mUnsignedDistanceTraveled;
  stream >> mDMIScaleFactor;
  stream >> mDataStatus;
  stream >> mDMIType;
  stream >> mDMIDataRate;

  uint8_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("TimeTaggedDMIData::read(): wrong pad");
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
  stream << std::hex << (uint16_t)mDataStatus << std::dec;
  stream << " ";
  stream << std::hex << (uint16_t)mDMIType << std::dec;
  stream << " ";
  stream << std::hex << (uint16_t)mDMIDataRate << std::dec;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

TimeTaggedDMIData* TimeTaggedDMIData::clone() const {
  return new TimeTaggedDMIData(*this);
}
