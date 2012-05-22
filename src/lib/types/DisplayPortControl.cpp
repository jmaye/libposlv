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

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

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
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mNumGroups(other.mNumGroups),
    mGroupsIDVector(other.mGroupsIDVector),
    mReserved(other.mReserved) {
}

DisplayPortControl& DisplayPortControl::operator =
    (const DisplayPortControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mNumGroups = other.mNumGroups;
    mGroupsIDVector = other.mGroupsIDVector;
    mReserved = other.mReserved;
  }
  return *this;
}

DisplayPortControl::~DisplayPortControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void DisplayPortControl::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  stream >> mTransactionNumber;
  stream >> mNumGroups;
  size_t padSize = (mNumGroups % 2) ? 0 : 2;
  if (byteCount != (mByteCount + (2 * mNumGroups) + padSize))
    throw IOException("DisplayPortControl::read(): wrong byte count");
  for (size_t i = 0; i < mNumGroups; i++) {
    uint16_t groupID;
    stream >> groupID;
    mGroupsIDVector.push_back(groupID);
  }
  stream >> mReserved;
}

void DisplayPortControl::write(BinaryWriter& stream) const {
  if (mGroupsIDVector.size() != mNumGroups)
    throw IOException("DisplayPortControl::write(): wrong number of groups");
  stream << mTypeID;
  size_t padSize = (mNumGroups % 2) ? 0 : 2;
  stream << mByteCount + (2 * mNumGroups) + padSize;
  stream << mTransactionNumber;
  stream << mNumGroups;
  for (size_t i = 0; i < mGroupsIDVector.size(); i++)
    stream << mGroupsIDVector[i];
  stream << mReserved;
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
