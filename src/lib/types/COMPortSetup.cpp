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

#include "types/COMPortSetup.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const COMPortSetup COMPortSetup::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

COMPortSetup::COMPortSetup() :
    Message(34) {
}

COMPortSetup::COMPortSetup(const COMPortSetup& other) :
    Message(other),
    mReadByteCount(other.mReadByteCount),
    mTransactionNumber(other.mTransactionNumber),
    mNumPorts(other.mNumPorts),
    mPortMask(other.mPortMask) {
  memcpy(mpParameters, other.mpParameters, sizeof(mpParameters));
}

COMPortSetup& COMPortSetup::operator = (const COMPortSetup& other) {
  if (this != &other) {
    Message::operator=(other);
    mReadByteCount = other.mReadByteCount;
    mTransactionNumber = other.mTransactionNumber;
    mNumPorts = other.mNumPorts;
    memcpy(mpParameters, other.mpParameters, sizeof(mpParameters));
    mPortMask = other.mPortMask;
  }
  return *this;
}

COMPortSetup::~COMPortSetup() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void COMPortSetup::read(BinaryReader& stream) {
  stream >> mReadByteCount;
  stream >> mTransactionNumber;
  stream >> mNumPorts;
  if (mReadByteCount != mByteCount + (8 * mNumPorts))
    throw IOException("COMPortSetup::read(): wrong byte count");
  for (size_t i = 0; i < mNumPorts; i++)
    stream >> mpParameters[i];
  stream >> mPortMask;
}

void COMPortSetup::write(BinaryWriter& stream) const {
  if (mNumPorts > 10)
    throw IOException("COMPortSetup::write(): 10 COM ports maximum");
  stream << mTypeID;
  stream << mReadByteCount;
  stream << mTransactionNumber;
  stream << mNumPorts;
  for (size_t i = 0; i < mNumPorts; i++)
    stream << mpParameters[i];
  stream << mPortMask;
}

void COMPortSetup::read(std::istream& stream) {
}

void COMPortSetup::write(std::ostream& stream) const {
}

void COMPortSetup::read(std::ifstream& stream) {
}

void COMPortSetup::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

COMPortSetup* COMPortSetup::clone() const {
  return new COMPortSetup(*this);
}
