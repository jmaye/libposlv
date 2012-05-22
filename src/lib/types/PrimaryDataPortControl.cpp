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

#include "types/PrimaryDataPortControl.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const PrimaryDataPortControl PrimaryDataPortControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PrimaryDataPortControl::PrimaryDataPortControl() :
    Message(52) {
}

PrimaryDataPortControl::PrimaryDataPortControl(const PrimaryDataPortControl&
    other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mNumGroups(other.mNumGroups),
    mGroupsIDVector(other.mGroupsIDVector),
    mOutputRate(other.mOutputRate) {
}

PrimaryDataPortControl& PrimaryDataPortControl::operator =
    (const PrimaryDataPortControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mNumGroups = other.mNumGroups;
    mGroupsIDVector = other.mGroupsIDVector;
    mOutputRate = other.mOutputRate;
  }
  return *this;
}

PrimaryDataPortControl::~PrimaryDataPortControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void PrimaryDataPortControl::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  stream >> mTransactionNumber;
  stream >> mNumGroups;
  size_t padSize = (mNumGroups % 2) ? 0 : 2;
  if (byteCount != (mByteCount + (2 * mNumGroups) + padSize))
    throw IOException("PrimaryDataPortControl::read(): wrong byte count");
  for (size_t i = 0; i < mNumGroups; i++) {
    uint16_t groupID;
    stream >> groupID;
    mGroupsIDVector.push_back(groupID);
  }
  stream >> mOutputRate;
}

void PrimaryDataPortControl::write(BinaryWriter& stream) const {
  if (mGroupsIDVector.size() != mNumGroups)
    throw IOException("PrimaryDataPortControl::write(): wrong number of "
      "groups");
  stream << mTypeID;
  size_t padSize = (mNumGroups % 2) ? 0 : 2;
  stream << mByteCount + (2 * mNumGroups) + padSize;
  stream << mTransactionNumber;
  stream << mNumGroups;
  for (size_t i = 0; i < mGroupsIDVector.size(); i++)
    stream << mGroupsIDVector[i];
  stream << mOutputRate;
}

void PrimaryDataPortControl::read(std::istream& stream) {
}

void PrimaryDataPortControl::write(std::ostream& stream) const {
}

void PrimaryDataPortControl::read(std::ifstream& stream) {
}

void PrimaryDataPortControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

PrimaryDataPortControl* PrimaryDataPortControl::clone() const {
  return new PrimaryDataPortControl(*this);
}
