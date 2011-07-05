#include "types/RawEvent1.h"

#include "com/Connection.h"

#include <fstream>

using namespace std;

const RawEvent1 RawEvent1::mProto;

RawEvent1::RawEvent1() : Group(10004) {
}

RawEvent1::RawEvent1(const RawEvent1 &other) : Group(other) {
}

RawEvent1::~RawEvent1() {
}

void RawEvent1::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("RawEvent1::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mu32Event1PulseCount;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("RawEvent1::read: Wrong pad");
}

void RawEvent1::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mu32Event1PulseCount;
}

RawEvent1* RawEvent1::clone() const {
  return new RawEvent1(*this);
}
