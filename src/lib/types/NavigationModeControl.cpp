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

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

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
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mNavigationMode(other.mNavigationMode) {
}

NavigationModeControl& NavigationModeControl::operator =
    (const NavigationModeControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mNavigationMode = other.mNavigationMode;
  }
  return *this;
}

NavigationModeControl::~NavigationModeControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void NavigationModeControl::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("NavigationModeControl::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mNavigationMode;
}

void NavigationModeControl::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mNavigationMode;
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
