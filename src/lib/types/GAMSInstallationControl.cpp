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

#include "types/GAMSInstallationControl.h"

#include "com/POSLVControl.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const GAMSInstallationControl GAMSInstallationControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GAMSInstallationControl::GAMSInstallationControl() :
  Message(21) {
}

GAMSInstallationControl::GAMSInstallationControl(const GAMSInstallationControl&
  other) :
  Message(other) {
}

GAMSInstallationControl& GAMSInstallationControl::operator =
  (const GAMSInstallationControl& other) {
  this->Message::operator=(other);
  return *this;
}

GAMSInstallationControl::~GAMSInstallationControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GAMSInstallationControl::read(POSLVControl& stream) throw (IOException) {
  mChecksum = 19748 + 18259; // for $MSG
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("GAMSInstallationControl::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTransactionNumber;
  mChecksum += mTransactionNumber;
  stream >> mAntennaSeparation;
  mChecksum += ((uint16_t*)&mAntennaSeparation)[0];
  mChecksum += ((uint16_t*)&mAntennaSeparation)[1];
  stream >> mBaselineX;
  mChecksum += ((uint16_t*)&mBaselineX)[0];
  mChecksum += ((uint16_t*)&mBaselineX)[1];
  stream >> mBaselineY;
  mChecksum += ((uint16_t*)&mBaselineY)[0];
  mChecksum += ((uint16_t*)&mBaselineY)[1];
  stream >> mBaselineZ;
  mChecksum += ((uint16_t*)&mBaselineZ)[0];
  mChecksum += ((uint16_t*)&mBaselineZ)[1];
  stream >> mMaxHeadingError;
  mChecksum += ((uint16_t*)&mMaxHeadingError)[0];
  mChecksum += ((uint16_t*)&mMaxHeadingError)[1];
  stream >> mHeadingCorrection;
  mChecksum += ((uint16_t*)&mHeadingCorrection)[0];
  mChecksum += ((uint16_t*)&mHeadingCorrection)[1];
  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("GAMSInstallationControl::read(): wrong pad");
  mChecksum += pad;
  mChecksum += 8996; // for $#
  mChecksum = 65536 - mChecksum;
}

void GAMSInstallationControl::write(POSLVControl& stream) const {
  uint16_t checksum = 19748 + 18259; // for $MSG
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount;
  checksum += mByteCount;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mAntennaSeparation;
  checksum += ((uint16_t*)&mAntennaSeparation)[0];
  checksum += ((uint16_t*)&mAntennaSeparation)[1];
  stream << mBaselineX;
  checksum += ((uint16_t*)&mBaselineX)[0];
  checksum += ((uint16_t*)&mBaselineX)[1];
  stream << mBaselineY;
  checksum += ((uint16_t*)&mBaselineY)[0];
  checksum += ((uint16_t*)&mBaselineY)[1];
  stream << mBaselineZ;
  checksum += ((uint16_t*)&mBaselineZ)[0];
  checksum += ((uint16_t*)&mBaselineZ)[1];
  stream << mMaxHeadingError;
  checksum += ((uint16_t*)&mMaxHeadingError)[0];
  checksum += ((uint16_t*)&mMaxHeadingError)[1];
  stream << mHeadingCorrection;
  checksum += ((uint16_t*)&mHeadingCorrection)[0];
  checksum += ((uint16_t*)&mHeadingCorrection)[1];
  uint16_t pad = 0;
  stream << pad;
  checksum += pad;
  checksum += 8996; // for $#
  checksum = 65536 - checksum;
  stream << checksum;
}

void GAMSInstallationControl::read(std::istream& stream) {
}

void GAMSInstallationControl::write(std::ostream& stream) const {
}

void GAMSInstallationControl::read(std::ifstream& stream) {
}

void GAMSInstallationControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

GAMSInstallationControl* GAMSInstallationControl::clone() const {
  return new GAMSInstallationControl(*this);
}
