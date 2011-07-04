#include "types/PrimaryGPSStatus.h"

#include "com/Connection.h"
#include "utils/TypesFactory.h"

#include <fstream>

using namespace std;

const PrimaryGPSStatus PrimaryGPSStatus::mProto;

PrimaryGPSStatus::PrimaryGPSStatus() : Group(3) {
}

PrimaryGPSStatus::PrimaryGPSStatus(const PrimaryGPSStatus &other)
  : Group(other) {
}

PrimaryGPSStatus::~PrimaryGPSStatus() {
}

void PrimaryGPSStatus::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  stream >> mTimeDistance;
  stream >> mi8NavigationSolutionStatus;
  stream >> mu8NumberOfSVTracked;
  stream >> mu16ChannelStatusByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("PrimaryGPSStatus::read: Wrong byte count");
  for (uint32_t i = 0; i < mu8NumberOfSVTracked; i ++)
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

  for (uint32_t i = 0; i < u16ByteCount - 74; i ++) {
    uint8_t u8Byte;
    stream >> u8Byte;
  }
}

void PrimaryGPSStatus::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << hex << (uint16_t)mi8NavigationSolutionStatus << dec;
  stream << " ";
  stream << (uint16_t)mu8NumberOfSVTracked;
  stream << " ";
  stream << mu16ChannelStatusByteCount;
  stream << " ";
  for (uint32_t i = 0; i < mu8NumberOfSVTracked; i ++)
    stream << maChannelStatusData[i];
  stream << mf32HDOP;
  stream << " ";
  stream << mf32VDOP;
  stream << " ";
  stream << mf32DGPSCorrectionLatency;
  stream << " ";
  stream << mu16DGPSReferenceID;
  stream << " ";
  stream << mu32GPSUTCWeekNumber;
  stream << " ";
  stream << mf64GPSUTCTimeOffset;
  stream << " ";
  stream << mf32GPSNavigationMessageLatency;
  stream << " ";
  stream << mf32GeoidalSeparation;
  stream << " ";
  stream << mu16GPSReceiverType;
  stream << " ";
  stream << mu32GPSStatus;
}

PrimaryGPSStatus* PrimaryGPSStatus::clone() const {
  return new PrimaryGPSStatus(*this);
}
