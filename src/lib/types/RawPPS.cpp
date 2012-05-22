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

#include "types/RawPPS.h"

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const RawPPS RawPPS::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

RawPPS::RawPPS() :
    Group(10003) {
}

RawPPS::RawPPS(const RawPPS& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mPPSPulseCount(other.mPPSPulseCount) {
}

RawPPS& RawPPS::operator = (const RawPPS& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    mPPSPulseCount = other.mPPSPulseCount;
  }
  return *this;
}

RawPPS::~RawPPS() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void RawPPS::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("RawPPS::read(): wrong byte count");
  stream >> mTimeDistance;
  stream >> mPPSPulseCount;
}

void RawPPS::read(std::istream& stream) {
}

void RawPPS::write(std::ostream& stream) const {
}

void RawPPS::read(std::ifstream& stream) {
}

void RawPPS::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mPPSPulseCount;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

RawPPS* RawPPS::clone() const {
  return new RawPPS(*this);
}
