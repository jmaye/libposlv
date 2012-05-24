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

#include "types/GAMSCalibrationControl.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const GAMSCalibrationControl GAMSCalibrationControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GAMSCalibrationControl::GAMSCalibrationControl() :
    Message(58) {
}

GAMSCalibrationControl::GAMSCalibrationControl(const
    GAMSCalibrationControl& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mCalibrationAction(other.mCalibrationAction) {
}

GAMSCalibrationControl& GAMSCalibrationControl::operator =
    (const GAMSCalibrationControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mCalibrationAction = other.mCalibrationAction;
  }
  return *this;
}

GAMSCalibrationControl::~GAMSCalibrationControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GAMSCalibrationControl::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("InstallationCalibrationControl::read(): "
      "wrong byte count");
  stream >> mTransactionNumber >> mCalibrationAction;
}

void GAMSCalibrationControl::write(BinaryWriter& stream) const {
  stream << mTypeID << mByteCount << mTransactionNumber << mCalibrationAction;
}

void GAMSCalibrationControl::read(std::istream& stream) {
}

void GAMSCalibrationControl::write(std::ostream& stream) const {
  stream << mTypeID << std::endl
    << mByteCount << std::endl
    << mTransactionNumber << std::endl
    << (uint16_t)mCalibrationAction;
}

void GAMSCalibrationControl::read(std::ifstream& stream) {
}

void GAMSCalibrationControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

GAMSCalibrationControl* GAMSCalibrationControl::clone() const {
  return new GAMSCalibrationControl(*this);
}
