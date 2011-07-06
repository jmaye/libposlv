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

#include "types/PrimaryGPSStatus.h"

#include "com/Connection.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const PrimaryGPSStatus PrimaryGPSStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PrimaryGPSStatus::PrimaryGPSStatus() :
  Group(3) {
}

PrimaryGPSStatus::PrimaryGPSStatus(const PrimaryGPSStatus& other) :
  Group(other) {
}

PrimaryGPSStatus& PrimaryGPSStatus::operator =
  (const PrimaryGPSStatus& other) {
  this->Group::operator=(other);
  return *this;
}

PrimaryGPSStatus::~PrimaryGPSStatus() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void PrimaryGPSStatus::read(Connection& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;

  stream >> mTimeDistance;
  stream >> mNavigationSolutionStatus;
  stream >> mNumberOfSVTracked;
  stream >> mChannelStatusByteCount;
  if (byteCount != mByteCount)
    throw IOException("PrimaryGPSStatus::read(): wrong byte count");
  for (size_t i = 0; i < mNumberOfSVTracked; i ++)
    stream >> maChannelStatusData[i];
  stream >> mHDOP;
  stream >> mVDOP;
  stream >> mDGPSCorrectionLatency;
  stream >> mDGPSReferenceID;
  stream >> mGPSUTCWeekNumber;
  stream >> mGPSUTCTimeOffset;
  stream >> mGPSNavigationMessageLatency;
  stream >> mGeoidalSeparation;
  stream >> mGPSReceiverType;
  stream >> mGPSStatus;
  byteCount -= 74;
  for (size_t i = 0; i < byteCount; i++) {
    uint8_t byte;
    stream >> byte;
  }
}

void PrimaryGPSStatus::read(std::istream& stream) {
}

void PrimaryGPSStatus::write(std::ostream& stream) const {
}

void PrimaryGPSStatus::read(std::ifstream& stream) {
}

void PrimaryGPSStatus::write(std::ofstream& stream) const {
//  stream << mu16TypeID;
//  stream << " ";
//  stream << mTimeDistance;
//  stream << " ";
//  stream << hex << (uint16_t)mi8NavigationSolutionStatus << dec;
//  stream << " ";
//  stream << (uint16_t)mu8NumberOfSVTracked;
//  stream << " ";
//  stream << mu16ChannelStatusByteCount;
//  stream << " ";
//  for (uint32_t i = 0; i < mu8NumberOfSVTracked; i ++)
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
//  stream << mu16GPSReceiverType;
//  stream << " ";
//  stream << mu32GPSStatus;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

PrimaryGPSStatus* PrimaryGPSStatus::clone() const {
  return new PrimaryGPSStatus(*this);
}
