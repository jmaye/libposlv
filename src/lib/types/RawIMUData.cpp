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

#include "com/POSLVGroupRead.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const RawIMUData RawIMUData::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

RawIMUData::RawIMUData() :
  Group(10002) {
}

RawIMUData::RawIMUData(const RawIMUData& other) :
  Group(other) {
}

RawIMUData& RawIMUData::operator = (const RawIMUData& other) {
  this->Group::operator=(other);
  return *this;
}

RawIMUData::~RawIMUData() {
  if (mau8IMURawData)
    delete mau8IMURawData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void RawIMUData::read(POSLVGroupRead& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  stream >> mTimeDistance;
  for (size_t i = 0; i < 6; i++)
    stream >> mau8IMUHeader[i];
  stream >> mVariableMsgByteCount;
  mau8IMURawData = new uint8_t[mVariableMsgByteCount];
  for (size_t i = 0; i < mVariableMsgByteCount; i++)
    stream >> mau8IMURawData[i];
  stream >> mDataChecksum;
  uint32_t padSize = byteCount - mVariableMsgByteCount - 40;

  uint8_t pad;
  for (size_t i = 0; i < padSize; i++) {
    stream >> pad;
    if (pad != 0)
      throw IOException("RawIMUData::read(): wrong pad");
  }
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
    stream << mau8IMUHeader[i];
  stream << " ";
  stream << mVariableMsgByteCount;
  stream << " ";
  for (size_t i = 0; i < mVariableMsgByteCount; i++) {
    stream << std::hex << (uint16_t)mau8IMURawData[i] << std::dec;
    stream << " ";
  }
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

RawIMUData* RawIMUData::clone() const {
  return new RawIMUData(*this);
}
