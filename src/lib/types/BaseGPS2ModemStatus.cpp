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

#include "types/BaseGPS2ModemStatus.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const BaseGPS2ModemStatus BaseGPS2ModemStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BaseGPS2ModemStatus::BaseGPS2ModemStatus() :
    Group(22) {
}

BaseGPS2ModemStatus::BaseGPS2ModemStatus(const BaseGPS2ModemStatus& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mNumberOfRedialsPerDisconnect(other.mNumberOfDisconnects),
    mMaximumNumberOfRedialsPerDisconnect(
      other.mMaximumNumberOfRedialsPerDisconnect),
    mNumberOfDisconnects(other.mNumberOfDisconnects),
    mDataGapLength(other.mDataGapLength),
    mMaximumDataGapLength(other.mMaximumDataGapLength) {
  memcpy(mModemResponse, other.mModemResponse, sizeof(mModemResponse));
  memcpy(mConnectionStatus, other.mConnectionStatus,
      sizeof(mConnectionStatus));
}

BaseGPS2ModemStatus& BaseGPS2ModemStatus::operator =
    (const BaseGPS2ModemStatus& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    memcpy(mModemResponse, other.mModemResponse, sizeof(mModemResponse));
    memcpy(mConnectionStatus, other.mConnectionStatus,
      sizeof(mConnectionStatus));
    mNumberOfRedialsPerDisconnect = other.mNumberOfDisconnects;
    mMaximumNumberOfRedialsPerDisconnect =
      other.mMaximumNumberOfRedialsPerDisconnect;
    mNumberOfDisconnects = other.mNumberOfDisconnects;
    mDataGapLength = other.mDataGapLength;
    mMaximumDataGapLength = other.mMaximumDataGapLength;
  }
  return *this;
}

BaseGPS2ModemStatus::~BaseGPS2ModemStatus() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BaseGPS2ModemStatus::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("BaseGPS2ModemStatus::read(): wrong byte count");
  stream >> mTimeDistance;
  for (size_t i = 0; i < 16; i++)
    stream >> mModemResponse[i];
  for (size_t i = 0; i < 48; i++)
    stream >> mConnectionStatus[i];
  stream >> mNumberOfRedialsPerDisconnect;
  stream >> mMaximumNumberOfRedialsPerDisconnect;
  stream >> mNumberOfDisconnects;
  stream >> mDataGapLength;
  stream >> mMaximumDataGapLength;
  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("BaseGPS2ModemStatus::read(): wrong pad");
}

void BaseGPS2ModemStatus::read(std::istream& stream) {
}

void BaseGPS2ModemStatus::write(std::ostream& stream) const {
}

void BaseGPS2ModemStatus::read(std::ifstream& stream) {
}

void BaseGPS2ModemStatus::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " " ;
  stream << mTimeDistance;
  for (size_t i = 0; i < 16; i++) {
    stream << (uint16_t)mModemResponse[i];
    stream << " " ;
  }
  for (size_t i = 0; i < 48; i++) {
    stream << (uint16_t)mConnectionStatus[i];
    stream << " " ;
  }
  stream << mNumberOfRedialsPerDisconnect;
  stream << " " ;
  stream << mMaximumNumberOfRedialsPerDisconnect;
  stream << " " ;
  stream << mNumberOfDisconnects;
  stream << " " ;
  stream << mDataGapLength;
  stream << " " ;
  stream << mMaximumDataGapLength;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

BaseGPS2ModemStatus* BaseGPS2ModemStatus::clone() const {
  return new BaseGPS2ModemStatus(*this);
}
