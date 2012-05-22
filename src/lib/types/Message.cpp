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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "types/Message.h"

#include "base/Factory.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Message::Message(uint16_t typeID) :
    Packet("$MSG"),
    mTypeID(typeID) {
  Factory<uint16_t, Message>::getInstance().registerType(this, mTypeID);
}

Message::Message(const Message& other) :
    Packet(other),
    mTypeID(other.mTypeID) {
}

Message& Message::operator = (const Message& other) {
  if (this != &other) {
    Packet::operator=(other);
    mTypeID = other.mTypeID;
  }
  return *this;
}

Message::~Message() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

uint16_t Message::getTypeID() const {
  return mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

BinaryWriter& operator << (BinaryWriter& stream, const Message& obj) {
  obj.write(stream);
  return stream;
}
