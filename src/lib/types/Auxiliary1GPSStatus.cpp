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

#include "types/Auxiliary1GPSStatus.h"

#include "com/Connection.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const Auxiliary1GPSStatus Auxiliary1GPSStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Auxiliary1GPSStatus::Auxiliary1GPSStatus() :
  Group(13) {
}

Auxiliary1GPSStatus::Auxiliary1GPSStatus(const Auxiliary1GPSStatus& other) :
  Group(other) {
}

Auxiliary1GPSStatus& Auxiliary1GPSStatus::operator =
  (const Auxiliary1GPSStatus& other) {
  this->Group::operator=(other);
  return *this;
}

Auxiliary1GPSStatus::~Auxiliary1GPSStatus() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void Auxiliary1GPSStatus::read(Connection& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  stream >> mTimeDistance;
  stream >> mNavigationSolutionStatus;
  stream >> mNumberOfSVTracked;
  stream >> mChannelStatusByteCount;
  if (byteCount != mByteCount)
    throw IOException("Auxiliary1GPSStatus::read(): wrong byte count");
  mChannelNumber = mChannelStatusByteCount / 20;
  for (size_t i = 0; i < mChannelNumber; i ++)
    stream >> maChannelStatusData[i];
  stream >> mHDOP;
  stream >> mVDOP;
  stream >> mDGPSCorrectionLatency;
  stream >> mDGPSReferenceID;
  stream >> mGPSUTCWeekNumber;
  stream >> mGPSUTCTimeOffset;
  stream >> mGPSNavigationMessageLatency;
  stream >> mGeoidalSeparation;
  stream >> mNMEAMessageReceived;
  stream >> mAux12InUse;

  uint8_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("Auxiliary1GPSStatus::read(): wrong pad");
}

void Auxiliary1GPSStatus::read(std::istream& stream) {
}

void Auxiliary1GPSStatus::write(std::ostream& stream) const {
}

void Auxiliary1GPSStatus::read(std::ifstream& stream) {
}

void Auxiliary1GPSStatus::write(std::ofstream& stream) const {
//  stream << mu16TypeID;
//  stream << " ";
//  stream << mTimeDistance;
//  stream << hex << (uint16_t)mi8NavigationSolutionStatus << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8NumberOfSVTracked << dec;
//  stream << " ";
//  stream << mu16ChannelStatusByteCount;
//  stream << " ";
//  for (uint32_t i = 0; i < mu32ChannelNumber; i ++)
//    stream << maChannelStatusData[i];
//  stream << mf32HDOP;
//  stream << " ";
//  stream << mf32VDOP;
//  stream << " ";
//  stream << mf32DGPSCorrectionLatency;
//  stream << " ";
//  stream << mu16DGPSReferenceID;
//  stream << " ";
//  stream << mu32GPSUTCWeekNumber;
//  stream << " ";
//  stream << mf64GPSUTCTimeOffset;
//  stream << " ";
//  stream << mf32GPSNavigationMessageLatency;
//  stream << " ";
//  stream << mf32GeoidalSeparation;
//  stream << " ";
//  stream << mu16NMEAMessageReceived;
//  stream << " ";
//  stream << hex << (uint16_t)mu8Aux12InUse << dec;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

Auxiliary1GPSStatus* Auxiliary1GPSStatus::clone() const {
  return new Auxiliary1GPSStatus(*this);
}