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

#include "types/RawEvent1.h"

#include "com/POSLVGroupRead.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const RawEvent1 RawEvent1::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

RawEvent1::RawEvent1() :
  Group(10004) {
}

RawEvent1::RawEvent1(const RawEvent1 &other) : Group(other) {
}

RawEvent1& RawEvent1::operator = (const RawEvent1& other) {
  this->Group::operator=(other);
  return *this;
}

RawEvent1::~RawEvent1() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void RawEvent1::read(POSLVGroupRead& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("RawEvent1::read(): wrong byte count");

  stream >> mTimeDistance;
  stream >> mEvent1PulseCount;

  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("RawEvent1::read(): wrong pad");
}

void RawEvent1::read(std::istream& stream) {
}

void RawEvent1::write(std::ostream& stream) const {
}

void RawEvent1::read(std::ifstream& stream) {
}

void RawEvent1::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mEvent1PulseCount;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

RawEvent1* RawEvent1::clone() const {
  return new RawEvent1(*this);
}
