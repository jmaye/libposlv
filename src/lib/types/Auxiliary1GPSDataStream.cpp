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

#include "com/POSLVGroupRead.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const Auxiliary1GPSDataStream Auxiliary1GPSDataStream::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Auxiliary1GPSDataStream::Auxiliary1GPSDataStream() :
  Group(10007) {
}

Auxiliary1GPSDataStream::Auxiliary1GPSDataStream(const Auxiliary1GPSDataStream&
  other) :
  Group(other) {
}

Auxiliary1GPSDataStream& Auxiliary1GPSDataStream::operator =
  (const Auxiliary1GPSDataStream& other) {
  this->Group::operator=(other);
  return *this;
}

Auxiliary1GPSDataStream::~Auxiliary1GPSDataStream() {
  if (mau8GPSReceiverRawData)
    delete mau8GPSReceiverRawData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Auxiliary1GPSDataStream::read(POSLVGroupRead& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;

  stream >> mTimeDistance;
  for (size_t i = 0; i < 6; i++)
    stream >> mau8Reserved[i];
  stream >> mVariableMsgByteCount;
  mau8GPSReceiverRawData = new uint8_t[mVariableMsgByteCount];
  for (size_t i = 0; i < mVariableMsgByteCount; i++)
    stream >> mau8GPSReceiverRawData[i];

  size_t padSize = byteCount - mVariableMsgByteCount - 38;

  uint8_t pad;
  for (size_t i = 0; i < padSize; i++) {
    stream >> pad;
    if (pad != 0)
      throw IOException("Auxiliary1GPSDataStream::read(): wrong pad");
  }
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
    stream << std::hex << (uint16_t)mau8Reserved[i] << std::dec;
    stream << " ";
  }
  stream << mVariableMsgByteCount;
  stream << " ";
  for (size_t i = 0; i < mVariableMsgByteCount; i++) {
    stream << std::hex << (uint16_t)mau8GPSReceiverRawData[i] << std::dec;
    stream << " ";
  }
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/


Auxiliary1GPSDataStream* Auxiliary1GPSDataStream::clone() const {
  return new Auxiliary1GPSDataStream(*this);
}
