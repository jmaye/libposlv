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

#include "types/NavigationModeControl.h"

#include "com/POSLVControl.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const NavigationModeControl NavigationModeControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

NavigationModeControl::NavigationModeControl() :
  Message(50) {
}

NavigationModeControl::NavigationModeControl(const NavigationModeControl&
  other) :
  Message(other) {
}

NavigationModeControl& NavigationModeControl::operator =
  (const NavigationModeControl& other) {
  this->Message::operator=(other);
  return *this;
}

NavigationModeControl::~NavigationModeControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void NavigationModeControl::read(POSLVControl& stream) {
}

void NavigationModeControl::write(POSLVControl& stream) const {
  uint16_t checksum = 19748 + 18259; // for $MSG
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount;
  checksum += mByteCount;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mNavigationMode;
  uint8_t pad = 0;
  stream << pad;
  checksum += ((pad << 8) | mNavigationMode);
  checksum += 8996; // for $#
  checksum = 65536 - checksum;
  stream << checksum;
}

void NavigationModeControl::read(std::istream& stream) {
}

void NavigationModeControl::write(std::ostream& stream) const {
}

void NavigationModeControl::read(std::ifstream& stream) {
}

void NavigationModeControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

NavigationModeControl* NavigationModeControl::clone() const {
  return new NavigationModeControl(*this);
}
