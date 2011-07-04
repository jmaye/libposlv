#include "types/RawPPS.h"

#include "com/Connection.h"
#include "serialization/TypesFactory.h"

#include <fstream>

using namespace std;

const RawPPS RawPPS::mProto;

RawPPS::RawPPS() : Group(10003) {
}

RawPPS::RawPPS(const RawPPS &other)
  : Group(other) {
}

RawPPS::~RawPPS() {
}

void RawPPS::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("RawPPS::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mu16PPSPulseCount;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("RawPPS::read: Wrong pad");
}

void RawPPS::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mu16PPSPulseCount;
}

RawPPS* RawPPS::clone() const {
  return new RawPPS(*this);
}
