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

#include "com/POSLVControl.h"

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
  Message(other) {
}

COMPortControl& COMPortControl::operator = (const COMPortControl& other) {
  this->Message::operator=(other);
  return *this;
}

COMPortControl::~COMPortControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void COMPortControl::read(POSLVControl& stream) throw (IOException) {
  mChecksum = 19748 + 18259; // for $MSG
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  mChecksum += mByteCount;
  stream >> mTransactionNumber;
  mChecksum += mTransactionNumber;
  stream >> mNumPorts;
  mChecksum += mNumPorts;
  if (byteCount != mByteCount + (8 * mNumPorts))
    throw IOException("COMPortControl::read(): wrong byte count");
  for (size_t i = 0; i < mNumPorts; i++) {
    stream >> mpParameters[i];
    mChecksum += mpParameters[i].getChecksum();
  }
  stream >> mPortMask;
  mChecksum += mPortMask;
  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("COMPortControl::read(): wrong pad");
  mChecksum += pad;
  mChecksum += 8996; // for $#
  mChecksum = 65536 - mChecksum;
}

void COMPortControl::write(POSLVControl& stream) const throw (IOException) {
  if (mNumPorts > 10)
    throw IOException("COMPortControl::write(): 10 COM ports maximum");
  uint16_t checksum = 19748 + 18259; // for $MSG
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount + (8 * mNumPorts);
  checksum += mByteCount + (8 * mNumPorts);
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mNumPorts;
  checksum += mNumPorts;
  for (size_t i = 0; i < mNumPorts; i++) {
    stream << mpParameters[i];
    checksum += mpParameters[i].getChecksum();
  }
  stream << mPortMask;
  checksum += mPortMask;
  uint16_t pad = 0;
  stream << pad;
  checksum += pad;
  checksum += 8996; // for $#
  checksum = 65536 - checksum;
  stream << checksum;
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
