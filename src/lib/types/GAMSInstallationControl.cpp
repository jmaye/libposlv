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

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

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
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mAntennaSeparation(other.mAntennaSeparation),
    mBaselineX(other.mBaselineX),
    mBaselineY(other.mBaselineY),
    mBaselineZ(other.mBaselineZ),
    mMaxHeadingError(other.mMaxHeadingError),
    mHeadingCorrection(other.mHeadingCorrection) {
}

GAMSInstallationControl& GAMSInstallationControl::operator =
    (const GAMSInstallationControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mAntennaSeparation = other.mAntennaSeparation;
    mBaselineX = other.mBaselineX;
    mBaselineY = other.mBaselineY;
    mBaselineZ = other.mBaselineZ;
    mMaxHeadingError = other.mMaxHeadingError;
    mHeadingCorrection = other.mHeadingCorrection;
  }
  return *this;
}

GAMSInstallationControl::~GAMSInstallationControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GAMSInstallationControl::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("GAMSInstallationControl::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mAntennaSeparation;
  stream >> mBaselineX;
  stream >> mBaselineY;
  stream >> mBaselineZ;
  stream >> mMaxHeadingError;
  stream >> mHeadingCorrection;
}

void GAMSInstallationControl::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mAntennaSeparation;
  stream << mBaselineX;
  stream << mBaselineY;
  stream << mBaselineZ;
  stream << mMaxHeadingError;
  stream << mHeadingCorrection;
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
