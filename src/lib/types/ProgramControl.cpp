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

#include "types/ProgramControl.h"

#include "com/POSLVControl.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const ProgramControl ProgramControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ProgramControl::ProgramControl() :
  Message(90) {
}

ProgramControl::ProgramControl(const ProgramControl&
  other) :
  Message(other) {
}

ProgramControl& ProgramControl::operator =
  (const ProgramControl& other) {
  this->Message::operator=(other);
  return *this;
}

ProgramControl::~ProgramControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void ProgramControl::read(POSLVControl& stream) {
}

void ProgramControl::write(POSLVControl& stream) const {
  uint16_t checksum = 9293 + 21319; // for $MSG
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount;
  checksum += mByteCount;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mControl;
  checksum += mControl;
  checksum += 9251; // for $#
  checksum = 65536 - checksum;
  stream << checksum;
}

void ProgramControl::read(std::istream& stream) {
}

void ProgramControl::write(std::ostream& stream) const {
}

void ProgramControl::read(std::ifstream& stream) {
}

void ProgramControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

ProgramControl* ProgramControl::clone() const {
  return new ProgramControl(*this);
}
