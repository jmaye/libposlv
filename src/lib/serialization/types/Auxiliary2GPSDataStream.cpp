#include "types/Auxiliary2GPSDataStream.h"

#include "com/Connection.h"
#include "serialization/TypesFactory.h"

#include <fstream>

using namespace std;

const Auxiliary2GPSDataStream Auxiliary2GPSDataStream::mProto;

Auxiliary2GPSDataStream::Auxiliary2GPSDataStream() : Group(10008) {
}

Auxiliary2GPSDataStream::
  Auxiliary2GPSDataStream(const Auxiliary2GPSDataStream &other)
  : Group(other) {
}

Auxiliary2GPSDataStream::~Auxiliary2GPSDataStream() {
  if (mau8GPSReceiverRawData)
    delete mau8GPSReceiverRawData;
}

void Auxiliary2GPSDataStream::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  stream >> mTimeDistance;
  for (uint32_t i = 0; i < 6; i++)
    stream >> mau8Reserved[i];
  stream >> mu16VariableMsgByteCount;
  mau8GPSReceiverRawData = new uint8_t[mu16VariableMsgByteCount];
  for (uint16_t i = 0; i < mu16VariableMsgByteCount; i++)
    stream >> mau8GPSReceiverRawData[i];
  uint32_t u32PadSize = u16ByteCount - 26 - 6 - 2 -
    mu16VariableMsgByteCount - 2 - 2;

  uint8_t u8Pad;
  for (uint32_t i = 0; i < u32PadSize; i++)
    stream >> u8Pad;
}

void Auxiliary2GPSDataStream::write(ofstream &stream) const {
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
    stream << hex << (uint16_t)mau8GPSReceiverRawData[i] << dec;
    stream << " ";
  }
}

Auxiliary2GPSDataStream* Auxiliary2GPSDataStream::clone() const {
  return new Auxiliary2GPSDataStream(*this);
}
