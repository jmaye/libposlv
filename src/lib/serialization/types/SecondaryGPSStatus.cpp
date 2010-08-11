#include "SecondaryGPSStatus.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const SecondaryGPSStatus SecondaryGPSStatus::mProto;

SecondaryGPSStatus::SecondaryGPSStatus() : Group(11) {
}

SecondaryGPSStatus::SecondaryGPSStatus(const SecondaryGPSStatus &other)
  : Group(other) {
}

SecondaryGPSStatus::~SecondaryGPSStatus() {
}

void SecondaryGPSStatus::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;

  stream >> mTimeDistance;
  stream >> mi8NavigationSolutionStatus;
  stream >> mu8NumberOfSVTracked;
  stream >> mu16ChannelStatusByteCount;
  if (u16ByteCount - mu16ChannelStatusByteCount < mcu16ByteCount)
    throw IOException("SecondaryGPSStatus::read: Wrong byte count");
  uint32_t u32ChannelNumber = mu16ChannelStatusByteCount / 20;
  for (uint32_t i = 0; i < u32ChannelNumber; i ++)
    stream >> maChannelStatusData[i];
  stream >> mf32HDOP;
  stream >> mf32VDOP;
  stream >> mf32DGPSCorrectionLatency;
  stream >> mu16DGPSReferenceID;
  stream >> mu32GPSUTCWeekNumber;
  stream >> mf64GPSUTCTimeOffset;
  stream >> mf32GPSNavigationMessageLatency;
  stream >> mf32GeoidalSeparation;
  stream >> mu16GPSReceiverType;
  stream >> mu32GPSStatus;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("SecondaryGPSStatus::read: Wrong pad");
}

void SecondaryGPSStatus::write(ofstream &stream) const {
}

SecondaryGPSStatus* SecondaryGPSStatus::clone() const {
  return new SecondaryGPSStatus(*this);
}
