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

#include "types/PrimaryGPSReceiverDGPSStaDB.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const PrimaryGPSReceiverDGPSStaDB PrimaryGPSReceiverDGPSStaDB::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PrimaryGPSReceiverDGPSStaDB::PrimaryGPSReceiverDGPSStaDB() :
    Group(26) {
}

PrimaryGPSReceiverDGPSStaDB::PrimaryGPSReceiverDGPSStaDB(const
    PrimaryGPSReceiverDGPSStaDB& other) :
    Group(other),
    mReadByteCount(other.mReadByteCount),
    mTimeDistance(other.mTimeDistance),
    mStationNbr(other.mStationNbr) {
  memcpy(mStationRecord, other.mStationRecord, sizeof(mStationRecord));
}

PrimaryGPSReceiverDGPSStaDB& PrimaryGPSReceiverDGPSStaDB::operator =
    (const PrimaryGPSReceiverDGPSStaDB& other) {
  if (this != &other) {
    Group::operator=(other);
    mReadByteCount = other.mReadByteCount;
    mTimeDistance = other.mTimeDistance;
    memcpy(mStationRecord, other.mStationRecord, sizeof(mStationRecord));
    mStationNbr = other.mStationNbr;
  }
  return *this;
}

PrimaryGPSReceiverDGPSStaDB::~PrimaryGPSReceiverDGPSStaDB() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void PrimaryGPSReceiverDGPSStaDB::read(BinaryReader& stream) {
  stream >> mReadByteCount;
  stream >> mTimeDistance;
  mStationNbr = (mReadByteCount - mByteCount) / 24;
  for (size_t i = 0; i < mStationNbr; i++)
    stream >> mStationRecord[i];
}

void PrimaryGPSReceiverDGPSStaDB::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mReadByteCount;
  stream << mTimeDistance;
  for (size_t i = 0; i < mStationNbr; i++)
    stream << mStationRecord[i];
}

void PrimaryGPSReceiverDGPSStaDB::read(std::istream& stream) {
}

void PrimaryGPSReceiverDGPSStaDB::write(std::ostream& stream) const {
}

void PrimaryGPSReceiverDGPSStaDB::read(std::ifstream& stream) {
}

void PrimaryGPSReceiverDGPSStaDB::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  for (size_t i = 0; i < mStationNbr; i++)
    stream << mStationRecord[i];
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

PrimaryGPSReceiverDGPSStaDB* PrimaryGPSReceiverDGPSStaDB::clone() const {
  return new PrimaryGPSReceiverDGPSStaDB(*this);
}
