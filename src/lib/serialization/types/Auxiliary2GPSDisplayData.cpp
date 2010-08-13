#include "Auxiliary2GPSDisplayData.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const Auxiliary2GPSDisplayData Auxiliary2GPSDisplayData::mProto;

Auxiliary2GPSDisplayData::Auxiliary2GPSDisplayData() : Group(10008) {
}

Auxiliary2GPSDisplayData::
  Auxiliary2GPSDisplayData(const Auxiliary2GPSDisplayData &other)
  : Group(other) {
}

Auxiliary2GPSDisplayData::~Auxiliary2GPSDisplayData() {
  if (mau8GPSRawData)
    delete mau8GPSRawData;
}

void Auxiliary2GPSDisplayData::read(Connection &stream) throw(IOException) {
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

void Auxiliary2GPSDisplayData::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  for (uint32_t i = 0; i < 6; i++) {
    stream << mau8Reserved[i];
    stream << " ";
  }
  stream << mu16VariableMsgByteCount;
  stream << " ";
  for (uint16_t i = 0; i < mu16VariableMsgByteCount; i++) {
    stream << mau8GPSRawData[i];
    stream << " ";
  }
}

Auxiliary2GPSDisplayData* Auxiliary2GPSDisplayData::clone() const {
  return new Auxiliary2GPSDisplayData(*this);
}
