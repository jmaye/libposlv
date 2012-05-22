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

#include "types/IPControl.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const IPControl IPControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

IPControl::IPControl() :
    Message(32) {
}

IPControl::IPControl(const IPControl& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mNetworkPart1(other.mNetworkPart1),
    mNetworkPart2(other.mNetworkPart2),
    mHostPart1(other.mHostPart1),
    mHostPart2(other.mHostPart2),
    mSubNetworkPart1(other.mSubNetworkPart1),
    mSubNetworkPart2(other.mSubNetworkPart2),
    mSubHostPart1(other.mSubHostPart1),
    mSubHostPart2(other.mSubHostPart2) {
}

IPControl& IPControl::operator = (const IPControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mNetworkPart1 = other.mNetworkPart1;
    mNetworkPart2 = other.mNetworkPart2;
    mHostPart1 = other.mHostPart1;
    mHostPart2 = other.mHostPart2;
    mSubNetworkPart1 = other.mSubNetworkPart1;
    mSubNetworkPart2 = other.mSubNetworkPart2;
    mSubHostPart1 = other.mSubHostPart1;
    mSubHostPart2 = other.mSubHostPart2;
  }
  return *this;
}

IPControl::~IPControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void IPControl::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("IPControl::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mNetworkPart1;
  stream >> mNetworkPart2;
  stream >> mHostPart1;
  stream >> mHostPart2;
  stream >> mSubNetworkPart1;
  stream >> mSubNetworkPart2;
  stream >> mSubHostPart1;
  stream >> mSubHostPart2;
}

void IPControl::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mNetworkPart1;
  stream << mNetworkPart2;
  stream << mHostPart1;
  stream << mHostPart2;
  stream << mSubNetworkPart1;
  stream << mSubNetworkPart2;
  stream << mSubHostPart1;
  stream << mSubHostPart2;
}

void IPControl::read(std::istream& stream) {
}

void IPControl::write(std::ostream& stream) const {
}

void IPControl::read(std::ifstream& stream) {
}

void IPControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

IPControl* IPControl::clone() const {
  return new IPControl(*this);
}
