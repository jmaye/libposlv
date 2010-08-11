#ifndef PRIMARYGPSRECEIVERINTEGRATEDDGPSSTATUS_H
#define PRIMARYGPSRECEIVERINTEGRATEDDGPSSTATUS_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class PrimaryGPSReceiverIntegratedDGPSStatus : public Group {
  PrimaryGPSReceiverIntegratedDGPSStatus();
  PrimaryGPSReceiverIntegratedDGPSStatus(
    const PrimaryGPSReceiverIntegratedDGPSStatus &other);
  PrimaryGPSReceiverIntegratedDGPSStatus& operator =
    (const PrimaryGPSReceiverIntegratedDGPSStatus &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 74;

  TimeDistance mTimeDistance;
  uint8_t mu8MobileDifferentialMode;
  double mf64Frequency0;
  uint8_t AcquisitionMode0;
  uint8_t mu8ChannelStatus0;
  uint8_t mu8RCTMUsedFlag0;
  uint8_t mu8SNR0;
  uint8_t mu8DataRateIndex0;
  uint8_t mu8LockIndicator0;
  uint8_t mu8DGPSSourceAutoSwitching0;
  uint8_t mu8ServiceProvider0;
  double mf64Frequency1;
  uint8_t AcquisitionMode1;
  uint8_t mu8ChannelStatus1;
  uint8_t mu8RCTMUsedFlag1;
  uint8_t mu8SNR1;
  uint8_t mu8DataRateIndex1;
  uint8_t mu8LockIndicator1;
  uint8_t mu8DGPSSourceAutoSwitching1;
  uint8_t mu8ServiceProvider1;
  uint64_t mu64UserIDCode;
  uint8_t mu8UserAccess;
  uint8_t mu8DecoderState;

public:
  ~PrimaryGPSReceiverIntegratedDGPSStatus();

  virtual PrimaryGPSReceiverIntegratedDGPSStatus* clone() const;

  static const PrimaryGPSReceiverIntegratedDGPSStatus mProto;

protected:
};

#endif // PRIMARYGPSRECEIVERINTEGRATEDDGPSSTATUS_H
