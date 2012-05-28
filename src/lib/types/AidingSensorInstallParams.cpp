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

#include "types/AidingSensorInstallParams.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const AidingSensorInstallParams AidingSensorInstallParams::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

AidingSensorInstallParams::AidingSensorInstallParams() :
    Message(22) {
}

AidingSensorInstallParams::AidingSensorInstallParams(const
    AidingSensorInstallParams& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mDMIScaleFactor(other.mDMIScaleFactor),
    mRefDMIX(other.mRefDMIX),
    mRefDMIY(other.mRefDMIY),
    mRefDMIZ(other.mRefDMIZ) {
  memcpy(mReserved, other.mReserved, sizeof(mReserved));
}

AidingSensorInstallParams& AidingSensorInstallParams::operator =
    (const AidingSensorInstallParams& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mDMIScaleFactor = other.mDMIScaleFactor;
    mRefDMIX = other.mRefDMIX;
    mRefDMIY = other.mRefDMIY;
    mRefDMIZ = other.mRefDMIZ;
    memcpy(mReserved, other.mReserved, sizeof(mReserved));
  }
  return *this;
}

AidingSensorInstallParams::~AidingSensorInstallParams() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void AidingSensorInstallParams::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("AidingSensorInstallParams::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mDMIScaleFactor;
  stream >> mRefDMIX;
  stream >> mRefDMIY;
  stream >> mRefDMIZ;
  for (size_t i = 0; i < sizeof(mReserved) / sizeof(mReserved[0]); i++)
    stream >> mReserved[i];
}

void AidingSensorInstallParams::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mDMIScaleFactor;
  stream << mRefDMIX;
  stream << mRefDMIY;
  stream << mRefDMIZ;
  for (size_t i = 0; i < sizeof(mReserved) / sizeof(mReserved[0]); i++)
    stream << mReserved[i];
}

void AidingSensorInstallParams::read(std::istream& stream) {
}

void AidingSensorInstallParams::write(std::ostream& stream) const {
}

void AidingSensorInstallParams::read(std::ifstream& stream) {
}

void AidingSensorInstallParams::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

AidingSensorInstallParams* AidingSensorInstallParams::clone() const {
  return new AidingSensorInstallParams(*this);
}
