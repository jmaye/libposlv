#include "Event2.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const Event2 Event2::mProto;

Event2::Event2() : Group(6) {
}

Event2::Event2(const Event2 &other) : Group(other) {
}

Event2::~Event2() {
}

void Event2::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("Event2::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mu32EventPulseNumber;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("Event2::read: Wrong pad");
}

void Event2::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mu32EventPulseNumber;
}

Event2* Event2::clone() const {
  return new Event2(*this);
}
