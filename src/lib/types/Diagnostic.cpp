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

#include "types/Diagnostic.h"

#include "com/POSLVGroupRead.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const Diagnostic Diagnostic::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Diagnostic::Diagnostic() :
  Group(20000) {
}

Diagnostic::Diagnostic(const Diagnostic& other) :
  Group(other) {
}

Diagnostic& Diagnostic::operator = (const Diagnostic& other) {
  this->Group::operator=(other);
  return *this;
}

Diagnostic::~Diagnostic() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Diagnostic::read(POSLVGroupRead& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("Diagnostic::read(): wrong byte count");

  stream >> mTimeDistance;

  uint8_t byte;
  byteCount -= 30;
  for (size_t i = 0; i < byteCount; i++)
    stream >> byte;
}

void Diagnostic::read(std::istream& stream) {
}

void Diagnostic::write(std::ostream& stream) const {
}

void Diagnostic::read(std::ifstream& stream) {
}

void Diagnostic::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

Diagnostic* Diagnostic::clone() const {
  return new Diagnostic(*this);
}
