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

#include "com/POSLVMessageRead.h"
#include "com/POSLVMessageWrite.h"

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
  Message(other) {
}

IPControl& IPControl::operator = (const IPControl& other) {
  this->Message::operator=(other);
  return *this;
}

IPControl::~IPControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void IPControl::read(POSLVMessageRead& stream) throw (IOException) {
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("IPControl::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTransactionNumber;
  mChecksum += mTransactionNumber;
  stream >> mNetworkPart1;
  stream >> mNetworkPart2;
  mChecksum += ((mNetworkPart2 << 8) | mNetworkPart1);
  stream >> mHostPart1;
  stream >> mHostPart2;
  mChecksum += ((mHostPart2 << 8) | mHostPart1);
  stream >> mSubNetworkPart1;
  stream >> mSubNetworkPart2;
  mChecksum += ((mSubNetworkPart2 << 8) | mSubNetworkPart1);
  stream >> mSubHostPart1;
  stream >> mSubHostPart2;
  mChecksum += ((mSubHostPart2 << 8) | mSubHostPart1);
  uint16_t pad = 0;
  stream >> pad;
  if (pad != 0)
    throw IOException("IPControl::read(): wrong pad");
  mChecksum += pad;
  mChecksum = 65536 - mChecksum;
}

void IPControl::write(POSLVMessageWrite& stream) const {
  uint16_t checksum = mChecksum;
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount;
  checksum += mByteCount;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mNetworkPart1;
  stream << mNetworkPart2;
  checksum += ((mNetworkPart2 << 8) | mNetworkPart1);
  stream << mHostPart1;
  stream << mHostPart2;
  checksum += ((mHostPart2 << 8) | mHostPart1);
  stream << mSubNetworkPart1;
  stream << mSubNetworkPart2;
  checksum += ((mSubNetworkPart2 << 8) | mSubNetworkPart1);
  stream << mSubHostPart1;
  stream << mSubHostPart2;
  checksum += ((mSubHostPart2 << 8) | mSubHostPart1);
  uint16_t pad = 0;
  stream << pad;
  checksum += pad;
  checksum = 65536 - checksum;
  stream << checksum;
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
