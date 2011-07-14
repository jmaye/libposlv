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

#include "types/GravityControl.h"

#include "com/POSLVMessageRead.h"
#include "com/POSLVMessageWrite.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const GravityControl GravityControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GravityControl::GravityControl() :
  Message(40) {
}

GravityControl::GravityControl(const GravityControl& other) :
  Message(other) {
}

GravityControl& GravityControl::operator = (const GravityControl& other) {
  this->Message::operator=(other);
  return *this;
}

GravityControl::~GravityControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GravityControl::read(POSLVMessageRead& stream) throw (IOException) {
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("GravityControl::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTransactionNumber;
  mChecksum += mTransactionNumber;
  stream >> mMagnitude;
  mChecksum += ((uint16_t*)&mMagnitude)[0];
  mChecksum += ((uint16_t*)&mMagnitude)[1];
  mChecksum += ((uint16_t*)&mMagnitude)[2];
  mChecksum += ((uint16_t*)&mMagnitude)[3];
  stream >> mNorthDeflection;
  mChecksum += ((uint16_t*)&mNorthDeflection)[0];
  mChecksum += ((uint16_t*)&mNorthDeflection)[1];
  mChecksum += ((uint16_t*)&mNorthDeflection)[2];
  mChecksum += ((uint16_t*)&mNorthDeflection)[3];
  stream >> mEastDeflection;
  mChecksum += ((uint16_t*)&mEastDeflection)[0];
  mChecksum += ((uint16_t*)&mEastDeflection)[1];
  mChecksum += ((uint16_t*)&mEastDeflection)[2];
  mChecksum += ((uint16_t*)&mEastDeflection)[3];
  stream >> mLatitudeValidity;
  mChecksum += ((uint16_t*)&mLatitudeValidity)[0];
  mChecksum += ((uint16_t*)&mLatitudeValidity)[1];
  mChecksum += ((uint16_t*)&mLatitudeValidity)[2];
  mChecksum += ((uint16_t*)&mLatitudeValidity)[3];
  stream >> mLongitudeValidity;
  mChecksum += ((uint16_t*)&mLongitudeValidity)[0];
  mChecksum += ((uint16_t*)&mLongitudeValidity)[1];
  mChecksum += ((uint16_t*)&mLongitudeValidity)[2];
  mChecksum += ((uint16_t*)&mLongitudeValidity)[3];
  stream >> mAltitudeValidity;
  mChecksum += ((uint16_t*)&mAltitudeValidity)[0];
  mChecksum += ((uint16_t*)&mAltitudeValidity)[1];
  mChecksum += ((uint16_t*)&mAltitudeValidity)[2];
  mChecksum += ((uint16_t*)&mAltitudeValidity)[3];
  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("GravityControl::read(): wrong pad");
  mChecksum += pad;
  mChecksum = 65536 - mChecksum;
}

void GravityControl::write(POSLVMessageWrite& stream) const {
  uint16_t checksum = mChecksum;
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount;
  checksum += mByteCount;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mMagnitude;
  checksum += ((uint16_t*)&mMagnitude)[0];
  checksum += ((uint16_t*)&mMagnitude)[1];
  checksum += ((uint16_t*)&mMagnitude)[2];
  checksum += ((uint16_t*)&mMagnitude)[3];
  stream << mNorthDeflection;
  checksum += ((uint16_t*)&mNorthDeflection)[0];
  checksum += ((uint16_t*)&mNorthDeflection)[1];
  checksum += ((uint16_t*)&mNorthDeflection)[2];
  checksum += ((uint16_t*)&mNorthDeflection)[3];
  stream << mEastDeflection;
  checksum += ((uint16_t*)&mEastDeflection)[0];
  checksum += ((uint16_t*)&mEastDeflection)[1];
  checksum += ((uint16_t*)&mEastDeflection)[2];
  checksum += ((uint16_t*)&mEastDeflection)[3];
  stream << mLatitudeValidity;
  checksum += ((uint16_t*)&mLatitudeValidity)[0];
  checksum += ((uint16_t*)&mLatitudeValidity)[1];
  checksum += ((uint16_t*)&mLatitudeValidity)[2];
  checksum += ((uint16_t*)&mLatitudeValidity)[3];
  stream << mLongitudeValidity;
  checksum += ((uint16_t*)&mLongitudeValidity)[0];
  checksum += ((uint16_t*)&mLongitudeValidity)[1];
  checksum += ((uint16_t*)&mLongitudeValidity)[2];
  checksum += ((uint16_t*)&mLongitudeValidity)[3];
  stream << mAltitudeValidity;
  checksum += ((uint16_t*)&mAltitudeValidity)[0];
  checksum += ((uint16_t*)&mAltitudeValidity)[1];
  checksum += ((uint16_t*)&mAltitudeValidity)[2];
  checksum += ((uint16_t*)&mAltitudeValidity)[3];
  uint16_t pad = 0;
  stream << pad;
  checksum += pad;
  checksum = 65536 - checksum;
  stream << checksum;
}

void GravityControl::read(std::istream& stream) {
}

void GravityControl::write(std::ostream& stream) const {
}

void GravityControl::read(std::ifstream& stream) {
}

void GravityControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

GravityControl* GravityControl::clone() const {
  return new GravityControl(*this);
}
