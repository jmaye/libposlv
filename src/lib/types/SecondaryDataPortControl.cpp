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

#include "types/SecondaryDataPortControl.h"

#include "com/POSLVMessageRead.h"
#include "com/POSLVMessageWrite.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const SecondaryDataPortControl SecondaryDataPortControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SecondaryDataPortControl::SecondaryDataPortControl() :
  Message(61) {
}

SecondaryDataPortControl::SecondaryDataPortControl(const
  SecondaryDataPortControl& other) :
  Message(other) {
}

SecondaryDataPortControl& SecondaryDataPortControl::operator =
  (const SecondaryDataPortControl& other) {
  this->Message::operator=(other);
  return *this;
}

SecondaryDataPortControl::~SecondaryDataPortControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void SecondaryDataPortControl::read(POSLVMessageRead& stream)
  throw (IOException) {
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  mChecksum += byteCount;
  stream >> mTransactionNumber;
  mChecksum += mTransactionNumber;
  stream >> mNumGroups;
  mChecksum += mNumGroups;
  size_t padSize = (mNumGroups % 2) ? 0 : 2;
  if (byteCount != (mByteCount + (2 * mNumGroups) + padSize))
    throw IOException("SecondaryDataPortControl::read(): wrong byte count");
  for (size_t i = 0; i < mNumGroups; i++) {
    uint16_t groupID;
    stream >> groupID;
    mGroupsIDVector.push_back(groupID);
    mChecksum += groupID;
  }
  stream >> mOutputRate;
  mChecksum += mOutputRate;
  if (padSize) {
    uint16_t pad;
    stream >> pad;
    mChecksum += pad;
    if (pad != 0)
      throw IOException("SecondaryDataPortControl::read(): wrong pad");
  }
  mChecksum = 65536 - mChecksum;
}

void SecondaryDataPortControl::write(POSLVMessageWrite& stream) const
  throw (IOException) {
  if (mGroupsIDVector.size() != mNumGroups)
    throw IOException("SecondaryDataPortControl::write(): wrong number of groups");
  uint16_t checksum = mChecksum;
  stream << mTypeID;
  checksum += mTypeID;
  size_t padSize = (mNumGroups % 2) ? 0 : 2;
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
  stream << mOutputRate;
  checksum += mOutputRate;
  if (padSize) {
    uint16_t pad = 0;
    stream << pad;
    checksum += pad;
  }
  checksum = 65536 - checksum;
  stream << checksum;
}

void SecondaryDataPortControl::read(std::istream& stream) {
}

void SecondaryDataPortControl::write(std::ostream& stream) const {
}

void SecondaryDataPortControl::read(std::ifstream& stream) {
}

void SecondaryDataPortControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

SecondaryDataPortControl* SecondaryDataPortControl::clone() const {
  return new SecondaryDataPortControl(*this);
}
