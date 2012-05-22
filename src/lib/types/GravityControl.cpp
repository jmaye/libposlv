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

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

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
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mMagnitude(other.mMagnitude),
    mNorthDeflection(other.mNorthDeflection),
    mEastDeflection(other.mEastDeflection),
    mLatitudeValidity(other.mLatitudeValidity),
    mLongitudeValidity(other.mLongitudeValidity),
    mAltitudeValidity(other.mAltitudeValidity) {
}

GravityControl& GravityControl::operator = (const GravityControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mMagnitude = other.mMagnitude;
    mNorthDeflection = other.mNorthDeflection;
    mEastDeflection = other.mEastDeflection;
    mLatitudeValidity = other.mLatitudeValidity;
    mLongitudeValidity = other.mLongitudeValidity;
    mAltitudeValidity = other.mAltitudeValidity;
  }
  return *this;
}

GravityControl::~GravityControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GravityControl::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("GravityControl::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mMagnitude;
  stream >> mNorthDeflection;
  stream >> mEastDeflection;
  stream >> mLatitudeValidity;
  stream >> mLongitudeValidity;
  stream >> mAltitudeValidity;
}

void GravityControl::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mMagnitude;
  stream << mNorthDeflection;
  stream << mEastDeflection;
  stream << mLatitudeValidity;
  stream << mLongitudeValidity;
  stream << mAltitudeValidity;
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
