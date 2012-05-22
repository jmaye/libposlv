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

#include "types/BaseGPS2DataStream.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const BaseGPS2DataStream BaseGPS2DataStream::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BaseGPS2DataStream::BaseGPS2DataStream() :
    Group(10012),
    mGPSReceiverRawData(0) {
}

BaseGPS2DataStream::BaseGPS2DataStream(const BaseGPS2DataStream& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mVariableMsgByteCount(other.mVariableMsgByteCount) {
  memcpy(mReserved, other.mReserved, sizeof(mReserved));
  memcpy(mGPSReceiverRawData, other.mGPSReceiverRawData,
    sizeof(mGPSReceiverRawData));
}

BaseGPS2DataStream& BaseGPS2DataStream::operator =
    (const BaseGPS2DataStream& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    memcpy(mReserved, other.mReserved, sizeof(mReserved));
    mVariableMsgByteCount = other.mVariableMsgByteCount;
    memcpy(mGPSReceiverRawData, other.mGPSReceiverRawData,
      sizeof(mGPSReceiverRawData));
  }
  return *this;
}

BaseGPS2DataStream::~BaseGPS2DataStream() {
  if (mGPSReceiverRawData)
    delete []mGPSReceiverRawData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BaseGPS2DataStream::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  stream >> mTimeDistance;
  for (size_t i = 0; i < sizeof(mReserved); i++)
    stream >> mReserved[i];
  stream >> mVariableMsgByteCount;
  if (mGPSReceiverRawData)
    delete []mGPSReceiverRawData;
  mGPSReceiverRawData = new uint8_t[mVariableMsgByteCount];
  for (size_t i = 0; i < mVariableMsgByteCount; i++)
    stream >> mGPSReceiverRawData[i];
}

void BaseGPS2DataStream::read(std::istream& stream) {
}

void BaseGPS2DataStream::write(std::ostream& stream) const {
}

void BaseGPS2DataStream::read(std::ifstream& stream) {
}

void BaseGPS2DataStream::write(std::ofstream& stream) const {
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
    stream << std::hex << (uint16_t)mGPSReceiverRawData[i] << std::dec;
    stream << " ";
  }
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/


BaseGPS2DataStream* BaseGPS2DataStream::clone() const {
  return new BaseGPS2DataStream(*this);
}
