#include "types/PrimaryGPSReceiverIntegratedDGPSStatus.h"

#include "com/Connection.h"

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
  stream << hex << (uint16_t)mu8MobileDifferentialMode << dec;
  stream << " ";
  stream << mf64Frequency0;
  stream << " ";
  stream << hex << (uint16_t)mu8AcquisitionMode0 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8ChannelStatus0 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8RCTMUsedFlag0 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8SNR0 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8DataRateIndex0 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8LockIndicator0 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8DGPSSourceAutoSwitching0 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8ServiceProvider0 << dec;
  stream << " ";
  stream << mf64Frequency1;
  stream << " ";
  stream << hex << (uint16_t)mu8AcquisitionMode1 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8ChannelStatus1 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8RCTMUsedFlag1 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8SNR1 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8DataRateIndex1 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8LockIndicator1 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8DGPSSourceAutoSwitching1 << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8ServiceProvider1 << dec;
  stream << " ";
  stream << mu64UserIDCode;
  stream << " ";
  stream << hex << (uint16_t)mu8UserAccess << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8DecoderState << dec;
}

PrimaryGPSReceiverIntegratedDGPSStatus*
  PrimaryGPSReceiverIntegratedDGPSStatus::clone() const {
  return new PrimaryGPSReceiverIntegratedDGPSStatus(*this);
}
