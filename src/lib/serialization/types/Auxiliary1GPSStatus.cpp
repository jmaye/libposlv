#include "Auxiliary1GPSStatus.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const Auxiliary1GPSStatus Auxiliary1GPSStatus::mProto;

Auxiliary1GPSStatus::Auxiliary1GPSStatus() : Group(12) {
}

Auxiliary1GPSStatus::Auxiliary1GPSStatus(const Auxiliary1GPSStatus &other)
  : Group(other) {
}

Auxiliary1GPSStatus::~Auxiliary1GPSStatus() {
}

void Auxiliary1GPSStatus::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;

  stream >> mTimeDistance;
  stream >> mi8NavigationSolutionStatus;
  stream >> mu8NumberOfSVTracked;
  stream >> mu16ChannelStatusByteCount;
  if (u16ByteCount - mu16ChannelStatusByteCount < mcu16ByteCount)
    throw IOException("Auxiliary1GPSStatus::read: Wrong byte count");
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
  stream >> mu16NMEAMessageReceived;
  stream >> mu8Aux12InUse;

  uint8_t u8Pad;
  stream >> u8Pad;
  if (u8Pad != 0)
    throw IOException("Auxiliary1GPSStatus::read: Wrong pad");
}

void Auxiliary1GPSStatus::write(ofstream &stream) const {
}

Auxiliary1GPSStatus* Auxiliary1GPSStatus::clone() const {
  return new Auxiliary1GPSStatus(*this);
}
