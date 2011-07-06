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

/** \file PrimaryGPSReceiverIntegratedDGPSStatus.h
    \brief This file defines the PrimaryGPSReceiverIntegratedDGPSStatus class,
           which represents the Primary GPS Receiver Integrated DGPS Status
           message from the Applanix
  */

#ifndef PRIMARYGPSRECEIVERINTEGRATEDDGPSSTATUS_H
#define PRIMARYGPSRECEIVERINTEGRATEDDGPSSTATUS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class PrimaryGPSReceiverIntegratedDGPSStatus represents the Primary GPS
    Receiver Integrated DGPS Status message from the Applanix.
    \brief Primary GPS Receiver Integrated DGPS Status message
  */
class PrimaryGPSReceiverIntegratedDGPSStatus :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  PrimaryGPSReceiverIntegratedDGPSStatus();
  /// Copy constructor
  PrimaryGPSReceiverIntegratedDGPSStatus(const
    PrimaryGPSReceiverIntegratedDGPSStatus& other);
  /// Assignement operator
  PrimaryGPSReceiverIntegratedDGPSStatus& operator =
    (const PrimaryGPSReceiverIntegratedDGPSStatus& other);
  /// Destructor
  virtual ~PrimaryGPSReceiverIntegratedDGPSStatus();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual PrimaryGPSReceiverIntegratedDGPSStatus* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 74;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Mobile differential mode
  uint8_t mMobileDifferentialMode;
  /// Frequency 0
  double mFrequency0;
  /// Acquisition mode 0
  uint8_t mAcquisitionMode0;
  /// Channel status 0
  uint8_t mChannelStatus0;
  /// RCTM used flag 0
  uint8_t mRCTMUsedFlag0;
  /// SNR 0
  uint8_t mSNR0;
  /// Data rate index 0
  uint8_t mDataRateIndex0;
  /// Lock indicator 0
  uint8_t mLockIndicator0;
  /// DGPS source auto switching 0
  uint8_t mDGPSSourceAutoSwitching0;
  /// Service provider 0
  uint8_t mServiceProvider0;
  /// Frequency 1
  double mFrequency1;
  /// Acquisition mode 1
  uint8_t mAcquisitionMode1;
  /// Channel status 1
  uint8_t mChannelStatus1;
  /// RCTM used flag 1
  uint8_t mRCTMUsedFlag1;
  /// SNR 1
  uint8_t mSNR1;
  /// Data rate index 1
  uint8_t mDataRateIndex1;
  /// Lock indicator 1
  uint8_t mLockIndicator1;
  /// DGPS source auto switching 1
  uint8_t mDGPSSourceAutoSwitching1;
  /// Service provider 1
  uint8_t mServiceProvider1;
  /// User ID code
  uint64_t mUserIDCode;
  /// User accesss
  uint8_t mUserAccess;
  /// Decoder state
  uint8_t mDecoderState;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const ;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /// Reads from the network
  virtual void read(Connection& stream) throw (IOException);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Prototype for this group
  static const PrimaryGPSReceiverIntegratedDGPSStatus mProto;
  /** @}
    */

};

#endif // PRIMARYGPSRECEIVERINTEGRATEDDGPSSTATUS_H
