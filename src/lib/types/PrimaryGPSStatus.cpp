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

#include "com/POSLVGroupRead.h"

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

void PrimaryGPSStatus::read(POSLVGroupRead& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;

  stream >> mTimeDistance;
  stream >> mNavigationSolutionStatus;
  stream >> mNumberOfSVTracked;
  stream >> mChannelStatusByteCount;
  mChannelNumber = mChannelStatusByteCount / 20;
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
    throw IOException(" PrimaryGPSStatus::read(): wrong pad");
}

void PrimaryGPSStatus::read(std::istream& stream) {
}

void PrimaryGPSStatus::write(std::ostream& stream) const {
}

void PrimaryGPSStatus::read(std::ifstream& stream) {
}

void PrimaryGPSStatus::write(std::ofstream& stream) const {
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

PrimaryGPSStatus* PrimaryGPSStatus::clone() const {
  return new PrimaryGPSStatus(*this);
}
