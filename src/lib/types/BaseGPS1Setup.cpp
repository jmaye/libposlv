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

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

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
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mBaseGPSInputType(other.mBaseGPSInputType),
    mLineControl(other.mLineControl),
    mModemControl(other.mModemControl),
    mConnectionControl(other.mConnectionControl),
    mNumRedials(other.mNumRedials),
    mTimeoutLength(other.mTimeoutLength) {
  memcpy(mPhoneNumber, other.mPhoneNumber, sizeof(mPhoneNumber));
  memcpy(mCommandString, other.mCommandString, sizeof(mCommandString));
  memcpy(mInitString, other.mInitString, sizeof(mInitString));
}

BaseGPS1Setup& BaseGPS1Setup::operator = (const BaseGPS1Setup& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mBaseGPSInputType = other.mBaseGPSInputType;
    mLineControl = other.mLineControl;
    mModemControl = other.mModemControl;
    mConnectionControl = other.mConnectionControl;
    memcpy(mPhoneNumber, other.mPhoneNumber, sizeof(mPhoneNumber));
    mNumRedials = other.mNumRedials;
    memcpy(mCommandString, other.mCommandString, sizeof(mCommandString));
    memcpy(mInitString, other.mInitString, sizeof(mInitString));
    mTimeoutLength = other.mTimeoutLength;
  }
  return *this;
}

BaseGPS1Setup::~BaseGPS1Setup() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BaseGPS1Setup::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("BaseGPS1Setup::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mBaseGPSInputType;
  stream >> mLineControl;
  stream >> mModemControl;
  stream >> mConnectionControl;
  for (size_t i = 0; i < sizeof(mPhoneNumber) / sizeof(mPhoneNumber[0]); ++i)
    stream >> mPhoneNumber[i];
  stream >> mNumRedials;
  for (size_t i = 0; i < sizeof(mCommandString) / sizeof(mCommandString[0]);
      ++i)
    stream >> mCommandString[i];
  for (size_t i = 0; i < sizeof(mInitString) / sizeof(mInitString[0]); ++i)
    stream >> mInitString[i];
  stream >> mTimeoutLength;
}

void BaseGPS1Setup::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mBaseGPSInputType;
  stream << mLineControl;
  stream << mModemControl;
  stream << mConnectionControl;
  for (size_t i = 0; i < sizeof(mPhoneNumber) / sizeof(mPhoneNumber[0]); ++i)
    stream << mPhoneNumber[i];
  stream << mNumRedials;
  for (size_t i = 0; i < sizeof(mCommandString) / sizeof(mCommandString[0]);
      ++i)
    stream << mCommandString[i];
  for (size_t i = 0; i < sizeof(mInitString) / sizeof(mInitString[0]); ++i)
    stream << mInitString[i];
  stream << mTimeoutLength;
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
