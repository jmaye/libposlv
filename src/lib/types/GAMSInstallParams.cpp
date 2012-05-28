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

#include "types/GAMSInstallParams.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const GAMSInstallParams GAMSInstallParams::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GAMSInstallParams::GAMSInstallParams() :
    Message(21) {
}

GAMSInstallParams::GAMSInstallParams(const GAMSInstallParams& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mAntennaSeparation(other.mAntennaSeparation),
    mBaselineX(other.mBaselineX),
    mBaselineY(other.mBaselineY),
    mBaselineZ(other.mBaselineZ),
    mMaxHeadingError(other.mMaxHeadingError),
    mHeadingCorrection(other.mHeadingCorrection) {
}

GAMSInstallParams& GAMSInstallParams::operator =
    (const GAMSInstallParams& other) {
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

GAMSInstallParams::~GAMSInstallParams() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GAMSInstallParams::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("GAMSInstallParams::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mAntennaSeparation;
  stream >> mBaselineX;
  stream >> mBaselineY;
  stream >> mBaselineZ;
  stream >> mMaxHeadingError;
  stream >> mHeadingCorrection;
}

void GAMSInstallParams::write(BinaryWriter& stream) const {
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

void GAMSInstallParams::read(std::istream& stream) {
}

void GAMSInstallParams::write(std::ostream& stream) const {
}

void GAMSInstallParams::read(std::ifstream& stream) {
}

void GAMSInstallParams::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

GAMSInstallParams* GAMSInstallParams::clone() const {
  return new GAMSInstallParams(*this);
}
