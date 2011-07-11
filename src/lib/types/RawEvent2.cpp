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

#include "types/RawEvent2.h"

#include "com/POSLVGroupRead.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const RawEvent2 RawEvent2::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

RawEvent2::RawEvent2() :
  Group(10005) {
}

RawEvent2::RawEvent2(const RawEvent2& other) :
  Group(other) {
}

RawEvent2& RawEvent2::operator = (const RawEvent2& other) {
  this->Group::operator=(other);
  return *this;
}

RawEvent2::~RawEvent2() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void RawEvent2::read(POSLVGroupRead& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("RawEvent2::read(): wrong byte count");

  stream >> mTimeDistance;
  stream >> mEvent2PulseCount;

  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("RawEvent2::read(): wrong pad");
}

void RawEvent2::read(std::istream& stream) {
}

void RawEvent2::write(std::ostream& stream) const {
}

void RawEvent2::read(std::ifstream& stream) {
}

void RawEvent2::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mEvent2PulseCount;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

RawEvent2* RawEvent2::clone() const {
  return new RawEvent2(*this);
}
