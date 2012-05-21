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

#include "types/Acknowledge.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const Acknowledge Acknowledge::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Acknowledge::Acknowledge() :
    Message(0) {
}

Acknowledge::Acknowledge(const Acknowledge& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mID(other.mID),
    mResponseCode(other.mResponseCode),
    mNewParamsStatus(other.mNewParamsStatus) {
  memcpy(mParameterName, other.mParameterName, sizeof(mParameterName));
}

Acknowledge& Acknowledge::operator = (const Acknowledge& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mID = other.mID;
    mResponseCode = other.mResponseCode;
    mNewParamsStatus = other.mNewParamsStatus;
    memcpy(mParameterName, other.mParameterName, sizeof(mParameterName));
  }
  return *this;
}

Acknowledge::~Acknowledge() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Acknowledge::read(BinaryReader& stream) {
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("Acknowledge::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTransactionNumber;
  mChecksum += mTransactionNumber;
  stream >> mID;
  mChecksum += mID;
  stream >> mResponseCode;
  mChecksum += mResponseCode;
  stream >> mNewParamsStatus;
  mChecksum += mParameterName[0] << 8 | mNewParamsStatus;
  for (size_t i = 0; i < 32; i++)
    stream >> mParameterName[i];
  for (size_t i = 2; i < 31; i += 2)
    mChecksum += mParameterName[i] << 8 | mParameterName[i - 1];
  uint8_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("Acknowledge::read(): wrong pad");
  mChecksum += pad << 8 | mParameterName[31];
  mChecksum = 65536 - mChecksum;
}

void Acknowledge::write(BinaryWriter& stream) const {
}

void Acknowledge::read(std::istream& stream) {
}

void Acknowledge::write(std::ostream& stream) const {
}

void Acknowledge::read(std::ifstream& stream) {
}

void Acknowledge::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

Acknowledge* Acknowledge::clone() const {
  return new Acknowledge(*this);
}
