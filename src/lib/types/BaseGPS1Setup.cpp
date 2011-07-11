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

#include "types/BaseGPS1Setup.h"

#include "com/POSLVControl.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const BaseGPS1Setup BaseGPS1Setup::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BaseGPS1Setup::BaseGPS1Setup() :
  Message(37) {
}

BaseGPS1Setup::BaseGPS1Setup(const BaseGPS1Setup& other) :
  Message(other) {
}

BaseGPS1Setup& BaseGPS1Setup::operator =
  (const BaseGPS1Setup& other) {
  this->Message::operator=(other);
  return *this;
}

BaseGPS1Setup::~BaseGPS1Setup() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BaseGPS1Setup::read(POSLVControl& stream) {
}

void BaseGPS1Setup::write(POSLVControl& stream) const {
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
  checksum += (mModemControl << 8 | mLineControl);
  stream << mConnectionControl;
  stream << mPhoneNumber[0];
  checksum += (mPhoneNumber[0] << 8 | mConnectionControl);
  for (size_t i = 1; i < 32; i+=2) {
    stream << mPhoneNumber[i];
    if (i != 31) {
      stream << mPhoneNumber[i + 1];
      checksum += (mPhoneNumber[i + 1] << 8 | mPhoneNumber[i]);
    }
  }
  stream << mRedialsNumber;
  checksum += (mRedialsNumber << 8 | mPhoneNumber[31]);
  for (size_t i = 0; i < 64; i+=2) {
    stream << mModemCommandString[i];
    stream << mModemCommandString[i + 1];
    checksum += (mModemCommandString[i + 1] << 8 | mModemCommandString[i]);
  }
  for (size_t i = 0; i < 128; i+=2) {
    stream << mModemInitString[i];
    stream << mModemInitString[i + 1];
    checksum += (mModemInitString[i + 1] << 8 | mModemInitString[i]);
  }
  stream << mDataTimeout;
  checksum += mDataTimeout;
  checksum += 8996; // for $#
  checksum = 65536 - checksum;
  stream << checksum;
}

void BaseGPS1Setup::read(std::istream& stream) {
}

void BaseGPS1Setup::write(std::ostream& stream) const {
}

void BaseGPS1Setup::read(std::ifstream& stream) {
}

void BaseGPS1Setup::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

BaseGPS1Setup* BaseGPS1Setup::clone() const {
  return new BaseGPS1Setup(*this);
}
