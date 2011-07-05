#include "types/TimeTaggedDMIData.h"

#include "com/Connection.h"

#include <fstream>

using namespace std;

const TimeTaggedDMIData TimeTaggedDMIData::mProto;

TimeTaggedDMIData::TimeTaggedDMIData() : Group(15) {
}

TimeTaggedDMIData::TimeTaggedDMIData(const TimeTaggedDMIData &other)
  : Group(other) {
}

TimeTaggedDMIData::~TimeTaggedDMIData() {
}

void TimeTaggedDMIData::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("TimeTaggedDMIData::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mf64SignedDistanceTraveled;
  stream >> mf64UnsignedDistanceTraveled;
  stream >> mu16DMIScaleFactor;
  stream >> mu8DataStatus;
  stream >> mu8DMIType;
  stream >> mu8DMIDataRate;

  uint8_t u8Pad;
  stream >> u8Pad;
  if (u8Pad != 0)
    throw IOException("TimeTaggedDMIData::read: Wrong pad");
}

void TimeTaggedDMIData::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mf64SignedDistanceTraveled;
  stream << " ";
  stream << mf64UnsignedDistanceTraveled;
  stream << " ";
  stream << mu16DMIScaleFactor;
  stream << " ";
  stream << hex << (uint16_t)mu8DataStatus << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8DMIType << dec;
  stream << " ";
  stream << hex << (uint16_t)mu8DMIDataRate << dec;
}

TimeTaggedDMIData* TimeTaggedDMIData::clone() const {
  return new TimeTaggedDMIData(*this);
}
