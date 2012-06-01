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

#include "types/BaseGPS1DataStream.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const BaseGPS1DataStream BaseGPS1DataStream::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BaseGPS1DataStream::BaseGPS1DataStream() :
    Group(10011),
    mVariableMsgByteCount(0),
    mGPSReceiverRawData(0) {
}

BaseGPS1DataStream::BaseGPS1DataStream(const BaseGPS1DataStream& other) :
    Group(other),
    mByteCount(other.mByteCount),
    mTimeDistance(other.mTimeDistance),
    mVariableMsgByteCount(other.mVariableMsgByteCount) {
  if (mVariableMsgByteCount) {
    mGPSReceiverRawData = new uint8_t[mVariableMsgByteCount];
    memcpy(mGPSReceiverRawData, other.mGPSReceiverRawData,
      sizeof(mGPSReceiverRawData));
  }
  else
    mGPSReceiverRawData = 0;
  memcpy(mReserved, other.mReserved, sizeof(mReserved));
}

BaseGPS1DataStream& BaseGPS1DataStream::operator =
    (const BaseGPS1DataStream& other) {
  if (this != &other) {
    Group::operator=(other);
    mByteCount = other.mByteCount;
    mTimeDistance = other.mTimeDistance;
    memcpy(mReserved, other.mReserved, sizeof(mReserved));
    mVariableMsgByteCount = other.mVariableMsgByteCount;
    if (mVariableMsgByteCount) {
      mGPSReceiverRawData = new uint8_t[mVariableMsgByteCount];
      memcpy(mGPSReceiverRawData, other.mGPSReceiverRawData,
        sizeof(mGPSReceiverRawData));
    }
    else
      mGPSReceiverRawData = 0;
  }
  return *this;
}

BaseGPS1DataStream::~BaseGPS1DataStream() {
  if (mGPSReceiverRawData)
    delete []mGPSReceiverRawData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BaseGPS1DataStream::read(BinaryReader& stream) {
  stream >> mByteCount;
  stream >> mTimeDistance;
  for (size_t i = 0; i < sizeof(mReserved) / sizeof(mReserved[0]); i++)
    stream >> mReserved[i];
  stream >> mVariableMsgByteCount;
  if (mGPSReceiverRawData)
    delete []mGPSReceiverRawData;
  mGPSReceiverRawData = new uint8_t[mVariableMsgByteCount];
  for (size_t i = 0; i < mVariableMsgByteCount; i++)
    stream >> mGPSReceiverRawData[i];
}

void BaseGPS1DataStream::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTimeDistance;
  for (size_t i = 0; i < sizeof(mReserved) / sizeof(mReserved[0]); i++)
    stream << mReserved[i];
  stream << mVariableMsgByteCount;
  for (size_t i = 0; i < mVariableMsgByteCount; i++)
    stream << mGPSReceiverRawData[i];
}

void BaseGPS1DataStream::read(std::istream& stream) {
}

void BaseGPS1DataStream::write(std::ostream& stream) const {
}

void BaseGPS1DataStream::read(std::ifstream& stream) {
}

void BaseGPS1DataStream::write(std::ofstream& stream) const {
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


BaseGPS1DataStream* BaseGPS1DataStream::clone() const {
  return new BaseGPS1DataStream(*this);
}
