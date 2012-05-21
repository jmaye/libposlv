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

#include "types/COMPortParameters.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

COMPortParameters::COMPortParameters() {
}

COMPortParameters::COMPortParameters(const COMPortParameters& other) :
    mBaudrate(other.mBaudrate),
    mParity(other.mParity),
    mDataStopBits(other.mDataStopBits),
    mFlowControl(other.mFlowControl),
    mInputSelect(other.mInputSelect),
    mOutputSelect(other.mOutputSelect) {
}

COMPortParameters& COMPortParameters::operator =
    (const COMPortParameters& other) {
  if (this != &other) {
    mBaudrate = other.mBaudrate;
    mParity = other.mParity;
    mDataStopBits = other.mDataStopBits;
    mFlowControl = other.mFlowControl;
    mInputSelect = other.mInputSelect;
    mOutputSelect = other.mOutputSelect;
  }
  return *this;
}

COMPortParameters::~COMPortParameters() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void COMPortParameters::read(BinaryReader& stream) {
  stream >> mBaudrate;
  stream >> mParity;
  stream >> mDataStopBits;
  stream >> mFlowControl;
  stream >> mInputSelect;
  stream >> mOutputSelect;
}

void COMPortParameters::write(BinaryWriter& stream) const {
  stream << mBaudrate;
  stream << mParity;
  stream << mDataStopBits;
  stream << mFlowControl;
  stream << mInputSelect;
  stream << mOutputSelect;
}

void COMPortParameters::read(std::istream& stream) {
}

void COMPortParameters::write(std::ostream& stream) const {
}

void COMPortParameters::read(std::ifstream& stream) {
}

void COMPortParameters::write(std::ofstream& stream) const {
}

BinaryReader& operator >> (BinaryReader& stream, COMPortParameters&
    obj) {
  obj.read(stream);
  return stream;
}

BinaryWriter& operator << (BinaryWriter& stream, const
    COMPortParameters& obj) {
  obj.write(stream);
  return stream;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

uint16_t COMPortParameters::getChecksum() const {
  uint16_t checksum = (mParity << 8) | mBaudrate;
  checksum += (mFlowControl << 8) | mDataStopBits;
  checksum += mInputSelect;
  checksum += mOutputSelect;
  return checksum;
}
