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

#include "types/Auxiliary1GPSDisplayData.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const Auxiliary1GPSDisplayData Auxiliary1GPSDisplayData::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Auxiliary1GPSDisplayData::Auxiliary1GPSDisplayData() :
    Group(23),
    mGPSRawData(0) {
}

Auxiliary1GPSDisplayData::Auxiliary1GPSDisplayData(const
    Auxiliary1GPSDisplayData& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mVariableMsgByteCount(other.mVariableMsgByteCount) {
    mGPSRawData = new uint8_t[mVariableMsgByteCount];
    memcpy(mGPSRawData, other.mGPSRawData, sizeof(mGPSRawData));
    memcpy(mReserved, other.mReserved, sizeof(mReserved));
}

Auxiliary1GPSDisplayData& Auxiliary1GPSDisplayData::operator =
    (const Auxiliary1GPSDisplayData& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    memcpy(mReserved, other.mReserved, sizeof(mReserved));
    mVariableMsgByteCount = other.mVariableMsgByteCount;
    mGPSRawData = new uint8_t[mVariableMsgByteCount];
    memcpy(mGPSRawData, other.mGPSRawData, sizeof(mGPSRawData));
  }
  return *this;
}

Auxiliary1GPSDisplayData::~Auxiliary1GPSDisplayData() {
  if (mGPSRawData)
    delete []mGPSRawData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Auxiliary1GPSDisplayData::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  stream >> mTimeDistance;
  for (size_t i = 0; i < sizeof(mReserved); i++)
    stream >> mReserved[i];
  stream >> mVariableMsgByteCount;
  if (mGPSRawData)
    delete []mGPSRawData;
  mGPSRawData = new uint8_t[mVariableMsgByteCount];
  for (size_t i = 0; i < mVariableMsgByteCount; i++)
    stream >> mGPSRawData[i];
}

void Auxiliary1GPSDisplayData::read(std::istream& stream) {
}

void Auxiliary1GPSDisplayData::write(std::ostream& stream) const {
}

void Auxiliary1GPSDisplayData::read(std::ifstream& stream) {
}

void Auxiliary1GPSDisplayData::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  for (size_t i = 0; i < 6; i++) {
    stream << std::hex << (uint16_t)mReserved[i] << std::dec;
    stream << " ";
  }
  stream << mVariableMsgByteCount;
  stream << " ";
  for (size_t i = 0; i < mVariableMsgByteCount; i++) {
    stream << std::hex << (uint16_t)mGPSRawData[i] << std::dec;
    stream << " ";
  }
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

Auxiliary1GPSDisplayData* Auxiliary1GPSDisplayData::clone() const {
  return new Auxiliary1GPSDisplayData(*this);
}
