#include "types/RawIMUData.h"

#include "com/Connection.h"
#include "utils/TypesFactory.h"

#include <fstream>

using namespace std;

const RawIMUData RawIMUData::mProto;

RawIMUData::RawIMUData() : Group(10002) {
}

RawIMUData::RawIMUData(const RawIMUData &other)
  : Group(other) {
}

RawIMUData::~RawIMUData() {
  if (mau8IMURawData)
    delete mau8IMURawData;
}

void RawIMUData::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  stream >> mTimeDistance;
  for (uint32_t i = 0; i < 6; i++)
    stream >> mau8IMUHeader[i];
  stream >> mu16VariableMsgByteCount;
  mau8IMURawData = new uint8_t[mu16VariableMsgByteCount];
  for (uint16_t i = 0; i < mu16VariableMsgByteCount; i++)
    stream >> mau8IMURawData[i];
  stream >> mu16DataChecksum;
  uint32_t u32PadSize = u16ByteCount - 26 - 6 - 2 -
    mu16VariableMsgByteCount - 2 - 2 - 2;

  uint8_t u8Pad;
  for (uint32_t i = 0; i < u32PadSize; i++)
    stream >> u8Pad;
}

void RawIMUData::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  for (uint32_t i = 0; i < 6; i++)
    stream << mau8IMUHeader[i];
  stream << " ";
  stream << mu16VariableMsgByteCount;
  stream << " ";
  for (uint16_t i = 0; i < mu16VariableMsgByteCount; i++) {
    stream << hex << (uint16_t)mau8IMURawData[i] << dec;
    stream << " ";
  }
}

RawIMUData* RawIMUData::clone() const {
  return new RawIMUData(*this);
}
