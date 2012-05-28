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

#include "types/UserAccuracySpec.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const UserAccuracySpec UserAccuracySpec::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

UserAccuracySpec::UserAccuracySpec() :
    Message(24) {
}

UserAccuracySpec::UserAccuracySpec(const UserAccuracySpec& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mAttitudeAccuracy(other.mAttitudeAccuracy),
    mHeadingAccuracy(other.mHeadingAccuracy),
    mPositionAccuracy(other.mPositionAccuracy),
    mVelocityAccuracy(other.mVelocityAccuracy) {
}

UserAccuracySpec& UserAccuracySpec::operator = (const UserAccuracySpec& other) {
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

UserAccuracySpec::~UserAccuracySpec() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void UserAccuracySpec::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("UserAccuracySpec::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mAttitudeAccuracy;
  stream >> mHeadingAccuracy;
  stream >> mPositionAccuracy;
  stream >> mVelocityAccuracy;
}

void UserAccuracySpec::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mAttitudeAccuracy;
  stream << mHeadingAccuracy;
  stream << mPositionAccuracy;
  stream << mVelocityAccuracy;
}

void UserAccuracySpec::read(std::istream& stream) {
}

void UserAccuracySpec::write(std::ostream& stream) const {
}

void UserAccuracySpec::read(std::ifstream& stream) {
}

void UserAccuracySpec::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

UserAccuracySpec* UserAccuracySpec::clone() const {
  return new UserAccuracySpec(*this);
}
