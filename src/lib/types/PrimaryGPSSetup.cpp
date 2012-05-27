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

#include "types/PrimaryGPSSetup.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const PrimaryGPSSetup PrimaryGPSSetup::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PrimaryGPSSetup::PrimaryGPSSetup() :
    Message(30) {
}

PrimaryGPSSetup::PrimaryGPSSetup(const PrimaryGPSSetup& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mGPSAutoConfig(other.mGPSAutoConfig),
    mComPortRate(other.mComPortRate) {
  memcpy(mReserved, other.mReserved, sizeof(mReserved));
}

PrimaryGPSSetup& PrimaryGPSSetup::operator =
    (const PrimaryGPSSetup& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mGPSAutoConfig = other.mGPSAutoConfig;
    mComPortRate = other.mComPortRate;
    memcpy(mReserved, other.mReserved, sizeof(mReserved));
  }
  return *this;
}

PrimaryGPSSetup::~PrimaryGPSSetup() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void PrimaryGPSSetup::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("PrimaryGPSSetup::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mGPSAutoConfig;
  stream >> mComPortRate;
  for (size_t i = 0; i < sizeof(mReserved) / sizeof(mReserved[0]); i++)
    stream >> mReserved[i];
}

void PrimaryGPSSetup::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mGPSAutoConfig;
  stream << mComPortRate;
  for (size_t i = 0; i < sizeof(mReserved) / sizeof(mReserved[0]); i++)
    stream << mReserved[i];
}

void PrimaryGPSSetup::read(std::istream& stream) {
}

void PrimaryGPSSetup::write(std::ostream& stream) const {
}

void PrimaryGPSSetup::read(std::ifstream& stream) {
}

void PrimaryGPSSetup::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

PrimaryGPSSetup* PrimaryGPSSetup::clone() const {
  return new PrimaryGPSSetup(*this);
}
