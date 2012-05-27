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

#include "types/SecondaryGPSSetup.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const SecondaryGPSSetup SecondaryGPSSetup::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SecondaryGPSSetup::SecondaryGPSSetup() :
    Message(31) {
}

SecondaryGPSSetup::SecondaryGPSSetup(const SecondaryGPSSetup& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mGPSAutoConfig(other.mGPSAutoConfig),
    mComPortRate(other.mComPortRate) {
  memcpy(mReserved, other.mReserved, sizeof(mReserved));
}

SecondaryGPSSetup& SecondaryGPSSetup::operator =
    (const SecondaryGPSSetup& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mGPSAutoConfig = other.mGPSAutoConfig;
    mComPortRate = other.mComPortRate;
    memcpy(mReserved, other.mReserved, sizeof(mReserved));
  }
  return *this;
}

SecondaryGPSSetup::~SecondaryGPSSetup() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void SecondaryGPSSetup::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("SecondaryGPSSetup::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mGPSAutoConfig;
  stream >> mComPortRate;
  for (size_t i = 0; i < sizeof(mReserved) / sizeof(mReserved[0]); i++)
    stream >> mReserved[i];
}

void SecondaryGPSSetup::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mGPSAutoConfig;
  stream << mComPortRate;
  for (size_t i = 0; i < sizeof(mReserved) / sizeof(mReserved[0]); i++)
    stream << mReserved[i];
}

void SecondaryGPSSetup::read(std::istream& stream) {
}

void SecondaryGPSSetup::write(std::ostream& stream) const {
}

void SecondaryGPSSetup::read(std::ifstream& stream) {
}

void SecondaryGPSSetup::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

SecondaryGPSSetup* SecondaryGPSSetup::clone() const {
  return new SecondaryGPSSetup(*this);
}
