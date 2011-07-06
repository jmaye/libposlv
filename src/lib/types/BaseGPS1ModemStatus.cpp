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

#include "types/BaseGPS1ModemStatus.h"

#include "com/Connection.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const BaseGPS1ModemStatus BaseGPS1ModemStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BaseGPS1ModemStatus::BaseGPS1ModemStatus() :
  Group(21) {
}

BaseGPS1ModemStatus::BaseGPS1ModemStatus(const BaseGPS1ModemStatus& other) :
  Group(other) {
}

BaseGPS1ModemStatus& BaseGPS1ModemStatus::operator =
  (const BaseGPS1ModemStatus& other) {
  this->Group::operator=(other);
  return *this;
}

BaseGPS1ModemStatus::~BaseGPS1ModemStatus() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void BaseGPS1ModemStatus::read(Connection& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("BaseGPS1ModemStatus::read(): wrong byte count");

  stream >> mTimeDistance;
  for (size_t i = 0; i < 16; i++)
    stream >> mau8ModemResponse[i];
  for (size_t i = 0; i < 48; i++)
    stream >> mau8ConnectionStatus[i];
  stream >> mNumberOfRedialsPerDisconnect;
  stream >> mMaximumNumberOfRedialsPerDisconnect;
  stream >> mNumberOfDisconnects;
  stream >> mDataGapLength;
  stream >> mMaximumDataGapLength;

  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("BaseGPS1ModemStatus::read(): wrong pad");
}

void BaseGPS1ModemStatus::read(std::istream& stream) {
}

void BaseGPS1ModemStatus::write(std::ostream& stream) const {
}

void BaseGPS1ModemStatus::read(std::ifstream& stream) {
}

void BaseGPS1ModemStatus::write(std::ofstream& stream) const {
//  stream << mu16TypeID;
//  stream << " " ;
//  stream << mTimeDistance;
//  for (uint32_t i = 0; i < 16; i++) {
//    stream << hex << (uint16_t)mau8ModemResponse[i] << dec;
//    stream << " " ;
//  }
//  for (uint32_t i = 0; i < 48; i++) {
//    stream << hex << (uint16_t)mau8ConnectionStatus[i] << dec;
//    stream << " " ;
//  }
//  stream << mu32NumberOfRedialsPerDisconnect;
//  stream << " " ;
//  stream << mu32MaximumNumberOfRedialsPerDisconnect;
//  stream << " " ;
//  stream << mu32NumberOfDisconnects;
//  stream << " " ;
//  stream << mu32DataGapLength;
//  stream << " " ;
//  stream << mu32MaximumDataGapLength;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

BaseGPS1ModemStatus* BaseGPS1ModemStatus::clone() const {
  return new BaseGPS1ModemStatus(*this);
}
