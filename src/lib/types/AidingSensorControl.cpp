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

#include "types/AidingSensorControl.h"

#include "com/POSLVControl.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const AidingSensorControl AidingSensorControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

AidingSensorControl::AidingSensorControl() :
  Message(22) {
}

AidingSensorControl::AidingSensorControl(const AidingSensorControl&
  other) :
  Message(other) {
}

AidingSensorControl& AidingSensorControl::operator =
  (const AidingSensorControl& other) {
  this->Message::operator=(other);
  return *this;
}

AidingSensorControl::~AidingSensorControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void AidingSensorControl::read(POSLVControl& stream) throw (IOException) {
  mChecksum = 19748 + 18259; // for $MSG
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("AidingSensorControl::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTransactionNumber;
  mChecksum += mTransactionNumber;

  stream >> mDMIScaleFactor;
  mChecksum += ((uint16_t*)&mDMIScaleFactor)[0];
  mChecksum += ((uint16_t*)&mDMIScaleFactor)[1];
  stream >> mRefDMIX;
  mChecksum += ((uint16_t*)&mRefDMIX)[0];
  mChecksum += ((uint16_t*)&mRefDMIX)[1];
  stream >> mRefDMIY;
  mChecksum += ((uint16_t*)&mRefDMIY)[0];
  mChecksum += ((uint16_t*)&mRefDMIY)[1];
  stream >> mRefDMIZ;
  mChecksum += ((uint16_t*)&mRefDMIZ)[0];
  mChecksum += ((uint16_t*)&mRefDMIZ)[1];
  for (size_t i = 0; i < 7; i++) {
    stream >> mReserved[i];
    mChecksum += ((uint16_t*)&mReserved[i])[0];
    mChecksum += ((uint16_t*)&mReserved[i])[1];
  }
  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("AidingSensorControl::read(): wrong pad");
  mChecksum += pad;
  mChecksum += 8996; // for $#
  mChecksum = 65536 - mChecksum;
}

void AidingSensorControl::write(POSLVControl& stream) const {
  uint16_t checksum = 19748 + 18259; // for $MSG
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount;
  checksum += mByteCount;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mDMIScaleFactor;
  checksum += ((uint16_t*)&mDMIScaleFactor)[0];
  checksum += ((uint16_t*)&mDMIScaleFactor)[1];
  stream << mRefDMIX;
  checksum += ((uint16_t*)&mRefDMIX)[0];
  checksum += ((uint16_t*)&mRefDMIX)[1];
  stream << mRefDMIY;
  checksum += ((uint16_t*)&mRefDMIY)[0];
  checksum += ((uint16_t*)&mRefDMIY)[1];
  stream << mRefDMIZ;
  checksum += ((uint16_t*)&mRefDMIZ)[0];
  checksum += ((uint16_t*)&mRefDMIZ)[1];
  for (size_t i = 0; i < 7; i++) {
    stream << mReserved[i];
    checksum += ((uint16_t*)&mReserved[i])[0];
    checksum += ((uint16_t*)&mReserved[i])[1];
  }
  uint16_t pad = 0;
  stream << pad;
  checksum += pad;
  checksum += 8996; // for $#
  checksum = 65536 - checksum;
  stream << checksum;
}

void AidingSensorControl::read(std::istream& stream) {
}

void AidingSensorControl::write(std::ostream& stream) const {
}

void AidingSensorControl::read(std::ifstream& stream) {
}

void AidingSensorControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

AidingSensorControl* AidingSensorControl::clone() const {
  return new AidingSensorControl(*this);
}
