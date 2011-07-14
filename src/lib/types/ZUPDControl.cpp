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

#include "com/POSLVControl.h"

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

ZUPDControl::ZUPDControl(const ZUPDControl&
  other) :
  Message(other) {
}

ZUPDControl& ZUPDControl::operator =
  (const ZUPDControl& other) {
  this->Message::operator=(other);
  return *this;
}

ZUPDControl::~ZUPDControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void ZUPDControl::read(POSLVControl& stream) throw (IOException) {
  mChecksum = 19748 + 18259; // for $MSG
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("ZUPDControl::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTransactionNumber;
  mChecksum += mTransactionNumber;
  stream >> mControl;
  mChecksum += mControl;
  stream >> mDetectZeroVelocityThreshold;
  mChecksum += ((uint16_t*)&mDetectZeroVelocityThreshold)[0];
  mChecksum += ((uint16_t*)&mDetectZeroVelocityThreshold)[1];
  stream >> mRejectZeroVelocityThreshold;
  mChecksum += ((uint16_t*)&mRejectZeroVelocityThreshold)[0];
  mChecksum += ((uint16_t*)&mRejectZeroVelocityThreshold)[1];
  stream >> mZeroVelocityTestPeriod;
  mChecksum += ((uint16_t*)&mZeroVelocityTestPeriod)[0];
  mChecksum += ((uint16_t*)&mZeroVelocityTestPeriod)[1];
  stream >> mZUPDStd;
  mChecksum += ((uint16_t*)&mZUPDStd)[0];
  mChecksum += ((uint16_t*)&mZUPDStd)[1];
  mChecksum += 8996; // for $#
  mChecksum = 65536 - mChecksum;
}

void ZUPDControl::write(POSLVControl& stream) const {
  uint16_t checksum = 19748 + 18259; // for $MSG
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount;
  checksum += mByteCount;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mControl;
  checksum += mControl;
  stream << mDetectZeroVelocityThreshold;
  checksum += ((uint16_t*)&mDetectZeroVelocityThreshold)[0];
  checksum += ((uint16_t*)&mDetectZeroVelocityThreshold)[1];
  stream << mRejectZeroVelocityThreshold;
  checksum += ((uint16_t*)&mRejectZeroVelocityThreshold)[0];
  checksum += ((uint16_t*)&mRejectZeroVelocityThreshold)[1];
  stream << mZeroVelocityTestPeriod;
  checksum += ((uint16_t*)&mZeroVelocityTestPeriod)[0];
  checksum += ((uint16_t*)&mZeroVelocityTestPeriod)[1];
  stream << mZUPDStd;
  checksum += ((uint16_t*)&mZUPDStd)[0];
  checksum += ((uint16_t*)&mZUPDStd)[1];
  checksum += 8996; // for $#
  checksum = 65536 - checksum;
  stream << checksum;
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
