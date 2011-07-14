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

#include "types/DisplayPortControl.h"

#include "com/POSLVMessageRead.h"
#include "com/POSLVMessageWrite.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const DisplayPortControl DisplayPortControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

DisplayPortControl::DisplayPortControl() :
  Message(51) {
}

DisplayPortControl::DisplayPortControl(const DisplayPortControl& other) :
  Message(other) {
}

DisplayPortControl& DisplayPortControl::operator =
  (const DisplayPortControl& other) {
  this->Message::operator=(other);
  return *this;
}

DisplayPortControl::~DisplayPortControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void DisplayPortControl::read(POSLVMessageRead& stream) throw (IOException) {
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  mChecksum += mByteCount;
  stream >> mTransactionNumber;
  mChecksum += mTransactionNumber;
  stream >> mNumGroups;
  mChecksum += mNumGroups;
  size_t padSize = (mNumGroups % 2) * 2;
  if (byteCount != (mByteCount + (2 * mNumGroups) + padSize))
    throw IOException("DisplayPortControl::read(): wrong byte count");
  for (size_t i = 0; i < mNumGroups; i++) {
    uint16_t groupID;
    stream >> groupID;
    mGroupsIDVector.push_back(groupID);
    mChecksum += groupID;
  }
  stream >> mReserved;
  mChecksum += mReserved;
  if (padSize) {
    uint16_t pad;
    stream >> pad;
    mChecksum += pad;
    if (pad != 0)
      throw IOException("DisplayPortControl::read(): wrong pad");
  }
  mChecksum = 65536 - mChecksum;
}

void DisplayPortControl::write(POSLVMessageWrite& stream) const
  throw (IOException) {
  if (mGroupsIDVector.size() != mNumGroups)
    throw IOException("DisplayPortControl::write(): wrong number of groups");
  uint16_t checksum = mChecksum;
  stream << mTypeID;
  checksum += mTypeID;
  size_t padSize = (mNumGroups % 2) * 2;
  stream << mByteCount + (2 * mNumGroups) + padSize;
  checksum += mByteCount + (2 * mNumGroups) + padSize;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mNumGroups;
  checksum += mNumGroups;
  for (size_t i = 0; i < mGroupsIDVector.size(); i++) {
    stream << mGroupsIDVector[i];
    checksum += mGroupsIDVector[i];
  }
  stream << mReserved;
  checksum += mReserved;
  if (padSize) {
    uint16_t pad = 0;
    stream << pad;
    checksum += pad;
  }
  checksum = 65536 - checksum;
  stream << checksum;
}

void DisplayPortControl::read(std::istream& stream) {
}

void DisplayPortControl::write(std::ostream& stream) const {
}

void DisplayPortControl::read(std::ifstream& stream) {
}

void DisplayPortControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

DisplayPortControl* DisplayPortControl::clone() const {
  return new DisplayPortControl(*this);
}
