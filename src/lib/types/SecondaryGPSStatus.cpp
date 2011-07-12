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

#include "com/POSLVGroupRead.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const SecondaryGPSStatus SecondaryGPSStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SecondaryGPSStatus::SecondaryGPSStatus() :
  Group(11),
  maChannelStatusData(0) {
}

SecondaryGPSStatus::SecondaryGPSStatus(const SecondaryGPSStatus& other) :
  Group(other),
  maChannelStatusData(other.maChannelStatusData) {
}

SecondaryGPSStatus& SecondaryGPSStatus::operator =
  (const SecondaryGPSStatus& other) {
  this->Group::operator=(other);
  maChannelStatusData = other.maChannelStatusData;
  return *this;
}

SecondaryGPSStatus::~SecondaryGPSStatus() {
  if (maChannelStatusData != 0)
    delete []maChannelStatusData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void SecondaryGPSStatus::read(POSLVGroupRead& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;

  stream >> mTimeDistance;
  stream >> mNavigationSolutionStatus;
  stream >> mNumberOfSVTracked;
  stream >> mChannelStatusByteCount;
  mChannelNumber = (byteCount - mByteCount) / 20;
  if (mChannelNumber > 0)
    maChannelStatusData = new ChannelStatusData[mChannelNumber];
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
  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException(" SecondaryGPSStatus::read(): wrong pad");
}

void SecondaryGPSStatus::read(std::istream& stream) {
}

void SecondaryGPSStatus::write(std::ostream& stream) const {
}

void SecondaryGPSStatus::read(std::ifstream& stream) {
}

void SecondaryGPSStatus::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << " ";
  stream << (int16_t)mNavigationSolutionStatus;
  stream << " ";
  stream << (uint16_t)mNumberOfSVTracked;
  stream << " ";
  stream << mChannelStatusByteCount;
  stream << " ";
  for (size_t i = 0; i < mChannelNumber; i++)
    stream << maChannelStatusData[i];
  stream << mHDOP;
  stream << " ";
  stream << mVDOP;
  stream << " ";
  stream << mDGPSCorrectionLatency;
  stream << " ";
  stream << mDGPSReferenceID;
  stream << " ";
  stream << mGPSUTCWeekNumber;
  stream << " ";
  stream << mGPSUTCTimeOffset;
  stream << " ";
  stream << mGPSNavigationMessageLatency;
  stream << " ";
  stream << mGeoidalSeparation;
  stream << " ";
  stream << mGPSReceiverType;
  stream << " ";
  stream << mGPSStatus;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

SecondaryGPSStatus* SecondaryGPSStatus::clone() const {
  return new SecondaryGPSStatus(*this);
}
