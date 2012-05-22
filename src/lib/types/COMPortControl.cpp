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

#include "types/COMPortControl.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const COMPortControl COMPortControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

COMPortControl::COMPortControl() :
    Message(34) {
}

COMPortControl::COMPortControl(const COMPortControl& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mNumPorts(other.mNumPorts),
    mPortMask(other.mPortMask) {
  memcpy(mpParameters, other.mpParameters, sizeof(mpParameters));
}

COMPortControl& COMPortControl::operator = (const COMPortControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mNumPorts = other.mNumPorts;
    memcpy(mpParameters, other.mpParameters, sizeof(mpParameters));
    mPortMask = other.mPortMask;
  }
  return *this;
}

COMPortControl::~COMPortControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void COMPortControl::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  stream >> mTransactionNumber;
  stream >> mNumPorts;
  if (byteCount != mByteCount + (8 * mNumPorts))
    throw IOException("COMPortControl::read(): wrong byte count");
  for (size_t i = 0; i < mNumPorts; i++)
    stream >> mpParameters[i];
  stream >> mPortMask;
}

void COMPortControl::write(BinaryWriter& stream) const {
  if (mNumPorts > 10)
    throw IOException("COMPortControl::write(): 10 COM ports maximum");
  stream << mTypeID;
  stream << mByteCount + (8 * mNumPorts);
  stream << mTransactionNumber;
  stream << mNumPorts;
  for (size_t i = 0; i < mNumPorts; i++)
    stream << mpParameters[i];
  stream << mPortMask;
}

void COMPortControl::read(std::istream& stream) {
}

void COMPortControl::write(std::ostream& stream) const {
}

void COMPortControl::read(std::ifstream& stream) {
}

void COMPortControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

COMPortControl* COMPortControl::clone() const {
  return new COMPortControl(*this);
}
