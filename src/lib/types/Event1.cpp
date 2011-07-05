#include "types/Event1.h"

#include "com/Connection.h"
#include "serialization/TypesFactory.h"

#include <fstream>

using namespace std;

const Event1 Event1::mProto;

Event1::Event1() : Group(5) {
}

Event1::Event1(const Event1 &other) : Group(other) {
}

Event1::~Event1() {
}

void Event1::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("Event1::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mu32EventPulseNumber;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("Event1::read: Wrong byte count");
}

void Event1::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mu32EventPulseNumber;
}

Event1* Event1::clone() const {
  return new Event1(*this);
}
