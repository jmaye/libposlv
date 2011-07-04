#include "types/Auxiliary1GPSDisplayData.h"

#include "com/Connection.h"
#include "utils/TypesFactory.h"

#include <fstream>

using namespace std;

const Auxiliary1GPSDisplayData Auxiliary1GPSDisplayData::mProto;

Auxiliary1GPSDisplayData::Auxiliary1GPSDisplayData() : Group(10007) {
}

Auxiliary1GPSDisplayData::
  Auxiliary1GPSDisplayData(const Auxiliary1GPSDisplayData &other)
  : Group(other) {
}

Auxiliary1GPSDisplayData::~Auxiliary1GPSDisplayData() {
  if (mau8GPSRawData)
    delete mau8GPSRawData;
}

void Auxiliary1GPSDisplayData::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;

  stream >> mTimeDistance;
  for (uint32_t i = 0; i < 6; i++)
    stream >> mau8Reserved[i];
  stream >> mu16VariableMsgByteCount;
  mau8GPSRawData = new uint8_t[mu16VariableMsgByteCount];
  for (uint16_t i = 0; i < mu16VariableMsgByteCount; i++)
    stream >> mau8GPSRawData[i];

  uint32_t u32PadSize = u16ByteCount - 26 - 4 - 6 - 2 -
    mu16VariableMsgByteCount;

  uint8_t u8Pad;
  for (uint32_t i = 0; i < u32PadSize; i++)
    stream >> u8Pad;
}

void Auxiliary1GPSDisplayData::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  for (uint32_t i = 0; i < 6; i++) {
    stream << hex << (uint16_t)mau8Reserved[i] << dec;
    stream << " ";
  }
  stream << mu16VariableMsgByteCount;
  stream << " ";
  for (uint16_t i = 0; i < mu16VariableMsgByteCount; i++) {
    stream << hex << (uint16_t)mau8GPSRawData[i] << dec;
    stream << " ";
  }
}

Auxiliary1GPSDisplayData* Auxiliary1GPSDisplayData::clone() const {
  return new Auxiliary1GPSDisplayData(*this);
}
