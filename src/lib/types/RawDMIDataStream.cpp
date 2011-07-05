#include "types/RawDMIDataStream.h"

#include "com/Connection.h"

#include <fstream>

using namespace std;

const RawDMIDataStream RawDMIDataStream::mProto;

RawDMIDataStream::RawDMIDataStream() : Group(10006) {
}

RawDMIDataStream::RawDMIDataStream(const RawDMIDataStream &other)
  : Group(other) {
}

RawDMIDataStream::~RawDMIDataStream() {
}

void RawDMIDataStream::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("RawEvent1::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mi32UpDownPulseCount;
  stream >> mu32RectifiedPulseCount;
  stream >> mi32EventCount;
  stream >> mu32ReservedCount;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("RawEvent1::read: Wrong pad");
}

void RawDMIDataStream::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mi32UpDownPulseCount;
  stream << " ";
  stream << mu32RectifiedPulseCount;
  stream << " ";
  stream << mi32EventCount;
  stream << " ";
  stream << mu32ReservedCount;
}

RawDMIDataStream* RawDMIDataStream::clone() const {
  return new RawDMIDataStream(*this);
}
