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

#include "com/POSLVMessageRead.h"
#include "com/POSLVMessageWrite.h"

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
  Message(other) {
}

UserAccuracyControl& UserAccuracyControl::operator =
  (const UserAccuracyControl& other) {
  this->Message::operator=(other);
  return *this;
}

UserAccuracyControl::~UserAccuracyControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void UserAccuracyControl::read(POSLVMessageRead& stream) throw (IOException) {
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("UserAccuracyControl::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTransactionNumber;
  mChecksum += mTransactionNumber;
  stream >> mAttitudeAccuracy;
  mChecksum += ((uint16_t*)&mAttitudeAccuracy)[0];
  mChecksum += ((uint16_t*)&mAttitudeAccuracy)[1];
  stream >> mHeadingAccuracy;
  mChecksum += ((uint16_t*)&mHeadingAccuracy)[0];
  mChecksum += ((uint16_t*)&mHeadingAccuracy)[1];
  stream >> mPositionAccuracy;
  mChecksum += ((uint16_t*)&mPositionAccuracy)[0];
  mChecksum += ((uint16_t*)&mPositionAccuracy)[1];
  stream >> mVelocityAccuracy;
  mChecksum += ((uint16_t*)&mVelocityAccuracy)[0];
  mChecksum += ((uint16_t*)&mVelocityAccuracy)[1];
  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("UserAccuracyControl::read(): wrong pad");
  mChecksum += pad;
  mChecksum = 65536 - mChecksum;
}

void UserAccuracyControl::write(POSLVMessageWrite& stream) const {
  uint16_t checksum = mChecksum;
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount;
  checksum += mByteCount;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mAttitudeAccuracy;
  checksum += ((uint16_t*)&mAttitudeAccuracy)[0];
  checksum += ((uint16_t*)&mAttitudeAccuracy)[1];
  stream << mHeadingAccuracy;
  checksum += ((uint16_t*)&mHeadingAccuracy)[0];
  checksum += ((uint16_t*)&mHeadingAccuracy)[1];
  stream << mPositionAccuracy;
  checksum += ((uint16_t*)&mPositionAccuracy)[0];
  checksum += ((uint16_t*)&mPositionAccuracy)[1];
  stream << mVelocityAccuracy;
  checksum += ((uint16_t*)&mVelocityAccuracy)[0];
  checksum += ((uint16_t*)&mVelocityAccuracy)[1];
  uint16_t pad = 0;
  stream << pad;
  checksum += pad;
  checksum = 65536 - checksum;
  stream << checksum;
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
