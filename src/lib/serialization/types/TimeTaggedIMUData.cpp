#include "TimeTaggedIMUData.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const TimeTaggedIMUData TimeTaggedIMUData::mProto;

TimeTaggedIMUData::TimeTaggedIMUData() : Group(4) {
}

TimeTaggedIMUData::TimeTaggedIMUData(const TimeTaggedIMUData &other)
  : Group(other) {
}

TimeTaggedIMUData::~TimeTaggedIMUData() {
}

void TimeTaggedIMUData::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("TimeTaggedIMUData::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mi32XIncrementalVelocity;
  stream >> mi32YIncrementalVelocity;
  stream >> mi32ZIncrementalVelocity;
  stream >> mi32XIncrementalAngle;
  stream >> mi32YIncrementalAngle;
  stream >> mi32ZIncrementalAngle;
  stream >> mu8DataStatus;
  stream >> mu8IMUType;
  stream >> mu8POSIMUDataRate;
  stream >> mu16IMUStatus;

  uint8_t u8Pad;
  stream >> u8Pad;
  if (u8Pad != 0)
    throw IOException("TimeTaggedIMUData::read: Wrong pad");
}

void TimeTaggedIMUData::write(ofstream &stream) const {
}

TimeTaggedIMUData* TimeTaggedIMUData::clone() const {
  return new TimeTaggedIMUData(*this);
}
