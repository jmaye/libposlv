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

#include "types/RawIMUData.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const RawIMUData RawIMUData::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

RawIMUData::RawIMUData() :
    Group(10002),
    mIMURawData(0) {
}

RawIMUData::RawIMUData(const RawIMUData& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mVariableMsgByteCount(other.mVariableMsgByteCount),
    mDataChecksum(other.mDataChecksum) {
  mIMURawData = new uint8_t[mVariableMsgByteCount];
  memcpy(mIMURawData, other.mIMURawData, sizeof(mIMURawData));
  memcpy(mIMUHeader, other.mIMUHeader, sizeof(mIMUHeader));
}

RawIMUData& RawIMUData::operator = (const RawIMUData& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    memcpy(mIMUHeader, other.mIMUHeader, sizeof(mIMUHeader));
    mVariableMsgByteCount = other.mVariableMsgByteCount;
    mIMURawData = new uint8_t[mVariableMsgByteCount];
    memcpy(mIMURawData, other.mIMURawData, sizeof(mIMURawData));
    mDataChecksum = other.mDataChecksum;
  }
  return *this;
}

RawIMUData::~RawIMUData() {
  if (mIMURawData)
    delete []mIMURawData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void RawIMUData::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  stream >> mTimeDistance;
  for (size_t i = 0; i < sizeof(mIMUHeader); i++)
    stream >> mIMUHeader[i];
  stream >> mVariableMsgByteCount;
  if (mIMURawData)
    delete []mIMURawData;
  mIMURawData = new uint8_t[mVariableMsgByteCount];
  for (size_t i = 0; i < mVariableMsgByteCount; i++)
    stream >> mIMURawData[i];
  stream >> mDataChecksum;
}

void RawIMUData::write(BinaryWriter& stream) const {
}

void RawIMUData::read(std::istream& stream) {
}

void RawIMUData::write(std::ostream& stream) const {
}

void RawIMUData::read(std::ifstream& stream) {
}

void RawIMUData::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  for (size_t i = 0; i < 6; i++)
    stream << mIMUHeader[i];
  stream << " ";
  stream << mVariableMsgByteCount;
  stream << " ";
  for (size_t i = 0; i < mVariableMsgByteCount; i++) {
    stream << std::hex << (uint16_t)mIMURawData[i] << std::dec;
    stream << " ";
  }
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

RawIMUData* RawIMUData::clone() const {
  return new RawIMUData(*this);
}
