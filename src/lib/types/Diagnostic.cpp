#include "types/Diagnostic.h"

#include "com/Connection.h"
#include "serialization/TypesFactory.h"

#include <fstream>

using namespace std;

const Diagnostic Diagnostic::mProto;

Diagnostic::Diagnostic() : Group(20000) {
}

Diagnostic::Diagnostic(const Diagnostic &other) : Group(other) {
}

Diagnostic::~Diagnostic() {
}

void Diagnostic::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("Diagnostic::read: Wrong byte count");

  stream >> mTimeDistance;

  uint8_t u8Byte;
  for (uint32_t i = 0; i < u16ByteCount - 30; i++)
    stream >> u8Byte;
}

void Diagnostic::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
}

Diagnostic* Diagnostic::clone() const {
  return new Diagnostic(*this);
}
