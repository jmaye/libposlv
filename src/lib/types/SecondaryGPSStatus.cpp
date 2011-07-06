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

#include "types/SecondaryGPSStatus.h"

#include "com/Connection.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const SecondaryGPSStatus SecondaryGPSStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SecondaryGPSStatus::SecondaryGPSStatus() :
  Group(11) {
}

SecondaryGPSStatus::SecondaryGPSStatus(const SecondaryGPSStatus& other) :
  Group(other) {
}

SecondaryGPSStatus& SecondaryGPSStatus::operator =
  (const SecondaryGPSStatus& other) {
  this->Group::operator=(other);
  return *this;
}

SecondaryGPSStatus::~SecondaryGPSStatus() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void SecondaryGPSStatus::read(Connection& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;

  stream >> mTimeDistance;
  stream >> mNavigationSolutionStatus;
  stream >> mNumberOfSVTracked;
  stream >> mChannelStatusByteCount;
  mChannelNumber = (byteCount - mByteCount) / mChannelStatusByteCount;
  for (size_t i = 0; i < mChannelNumber; i++)
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

void SecondaryGPSStatus::read(std::istream& stream) {
}

void SecondaryGPSStatus::write(std::ostream& stream) const {
}

void SecondaryGPSStatus::read(std::ifstream& stream) {
}

void SecondaryGPSStatus::write(std::ofstream& stream) const {
  stream << mTypeID;
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

SecondaryGPSStatus* SecondaryGPSStatus::clone() const {
  return new SecondaryGPSStatus(*this);
}
