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

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const SecondaryGPSStatus SecondaryGPSStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SecondaryGPSStatus::SecondaryGPSStatus() :
    Group(11),
    mChannelStatusData(0),
    mChannelNumber(0) {
}

SecondaryGPSStatus::SecondaryGPSStatus(const SecondaryGPSStatus& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mNavigationSolutionStatus(other.mNavigationSolutionStatus),
    mNumberOfSVTracked(other.mNumberOfSVTracked),
    mChannelStatusByteCount(other.mChannelStatusByteCount),
    mHDOP(other.mHDOP),
    mVDOP(other.mVDOP),
    mDGPSCorrectionLatency(other.mDGPSCorrectionLatency),
    mDGPSReferenceID(other.mDGPSReferenceID),
    mGPSUTCWeekNumber(other.mGPSUTCWeekNumber),
    mGPSUTCTimeOffset(other.mGPSUTCTimeOffset),
    mGPSNavigationMessageLatency(other.mGPSNavigationMessageLatency),
    mGeoidalSeparation(other.mGeoidalSeparation),
    mGPSReceiverType(other.mGPSReceiverType),
    mGPSStatus(other.mGPSStatus),
    mChannelNumber(other.mChannelNumber) {
  if (mChannelNumber) {
    mChannelStatusData = new ChannelStatusData[mChannelNumber];
    memcpy(mChannelStatusData, other.mChannelStatusData,
      sizeof(mChannelStatusData));
  }
  else
    mChannelStatusData = 0;
}

SecondaryGPSStatus& SecondaryGPSStatus::operator =
    (const SecondaryGPSStatus& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    mNavigationSolutionStatus = other.mNavigationSolutionStatus;
    mNumberOfSVTracked = other.mNumberOfSVTracked;
    mChannelStatusByteCount = other.mChannelStatusByteCount;
    mHDOP = other.mHDOP;
    mVDOP = other.mVDOP;
    mDGPSCorrectionLatency = other.mDGPSCorrectionLatency;
    mDGPSReferenceID = other.mDGPSReferenceID;
    mGPSUTCWeekNumber = other.mGPSUTCWeekNumber;
    mGPSUTCTimeOffset = other.mGPSUTCTimeOffset;
    mGPSNavigationMessageLatency = other.mGPSNavigationMessageLatency;
    mGeoidalSeparation = other.mGeoidalSeparation;
    mGPSReceiverType = other.mGPSReceiverType;
    mGPSStatus = other.mGPSStatus;
    mChannelNumber = other.mChannelNumber;
    if (mChannelNumber) {
      mChannelStatusData = new ChannelStatusData[mChannelNumber];
      memcpy(mChannelStatusData, other.mChannelStatusData,
        sizeof(mChannelStatusData));
    }
    else
      mChannelStatusData = 0;
  }
  return *this;
}

SecondaryGPSStatus::~SecondaryGPSStatus() {
  if (mChannelStatusData != 0)
    delete []mChannelStatusData;
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void SecondaryGPSStatus::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  stream >> mTimeDistance;
  stream >> mNavigationSolutionStatus;
  stream >> mNumberOfSVTracked;
  stream >> mChannelStatusByteCount;
  mChannelNumber = mNumberOfSVTracked;
  if (mChannelStatusData)
    delete []mChannelStatusData;
  if (mChannelNumber > 0)
    mChannelStatusData = new ChannelStatusData[mChannelNumber];
  for (size_t i = 0; i < mChannelNumber; i++)
    stream >> mChannelStatusData[i];
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
}

void SecondaryGPSStatus::write(BinaryWriter& stream) const {
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
    stream << mChannelStatusData[i];
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
