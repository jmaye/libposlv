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

#include "com/POSLVControl.h"

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
  Message(other) {
}

InstallationCalibrationControl& InstallationCalibrationControl::operator =
  (const InstallationCalibrationControl& other) {
  this->Message::operator=(other);
  return *this;
}

InstallationCalibrationControl::~InstallationCalibrationControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void InstallationCalibrationControl::read(POSLVControl& stream) {
}

void InstallationCalibrationControl::write(POSLVControl& stream) const {
  uint16_t checksum = 19748 + 18259; // for $MSG
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount;
  checksum += mByteCount;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mCalibrationAction;
  stream << mCalibrationSelect;
  checksum += ((mCalibrationSelect << 8) | mCalibrationAction);
  checksum += 8996; // for $#
  checksum = 65536 - checksum;
  stream << checksum;
}

void InstallationCalibrationControl::read(std::istream& stream) {
}

void InstallationCalibrationControl::write(std::ostream& stream) const {
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
