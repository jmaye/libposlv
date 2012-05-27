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

#include "types/EventDiscreteSetup.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const EventDiscreteSetup EventDiscreteSetup::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

EventDiscreteSetup::EventDiscreteSetup() :
    Message(33) {
}

EventDiscreteSetup::EventDiscreteSetup(const EventDiscreteSetup& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mEvent1Trigger(other.mEvent1Trigger),
    mEvent2Trigger(other.mEvent2Trigger) {
}

EventDiscreteSetup& EventDiscreteSetup::operator =
    (const EventDiscreteSetup& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mEvent1Trigger = other.mEvent1Trigger;
    mEvent2Trigger = other.mEvent2Trigger;
  }
  return *this;
}

EventDiscreteSetup::~EventDiscreteSetup() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void EventDiscreteSetup::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("EventDiscreteSetup::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mEvent1Trigger;
  stream >> mEvent2Trigger;
}

void EventDiscreteSetup::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mEvent1Trigger;
  stream << mEvent2Trigger;
}

void EventDiscreteSetup::read(std::istream& stream) {
}

void EventDiscreteSetup::write(std::ostream& stream) const {
}

void EventDiscreteSetup::read(std::ifstream& stream) {
}

void EventDiscreteSetup::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

EventDiscreteSetup* EventDiscreteSetup::clone() const {
  return new EventDiscreteSetup(*this);
}
