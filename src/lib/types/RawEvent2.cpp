#include "types/RawEvent2.h"

#include "com/Connection.h"
#include "utils/TypesFactory.h"

#include <fstream>

using namespace std;

const RawEvent2 RawEvent2::mProto;

RawEvent2::RawEvent2() : Group(10005) {
}

RawEvent2::RawEvent2(const RawEvent2 &other) : Group(other) {
}

RawEvent2::~RawEvent2() {
}

void RawEvent2::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("RawEvent2::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mu32Event2PulseCount;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("v::read: Wrong pad");
}

void RawEvent2::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mu32Event2PulseCount;
}

RawEvent2* RawEvent2::clone() const {
  return new RawEvent2(*this);
}
