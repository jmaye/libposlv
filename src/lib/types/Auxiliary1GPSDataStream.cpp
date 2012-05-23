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

#include "types/Auxiliary1GPSDataStream.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const Auxiliary1GPSDataStream Auxiliary1GPSDataStream::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Auxiliary1GPSDataStream::Auxiliary1GPSDataStream() :
    Group(10007),
    mGPSReceiverRawData(0) {
}

Auxiliary1GPSDataStream::Auxiliary1GPSDataStream(const Auxiliary1GPSDataStream&
    other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mVariableMsgByteCount(other.mVariableMsgByteCount) {
  mGPSReceiverRawData = new uint8_t[mVariableMsgByteCount];
  memcpy(mGPSReceiverRawData, other.mGPSReceiverRawData,
    sizeof(mGPSReceiverRawData));
  memcpy(mReserved, other.mReserved, sizeof(mReserved));
}

Auxiliary1GPSDataStream& Auxiliary1GPSDataStream::operator =
    (const Auxiliary1GPSDataStream& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    memcpy(mReserved, other.mReserved, sizeof(mReserved));
    mVariableMsgByteCount = other.mVariableMsgByteCount;
    mGPSReceiverRawData = new uint8_t[mVariableMsgByteCount];
    memcpy(mGPSReceiverRawData, other.mGPSReceiverRawData,
      sizeof(mGPSReceiverRawData));
  }
  return *this;
}

Auxiliary1GPSDataStream::~Auxiliary1GPSDataStream() {
  if (mGPSReceiverRawData)
    delete []mGPSReceiverRawData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Auxiliary1GPSDataStream::read(BinaryReader& stream) {
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

void Auxiliary1GPSDataStream::write(BinaryWriter& stream) const {
}

void Auxiliary1GPSDataStream::read(std::istream& stream) {
}

void Auxiliary1GPSDataStream::write(std::ostream& stream) const {
}

void Auxiliary1GPSDataStream::read(std::ifstream& stream) {
}

void Auxiliary1GPSDataStream::write(std::ofstream& stream) const {
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


Auxiliary1GPSDataStream* Auxiliary1GPSDataStream::clone() const {
  return new Auxiliary1GPSDataStream(*this);
}
