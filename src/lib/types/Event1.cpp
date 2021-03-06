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

#include "types/Event1.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const Event1 Event1::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Event1::Event1() :
    Group(5) {
}

Event1::Event1(const Event1& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mEventPulseNumber(other.mEventPulseNumber) {
}

Event1& Event1::operator = (const Event1& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    mEventPulseNumber = other.mEventPulseNumber;
  }
  return *this;
}

Event1::~Event1() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Event1::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("Event1::read(): wrong byte count");
  stream >> mTimeDistance;
  stream >> mEventPulseNumber;
}

void Event1::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTimeDistance;
  stream << mEventPulseNumber;
}

void Event1::read(std::istream& stream) {
}

void Event1::write(std::ostream& stream) const {
}

void Event1::read(std::ifstream& stream) {
}

void Event1::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mEventPulseNumber;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

Event1* Event1::clone() const {
  return new Event1(*this);
}
