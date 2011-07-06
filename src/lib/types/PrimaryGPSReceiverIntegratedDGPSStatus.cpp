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

void PrimaryGPSReceiverIntegratedDGPSStatus::read(std::istream& stream) {
}

void PrimaryGPSReceiverIntegratedDGPSStatus::write(std::ostream& stream) const {
}

void PrimaryGPSReceiverIntegratedDGPSStatus::read(std::ifstream& stream) {
}

void PrimaryGPSReceiverIntegratedDGPSStatus::write(std::ofstream& stream)
  const {
  stream << mTypeID;
//  stream << " ";
//  stream << mTimeDistance;
//  stream << hex << (uint16_t)mu8MobileDifferentialMode << dec;
//  stream << " ";
//  stream << mf64Frequency0;
//  stream << " ";
//  stream << hex << (uint16_t)mu8AcquisitionMode0 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8ChannelStatus0 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8RCTMUsedFlag0 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8SNR0 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8DataRateIndex0 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8LockIndicator0 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8DGPSSourceAutoSwitching0 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8ServiceProvider0 << dec;
//  stream << " ";
//  stream << mf64Frequency1;
//  stream << " ";
//  stream << hex << (uint16_t)mu8AcquisitionMode1 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8ChannelStatus1 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8RCTMUsedFlag1 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8SNR1 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8DataRateIndex1 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8LockIndicator1 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8DGPSSourceAutoSwitching1 << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8ServiceProvider1 << dec;
//  stream << " ";
//  stream << mu64UserIDCode;
//  stream << " ";
//  stream << hex << (uint16_t)mu8UserAccess << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8DecoderState << dec;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

PrimaryGPSReceiverIntegratedDGPSStatus* PrimaryGPSReceiverIntegratedDGPSStatus::
  clone() const {
  return new PrimaryGPSReceiverIntegratedDGPSStatus(*this);
}
