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

#include "types/Acknowledge.h"

#include "com/POSLVMessageRead.h"
#include "com/POSLVMessageWrite.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const Acknowledge Acknowledge::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Acknowledge::Acknowledge() :
  Message(0) {
}

Acknowledge::Acknowledge(const Acknowledge& other) :
  Message(other) {
}

Acknowledge& Acknowledge::operator = (const Acknowledge& other) {
  this->Message::operator=(other);
  return *this;
}

Acknowledge::~Acknowledge() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Acknowledge::read(POSLVMessageRead& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("Acknowledge::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mID;
  stream >> mResponseCode;
  stream >> mNewParamsStatus;
  for (size_t i = 0; i < 32; i++)
    stream >> mParameterName[i];
  uint8_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("Acknowledge::read(): wrong pad");
}

void Acknowledge::write(POSLVMessageWrite& stream) const {
}

void Acknowledge::read(std::istream& stream) {
}

void Acknowledge::write(std::ostream& stream) const {
}

void Acknowledge::read(std::ifstream& stream) {
}

void Acknowledge::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

Acknowledge* Acknowledge::clone() const {
  return new Acknowledge(*this);
}
