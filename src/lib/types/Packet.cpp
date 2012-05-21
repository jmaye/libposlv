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

#include "types/Packet.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Packet::Packet(const std::string& start) :
    mStart(start) {
}

Packet::Packet(const Packet& other) :
    mStart(other.mStart) {
}

Packet& Packet::operator = (const Packet& other) {
  if (this != &other) {
    mStart = other.mStart;
  }
  return *this;
}

Packet::~Packet() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const std::string& Packet::getStart() const {
  return mStart;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

BinaryReader& operator >> (BinaryReader& stream, Packet& obj) {
  obj.read(stream);
  return stream;
}
