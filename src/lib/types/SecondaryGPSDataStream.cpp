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

#include "types/SecondaryGPSDataStream.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const SecondaryGPSDataStream SecondaryGPSDataStream::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SecondaryGPSDataStream::SecondaryGPSDataStream() :
    Group(10009),
    mVariableMsgByteCount(0),
    mGPSReceiverRawData(0) {
}

SecondaryGPSDataStream::SecondaryGPSDataStream(const SecondaryGPSDataStream&
    other) :
    Group(other),
    mByteCount(other.mByteCount),
    mTimeDistance(other.mTimeDistance),
    mGPSReceiverType(other.mGPSReceiverType),
    mReserved(other.mReserved),
    mVariableMsgByteCount(other.mVariableMsgByteCount) {
  if (mVariableMsgByteCount) {
    mGPSReceiverRawData = new uint8_t[mVariableMsgByteCount];
    memcpy(mGPSReceiverRawData, other.mGPSReceiverRawData,
      sizeof(mGPSReceiverRawData));
  }
  else
    mGPSReceiverRawData = 0;
}

SecondaryGPSDataStream& SecondaryGPSDataStream::operator =
    (const SecondaryGPSDataStream& other) {
  if (this != &other) {
    Group::operator=(other);
    mByteCount = other.mByteCount;
    mTimeDistance = other.mTimeDistance;
    mGPSReceiverType = other.mGPSReceiverType;
    mReserved = other.mReserved;
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

SecondaryGPSDataStream::~SecondaryGPSDataStream() {
  if (mGPSReceiverRawData)
    delete []mGPSReceiverRawData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void SecondaryGPSDataStream::read(BinaryReader& stream) {
  stream >> mByteCount;
  stream >> mTimeDistance;
  stream >> mGPSReceiverType;
  stream >> mReserved;
  stream >> mVariableMsgByteCount;
  if (mGPSReceiverRawData)
    delete []mGPSReceiverRawData;
  mGPSReceiverRawData = new uint8_t[mVariableMsgByteCount];
  for (size_t i = 0; i < mVariableMsgByteCount; i++)
    stream >> mGPSReceiverRawData[i];
}

void SecondaryGPSDataStream::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTimeDistance;
  stream << mGPSReceiverType;
  stream << mReserved;
  stream << mVariableMsgByteCount;
  for (size_t i = 0; i < mVariableMsgByteCount; i++)
    stream << mGPSReceiverRawData[i];
}

void SecondaryGPSDataStream::read(std::istream& stream) {
}

void SecondaryGPSDataStream::write(std::ostream& stream) const {
}

void SecondaryGPSDataStream::read(std::ifstream& stream) {
}

void SecondaryGPSDataStream::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mGPSReceiverType;
  stream << " ";
  stream << mReserved;
  stream << " ";
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

SecondaryGPSDataStream* SecondaryGPSDataStream::clone() const {
  return new SecondaryGPSDataStream(*this);
}
