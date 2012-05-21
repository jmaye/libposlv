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

#include "types/Event2.h"

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const Event2 Event2::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Event2::Event2() :
    Group(6) {
}

Event2::Event2(const Event2& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mEventPulseNumber(other.mEventPulseNumber) {
}

Event2& Event2::operator = (const Event2& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    mEventPulseNumber = other.mEventPulseNumber;
  }
  return *this;
}

Event2::~Event2() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Event2::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("Event2::read(): wrong byte count");
  stream >> mTimeDistance;
  stream >> mEventPulseNumber;
  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("Event2::read(): wrong pad");
}

void Event2::read(std::istream& stream) {
}

void Event2::write(std::ostream& stream) const {
}

void Event2::read(std::ifstream& stream) {
}

void Event2::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mEventPulseNumber;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

Event2* Event2::clone() const {
  return new Event2(*this);
}
