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

#include "types/BaseGPS1Control.h"

#include "com/POSLVControl.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const BaseGPS1Control BaseGPS1Control::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BaseGPS1Control::BaseGPS1Control() :
  Message(37) {
}

BaseGPS1Control::BaseGPS1Control(const BaseGPS1Control&
  other) :
  Message(other) {
}

BaseGPS1Control& BaseGPS1Control::operator =
  (const BaseGPS1Control& other) {
  this->Message::operator=(other);
  return *this;
}

BaseGPS1Control::~BaseGPS1Control() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BaseGPS1Control::read(POSLVControl& stream) throw (IOException) {
  mChecksum = 19748 + 18259; // for $MSG
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("BaseGPS1Control::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTransactionNumber;
  mChecksum += mTransactionNumber;
  stream >> mBaseGPSInputType;
  mChecksum += mBaseGPSInputType;
  stream >> mLineControl;
  stream >> mModemControl;
  mChecksum += (mModemControl << 8) | mLineControl;
  stream >> mConnectionControl;
  stream >> mPhoneNumber[0];
  mChecksum += (mPhoneNumber[0] << 8) | mConnectionControl;
  for (size_t i = 1; i < 32; i+=2) {
    stream >> mPhoneNumber[i];
    if (i != 31) {
      stream >> mPhoneNumber[i + 1];
      mChecksum += (mPhoneNumber[i + 1] << 8) | mPhoneNumber[i];
    }
  }
  stream >> mNumRedials;
  mChecksum += (mNumRedials << 8) | mPhoneNumber[31];
  for (size_t i = 0; i < 64; i+=2) {
    stream >> mCommandString[i];
    stream >> mCommandString[i + 1];
    mChecksum += (mCommandString[i + 1] << 8) | mCommandString[i];
  }
  for (size_t i = 0; i < 128; i+=2) {
    stream >> mInitString[i];
    stream >> mInitString[i + 1];
    mChecksum += (mInitString[i + 1] << 8) | mInitString[i];
  }
  stream >> mTimeoutLength;
  mChecksum += mTimeoutLength;
  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("BaseGPS1Control::read(): wrong pad");
  mChecksum += pad;
  mChecksum += 8996; // for $#
  mChecksum = 65536 - mChecksum;
}

void BaseGPS1Control::write(POSLVControl& stream) const {
  uint16_t checksum = 19748 + 18259; // for $MSG
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount;
  checksum += mByteCount;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mBaseGPSInputType;
  checksum += mBaseGPSInputType;
  stream << mLineControl;
  stream << mModemControl;
  checksum += (mModemControl << 8) | mLineControl;
  stream << mConnectionControl;
  stream << mPhoneNumber[0];
  checksum += (mPhoneNumber[0] << 8) | mConnectionControl;
  for (size_t i = 1; i < 32; i+=2) {
    stream << mPhoneNumber[i];
    if (i != 31) {
      stream << mPhoneNumber[i + 1];
      checksum += (mPhoneNumber[i + 1] << 8) | mPhoneNumber[i];
    }
  }
  stream << mNumRedials;
  checksum += (mNumRedials << 8) | mPhoneNumber[31];
  for (size_t i = 0; i < 64; i+=2) {
    stream << mCommandString[i];
    stream << mCommandString[i + 1];
    checksum += (mCommandString[i + 1] << 8) | mCommandString[i];
  }
  for (size_t i = 0; i < 128; i+=2) {
    stream << mInitString[i];
    stream << mInitString[i + 1];
    checksum += (mInitString[i + 1] << 8) | mInitString[i];
  }
  stream << mTimeoutLength;
  checksum += mTimeoutLength;
  uint16_t pad = 0;
  stream << pad;
  checksum += pad;
  checksum += 8996; // for $#
  checksum = 65536 - checksum;
  stream << checksum;
}

void BaseGPS1Control::read(std::istream& stream) {
}

void BaseGPS1Control::write(std::ostream& stream) const {
}

void BaseGPS1Control::read(std::ifstream& stream) {
}

void BaseGPS1Control::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

BaseGPS1Control* BaseGPS1Control::clone() const {
  return new BaseGPS1Control(*this);
}
