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

#include "types/Auxiliary2GPSDataStream.h"

#include "com/Connection.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const Auxiliary2GPSDataStream Auxiliary2GPSDataStream::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Auxiliary2GPSDataStream::Auxiliary2GPSDataStream() :
  Group(10008) {
}

Auxiliary2GPSDataStream::Auxiliary2GPSDataStream(const Auxiliary2GPSDataStream&
  other) :
  Group(other) {
}

Auxiliary2GPSDataStream& Auxiliary2GPSDataStream::operator =
  (const Auxiliary2GPSDataStream& other) {
  this->Group::operator=(other);
  return *this;
}

Auxiliary2GPSDataStream::~Auxiliary2GPSDataStream() {
  if (mau8GPSReceiverRawData)
    delete mau8GPSReceiverRawData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Auxiliary2GPSDataStream::read(Connection& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  stream >> mTimeDistance;
  for (size_t i = 0; i < 6; i++)
    stream >> mau8Reserved[i];
  stream >> mVariableMsgByteCount;
  mau8GPSReceiverRawData = new uint8_t[mVariableMsgByteCount];
  for (size_t i = 0; i < mVariableMsgByteCount; i++)
    stream >> mau8GPSReceiverRawData[i];
  size_t padSize = byteCount - 26 - 6 - 2 - mVariableMsgByteCount - 2 - 2;

  uint8_t pad;
  for (size_t i = 0; i < padSize; i++)
    stream >> pad;
}

void Auxiliary2GPSDataStream::read(std::istream& stream) {
}

void Auxiliary2GPSDataStream::write(std::ostream& stream) const {
}

void Auxiliary2GPSDataStream::read(std::ifstream& stream) {
}

void Auxiliary2GPSDataStream::write(std::ofstream& stream) const {
  stream << mTypeID;
//  stream << " ";
//  stream << mTimeDistance;
//  for (uint32_t i = 0; i < 6; i++) {
//    stream << hex << (uint16_t)mau8Reserved[i] << dec;
//    stream << " ";
//  }
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


Auxiliary2GPSDataStream* Auxiliary2GPSDataStream::clone() const {
  return new Auxiliary2GPSDataStream(*this);
}
