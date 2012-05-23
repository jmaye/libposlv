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

#include "types/RawDMIDataStream.h"

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const RawDMIDataStream RawDMIDataStream::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

RawDMIDataStream::RawDMIDataStream() :
    Group(10006) {
}

RawDMIDataStream::RawDMIDataStream(const RawDMIDataStream& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mUpDownPulseCount(other.mUpDownPulseCount),
    mRectifiedPulseCount(other.mRectifiedPulseCount),
    mEventCount(other.mEventCount),
    mReservedCount(other.mReservedCount) {
}

RawDMIDataStream& RawDMIDataStream::operator =
    (const RawDMIDataStream& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    mUpDownPulseCount = other.mUpDownPulseCount;
    mRectifiedPulseCount = other.mRectifiedPulseCount;
    mEventCount = other.mEventCount;
    mReservedCount = other.mReservedCount;
  }
  return *this;
}

RawDMIDataStream::~RawDMIDataStream() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void RawDMIDataStream::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("RawDMIDataStream::read(): wrong byte count");
  stream >> mTimeDistance;
  stream >> mUpDownPulseCount;
  stream >> mRectifiedPulseCount;
  stream >> mEventCount;
  stream >> mReservedCount;
}

void RawDMIDataStream::write(BinaryWriter& stream) const {
}

void RawDMIDataStream::read(std::istream& stream) {
}

void RawDMIDataStream::write(std::ostream& stream) const {
}

void RawDMIDataStream::read(std::ifstream& stream) {
}

void RawDMIDataStream::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mUpDownPulseCount;
  stream << " ";
  stream << mRectifiedPulseCount;
  stream << " ";
  stream << mEventCount;
  stream << " ";
  stream << mReservedCount;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

RawDMIDataStream* RawDMIDataStream::clone() const {
  return new RawDMIDataStream(*this);
}
