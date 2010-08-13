#include "PrimaryGPSDataStream.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const PrimaryGPSDataStream PrimaryGPSDataStream::mProto;

PrimaryGPSDataStream::PrimaryGPSDataStream() : Group(10001) {
}

PrimaryGPSDataStream::PrimaryGPSDataStream(const PrimaryGPSDataStream &other)
  : Group(other) {
}

PrimaryGPSDataStream::~PrimaryGPSDataStream() {
  if (mau8GPSReceiverRawData)
    delete mau8GPSReceiverRawData;
}

void PrimaryGPSDataStream::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  stream >> mTimeDistance;
  stream >> mu16GPSReceiverType;
  stream >> mu32Reserved;
  stream >> mu16VariableMsgByteCount;
  mau8GPSReceiverRawData = new uint8_t[mu16VariableMsgByteCount];
  for (uint16_t i = 0; i < mu16VariableMsgByteCount; i++)
    stream >> mau8GPSReceiverRawData[i];
  uint32_t u32PadSize = u16ByteCount - 26 - 2 - 4 - 2 -
    mu16VariableMsgByteCount - 2 - 2;

  uint8_t u8Pad;
  for (uint32_t i = 0; i < u32PadSize; i++)
    stream >> u8Pad;
}

void PrimaryGPSDataStream::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mu16GPSReceiverType;
  stream << " ";
  stream << mu32Reserved;
  stream << " ";
  stream << mu16VariableMsgByteCount;
  stream << " ";
  for (uint16_t i = 0; i < mu16VariableMsgByteCount; i++) {
    stream << hex << (uint16_t)mau8GPSReceiverRawData[i] << dec;
    stream << " ";
  }
}

PrimaryGPSDataStream* PrimaryGPSDataStream::clone() const {
  return new PrimaryGPSDataStream(*this);
}
