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

#include "types/PrimaryGPSReceiverIntegratedDGPSStatus.h"

#include "com/Connection.h"
#include "com/POSLVGroupRead.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const PrimaryGPSReceiverIntegratedDGPSStatus
  PrimaryGPSReceiverIntegratedDGPSStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PrimaryGPSReceiverIntegratedDGPSStatus::PrimaryGPSReceiverIntegratedDGPSStatus()
  : Group(25) {
}

PrimaryGPSReceiverIntegratedDGPSStatus::PrimaryGPSReceiverIntegratedDGPSStatus(
  const PrimaryGPSReceiverIntegratedDGPSStatus& other) :
  Group(other) {
}

PrimaryGPSReceiverIntegratedDGPSStatus&
  PrimaryGPSReceiverIntegratedDGPSStatus::operator =
  (const PrimaryGPSReceiverIntegratedDGPSStatus& other) {
  this->Group::operator=(other);
  return *this;
}

PrimaryGPSReceiverIntegratedDGPSStatus::
  ~PrimaryGPSReceiverIntegratedDGPSStatus() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void PrimaryGPSReceiverIntegratedDGPSStatus::read(Connection& stream)
  throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("PrimaryGPSReceiverIntegratedDGPSStatus::read(): wrong byte count");

  stream >> mTimeDistance;
  stream >> mMobileDifferentialMode;
  stream >> mFrequency0;
  stream >> mAcquisitionMode0;
  stream >> mChannelStatus0;
  stream >> mRCTMUsedFlag0;
  stream >> mSNR0;
  stream >> mDataRateIndex0;
  stream >> mLockIndicator0;
  stream >> mDGPSSourceAutoSwitching0;
  stream >> mServiceProvider0;
  stream >> mFrequency1;
  stream >> mAcquisitionMode1;
  stream >> mChannelStatus1;
  stream >> mRCTMUsedFlag1;
  stream >> mSNR1;
  stream >> mDataRateIndex1;
  stream >> mLockIndicator1;
  stream >> mDGPSSourceAutoSwitching1;
  stream >> mServiceProvider1;
  stream >> mUserIDCode;
  stream >> mUserAccess;
  stream >> mDecoderState;

  uint8_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("PrimaryGPSReceiverIntegratedDGPSStatus::read(): wrong pad");
}

void PrimaryGPSReceiverIntegratedDGPSStatus::read(POSLVGroupRead& stream)
  throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("PrimaryGPSReceiverIntegratedDGPSStatus::read(): wrong byte count");

  stream >> mTimeDistance;
  stream >> mMobileDifferentialMode;
  stream >> mFrequency0;
  stream >> mAcquisitionMode0;
  stream >> mChannelStatus0;
  stream >> mRCTMUsedFlag0;
  stream >> mSNR0;
  stream >> mDataRateIndex0;
  stream >> mLockIndicator0;
  stream >> mDGPSSourceAutoSwitching0;
  stream >> mServiceProvider0;
  stream >> mFrequency1;
  stream >> mAcquisitionMode1;
  stream >> mChannelStatus1;
  stream >> mRCTMUsedFlag1;
  stream >> mSNR1;
  stream >> mDataRateIndex1;
  stream >> mLockIndicator1;
  stream >> mDGPSSourceAutoSwitching1;
  stream >> mServiceProvider1;
  stream >> mUserIDCode;
  stream >> mUserAccess;
  stream >> mDecoderState;

  uint8_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("PrimaryGPSReceiverIntegratedDGPSStatus::read(): wrong pad");
}

void PrimaryGPSReceiverIntegratedDGPSStatus::read(std::istream& stream) {
}

void PrimaryGPSReceiverIntegratedDGPSStatus::write(std::ostream& stream) const {
}

void PrimaryGPSReceiverIntegratedDGPSStatus::read(std::ifstream& stream) {
}

void PrimaryGPSReceiverIntegratedDGPSStatus::write(std::ofstream& stream)
  const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << (uint16_t)mMobileDifferentialMode;
  stream << " ";
  stream << mFrequency0;
  stream << " ";
  stream << (uint16_t)mAcquisitionMode0;
  stream << " ";
  stream << (uint16_t)mChannelStatus0;
  stream << " ";
  stream << (uint16_t)mRCTMUsedFlag0;
  stream << " ";
  stream << (uint16_t)mSNR0;
  stream << " ";
  stream << (uint16_t)mDataRateIndex0;
  stream << " ";
  stream << (uint16_t)mLockIndicator0;
  stream << " ";
  stream << (uint16_t)mDGPSSourceAutoSwitching0;
  stream << " ";
  stream << (uint16_t)mServiceProvider0;
  stream << " ";
  stream << mFrequency1;
  stream << " ";
  stream << (uint16_t)mAcquisitionMode1;
  stream << " ";
  stream << (uint16_t)mChannelStatus1;
  stream << " ";
  stream << (uint16_t)mRCTMUsedFlag1;
  stream << " ";
  stream << (uint16_t)mSNR1;
  stream << " ";
  stream << (uint16_t)mDataRateIndex1;
  stream << " ";
  stream << (uint16_t)mLockIndicator1;
  stream << " ";
  stream << (uint16_t)mDGPSSourceAutoSwitching1;
  stream << " ";
  stream << (uint16_t)mServiceProvider1;
  stream << " ";
  stream << mUserIDCode;
  stream << " ";
  stream << (uint16_t)mUserAccess;
  stream << " ";
  stream << (uint16_t)mDecoderState;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

PrimaryGPSReceiverIntegratedDGPSStatus* PrimaryGPSReceiverIntegratedDGPSStatus::
  clone() const {
  return new PrimaryGPSReceiverIntegratedDGPSStatus(*this);
}
