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

#include "types/Auxiliary2GPSDisplayData.h"

#include "com/POSLVGroupRead.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const Auxiliary2GPSDisplayData Auxiliary2GPSDisplayData::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Auxiliary2GPSDisplayData::Auxiliary2GPSDisplayData() :
  Group(24),
  mau8GPSRawData(0) {
}

Auxiliary2GPSDisplayData::Auxiliary2GPSDisplayData(const
  Auxiliary2GPSDisplayData& other) :
  Group(other) {
}

Auxiliary2GPSDisplayData& Auxiliary2GPSDisplayData::operator =
  (const Auxiliary2GPSDisplayData& other) {
  this->Group::operator=(other);
  return *this;
}

Auxiliary2GPSDisplayData::~Auxiliary2GPSDisplayData() {
  if (mau8GPSRawData)
    delete mau8GPSRawData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Auxiliary2GPSDisplayData::read(POSLVGroupRead& stream) throw(IOException) {
  uint16_t byteCount;
  stream >> byteCount;

  stream >> mTimeDistance;
  for (size_t i = 0; i < 6; i++)
    stream >> mau8Reserved[i];
  stream >> mVariableMsgByteCount;
  mau8GPSRawData = new uint8_t[mVariableMsgByteCount];
  for (size_t i = 0; i < mVariableMsgByteCount; i++)
    stream >> mau8GPSRawData[i];

  size_t padSize = byteCount - mVariableMsgByteCount - 38;

  uint8_t pad;
  for (size_t i = 0; i < padSize; i++) {
    stream >> pad;
    if (pad != 0)
      throw IOException("Auxiliary2GPSDisplayData::read(): wrong pad");
  }
}

void Auxiliary2GPSDisplayData::read(std::istream& stream) {
}

void Auxiliary2GPSDisplayData::write(std::ostream& stream) const {
}

void Auxiliary2GPSDisplayData::read(std::ifstream& stream) {
}

void Auxiliary2GPSDisplayData::write(std::ofstream& stream) const {
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
    stream << std::hex << (uint16_t)mau8GPSRawData[i] << std::dec;
    stream << " ";
  }
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

Auxiliary2GPSDisplayData* Auxiliary2GPSDisplayData::clone() const {
  return new Auxiliary2GPSDisplayData(*this);
}
