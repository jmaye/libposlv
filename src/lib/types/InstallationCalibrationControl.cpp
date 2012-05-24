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

#include "types/InstallationCalibrationControl.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const InstallationCalibrationControl InstallationCalibrationControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

InstallationCalibrationControl::InstallationCalibrationControl() :
    Message(57) {
}

InstallationCalibrationControl::InstallationCalibrationControl(const
    InstallationCalibrationControl& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mCalibrationAction(other.mCalibrationAction),
    mCalibrationSelect(other.mCalibrationSelect) {
}

InstallationCalibrationControl& InstallationCalibrationControl::operator =
    (const InstallationCalibrationControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mCalibrationAction = other.mCalibrationAction;
    mCalibrationSelect = other.mCalibrationSelect;
  }
  return *this;
}

InstallationCalibrationControl::~InstallationCalibrationControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void InstallationCalibrationControl::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("InstallationCalibrationControl::read(): "
      "wrong byte count");
  stream >> mTransactionNumber >> mCalibrationAction >> mCalibrationSelect;
}

void InstallationCalibrationControl::write(BinaryWriter& stream) const {
  stream << mTypeID << mByteCount << mTransactionNumber << mCalibrationAction
    << mCalibrationSelect;
}

void InstallationCalibrationControl::read(std::istream& stream) {
}

void InstallationCalibrationControl::write(std::ostream& stream) const {
  stream << mTypeID << std::endl
    << mByteCount << std::endl
    << mTransactionNumber << std::endl
    << (uint16_t)mCalibrationAction << std::endl
    << (uint16_t)mCalibrationSelect;
}

void InstallationCalibrationControl::read(std::ifstream& stream) {
}

void InstallationCalibrationControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

InstallationCalibrationControl* InstallationCalibrationControl::clone() const {
  return new InstallationCalibrationControl(*this);
}
