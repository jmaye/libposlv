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

#include "com/POSLVControl.h"

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
  Message(other) {
}

GAMSCalibrationControl& GAMSCalibrationControl::operator =
  (const GAMSCalibrationControl& other) {
  this->Message::operator=(other);
  return *this;
}

GAMSCalibrationControl::~GAMSCalibrationControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GAMSCalibrationControl::read(POSLVControl& stream) {
}

void GAMSCalibrationControl::write(POSLVControl& stream) const {
  uint16_t checksum = 19748 + 18259; // for $MSG
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount;
  checksum += mByteCount;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mCalibrationAction;
  uint8_t pad = 0;
  stream << pad;
  checksum += ((pad << 8) | mCalibrationAction);
  checksum += 8996; // for $#
  checksum = 65536 - checksum;
  stream << checksum;
}

void GAMSCalibrationControl::read(std::istream& stream) {
}

void GAMSCalibrationControl::write(std::ostream& stream) const {
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
