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

#include "types/PrimaryGPSDataStream.h"

#include "com/Connection.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const PrimaryGPSDataStream PrimaryGPSDataStream::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PrimaryGPSDataStream::PrimaryGPSDataStream() :
  Group(10001) {
}

PrimaryGPSDataStream::PrimaryGPSDataStream(const PrimaryGPSDataStream& other) :
  Group(other) {
}

PrimaryGPSDataStream& PrimaryGPSDataStream::operator =
  (const PrimaryGPSDataStream& other) {
  this->Group::operator=(other);
  return *this;
}

PrimaryGPSDataStream::~PrimaryGPSDataStream() {
  if (mau8GPSReceiverRawData)
    delete mau8GPSReceiverRawData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void PrimaryGPSDataStream::read(Connection& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  stream >> mTimeDistance;
  stream >> mGPSReceiverType;
  stream >> mReserved;
  stream >> mVariableMsgByteCount;
  mau8GPSReceiverRawData = new uint8_t[mVariableMsgByteCount];
  for (size_t i = 0; i < mVariableMsgByteCount; i++)
    stream >> mau8GPSReceiverRawData[i];
  uint32_t padSize = byteCount - 26 - 2 - 4 - 2 - mVariableMsgByteCount - 2 - 2;

  uint8_t pad;
  for (size_t i = 0; i < padSize; i++)
    stream >> pad;
}

void PrimaryGPSDataStream::read(std::istream& stream) {
}

void PrimaryGPSDataStream::write(std::ostream& stream) const {
}

void PrimaryGPSDataStream::read(std::ifstream& stream) {
}

void PrimaryGPSDataStream::write(std::ofstream& stream) const {
  stream << mTypeID;
//  stream << " ";
//  stream << mTimeDistance;
//  stream << mu16GPSReceiverType;
//  stream << " ";
//  stream << mu32Reserved;
//  stream << " ";
//  stream << mu16VariableMsgByteCount;
//  stream << " ";
//  for (uint16_t i = 0; i < mu16VariableMsgByteCount; i++) {
//    stream << hex << (uint16_t)mau8GPSReceiverRawData[i] << dec;
//    stream << " ";
//  }
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

PrimaryGPSDataStream* PrimaryGPSDataStream::clone() const {
  return new PrimaryGPSDataStream(*this);
}
