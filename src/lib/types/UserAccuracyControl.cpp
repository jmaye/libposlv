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

#include "types/UserAccuracyControl.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const UserAccuracyControl UserAccuracyControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

UserAccuracyControl::UserAccuracyControl() :
    Message(24) {
}

UserAccuracyControl::UserAccuracyControl(const UserAccuracyControl& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mAttitudeAccuracy(other.mAttitudeAccuracy),
    mHeadingAccuracy(other.mHeadingAccuracy),
    mPositionAccuracy(other.mPositionAccuracy),
    mVelocityAccuracy(other.mVelocityAccuracy) {
}

UserAccuracyControl& UserAccuracyControl::operator =
    (const UserAccuracyControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mAttitudeAccuracy = other.mAttitudeAccuracy;
    mHeadingAccuracy = other.mHeadingAccuracy;
    mPositionAccuracy = other.mPositionAccuracy;
    mVelocityAccuracy = other.mVelocityAccuracy;
  }
  return *this;
}

UserAccuracyControl::~UserAccuracyControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void UserAccuracyControl::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("UserAccuracyControl::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mAttitudeAccuracy;
  stream >> mHeadingAccuracy;
  stream >> mPositionAccuracy;
  stream >> mVelocityAccuracy;
}

void UserAccuracyControl::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mAttitudeAccuracy;
  stream << mHeadingAccuracy;
  stream << mPositionAccuracy;
  stream << mVelocityAccuracy;
}

void UserAccuracyControl::read(std::istream& stream) {
}

void UserAccuracyControl::write(std::ostream& stream) const {
}

void UserAccuracyControl::read(std::ifstream& stream) {
}

void UserAccuracyControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

UserAccuracyControl* UserAccuracyControl::clone() const {
  return new UserAccuracyControl(*this);
}
