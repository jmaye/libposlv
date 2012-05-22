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

#include "types/Group.h"

#include "base/Factory.h"
#include "base/BinaryReader.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Group::Group(uint16_t typeID) :
    Packet("$GRP"),
    mTypeID(typeID) {
    Factory<uint16_t, Group>::getInstance().registerType(this, mTypeID);
}

Group::Group(const Group& other) :
    Packet(other),
    mTypeID(other.mTypeID) {
}

Group& Group::operator = (const Group& other) {
  if (this != &other) {
    Packet::operator=(other);
    mTypeID = other.mTypeID;
  }
  return *this;
}

Group::~Group() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

uint16_t Group::getTypeID() const {
  return mTypeID;
}
