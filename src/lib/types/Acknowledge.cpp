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
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("Acknowledge::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mID;
  stream >> mResponseCode;
  stream >> mNewParamsStatus;
  for (size_t i = 0; i < sizeof(mParameterName) / sizeof(mParameterName[0]);
      i++)
    stream >> mParameterName[i];
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
