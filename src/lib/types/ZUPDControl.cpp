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

#include "types/ZUPDControl.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const ZUPDControl ZUPDControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ZUPDControl::ZUPDControl() :
    Message(25) {
}

ZUPDControl::ZUPDControl(const ZUPDControl& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mControl(other.mControl),
    mDetectZeroVelocityThreshold(other.mDetectZeroVelocityThreshold),
    mRejectZeroVelocityThreshold(other.mRejectZeroVelocityThreshold),
    mZeroVelocityTestPeriod(other.mZeroVelocityTestPeriod),
    mZUPDStd(other.mZUPDStd) {
}

ZUPDControl& ZUPDControl::operator = (const ZUPDControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mControl = other.mControl;
    mDetectZeroVelocityThreshold = other.mDetectZeroVelocityThreshold;
    mRejectZeroVelocityThreshold = other.mRejectZeroVelocityThreshold;
    mZeroVelocityTestPeriod = other.mZeroVelocityTestPeriod;
    mZUPDStd = other.mZUPDStd;
  }
  return *this;
}

ZUPDControl::~ZUPDControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void ZUPDControl::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("ZUPDControl::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mControl;
  stream >> mDetectZeroVelocityThreshold;
  stream >> mRejectZeroVelocityThreshold;
  stream >> mZeroVelocityTestPeriod;
  stream >> mZUPDStd;
}

void ZUPDControl::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mControl;
  stream << mDetectZeroVelocityThreshold;
  stream << mRejectZeroVelocityThreshold;
  stream << mZeroVelocityTestPeriod;
  stream << mZUPDStd;
}

void ZUPDControl::read(std::istream& stream) {
}

void ZUPDControl::write(std::ostream& stream) const {
}

void ZUPDControl::read(std::ifstream& stream) {
}

void ZUPDControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

ZUPDControl* ZUPDControl::clone() const {
  return new ZUPDControl(*this);
}
