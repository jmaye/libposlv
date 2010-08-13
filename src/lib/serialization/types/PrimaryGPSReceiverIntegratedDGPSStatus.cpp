#include "PrimaryGPSReceiverIntegratedDGPSStatus.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const PrimaryGPSReceiverIntegratedDGPSStatus
  PrimaryGPSReceiverIntegratedDGPSStatus::mProto;

PrimaryGPSReceiverIntegratedDGPSStatus::PrimaryGPSReceiverIntegratedDGPSStatus()
  : Group(25) {
}

PrimaryGPSReceiverIntegratedDGPSStatus::
  PrimaryGPSReceiverIntegratedDGPSStatus(
  const PrimaryGPSReceiverIntegratedDGPSStatus &other)
  : Group(other) {
}

PrimaryGPSReceiverIntegratedDGPSStatus::~PrimaryGPSReceiverIntegratedDGPSStatus() {
}

void PrimaryGPSReceiverIntegratedDGPSStatus::read(Connection &stream)
  throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("PrimaryGPSReceiverIntegratedDGPSStatus::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mu8MobileDifferentialMode;
  stream >> mf64Frequency0;
  stream >> mu8AcquisitionMode0;
  stream >> mu8ChannelStatus0;
  stream >> mu8RCTMUsedFlag0;
  stream >> mu8SNR0;
  stream >> mu8DataRateIndex0;
  stream >> mu8LockIndicator0;
  stream >> mu8DGPSSourceAutoSwitching0;
  stream >> mu8ServiceProvider0;
  stream >> mf64Frequency1;
  stream >> mu8AcquisitionMode1;
  stream >> mu8ChannelStatus1;
  stream >> mu8RCTMUsedFlag1;
  stream >> mu8SNR1;
  stream >> mu8DataRateIndex1;
  stream >> mu8LockIndicator1;
  stream >> mu8DGPSSourceAutoSwitching1;
  stream >> mu8ServiceProvider1;
  stream >> mu64UserIDCode;
  stream >> mu8UserAccess;
  stream >> mu8DecoderState;

  uint8_t u8Pad;
  stream >> u8Pad;
  if (u8Pad != 0)
    throw IOException("PrimaryGPSReceiverIntegratedDGPSStatus::read: Wrong pad");
}

void PrimaryGPSReceiverIntegratedDGPSStatus::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mu8MobileDifferentialMode;
  stream << " ";
  stream << mf64Frequency0;
  stream << " ";
  stream << mu8AcquisitionMode0;
  stream << " ";
  stream << mu8ChannelStatus0;
  stream << " ";
  stream << mu8RCTMUsedFlag0;
  stream << " ";
  stream << mu8SNR0;
  stream << " ";
  stream << mu8DataRateIndex0;
  stream << " ";
  stream << mu8LockIndicator0;
  stream << " ";
  stream << mu8DGPSSourceAutoSwitching0;
  stream << " ";
  stream << mu8ServiceProvider0;
  stream << " ";
  stream << mf64Frequency1;
  stream << " ";
  stream << mu8AcquisitionMode1;
  stream << " ";
  stream << mu8ChannelStatus1;
  stream << " ";
  stream << mu8RCTMUsedFlag1;
  stream << " ";
  stream << mu8SNR1;
  stream << " ";
  stream << " ";
  stream << mu8DataRateIndex1;
  stream << " ";
  stream << mu8LockIndicator1;
  stream << " ";
  stream << mu8DGPSSourceAutoSwitching1;
  stream << " ";
  stream << mu8ServiceProvider1;
  stream << " ";
  stream << mu64UserIDCode;
  stream << " ";
  stream << mu8UserAccess;
  stream << " ";
  stream << mu8DecoderState;
}

PrimaryGPSReceiverIntegratedDGPSStatus*
  PrimaryGPSReceiverIntegratedDGPSStatus::clone() const {
  return new PrimaryGPSReceiverIntegratedDGPSStatus(*this);
}
