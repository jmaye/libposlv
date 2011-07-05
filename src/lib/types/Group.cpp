#include "types/Group.h"

#include "base/Factory.h"

#include <fstream>

Group::Group() throw (TypeCreationException<uint16_t>) :
  mu16TypeID(0xffff) {
  throw TypeCreationException<uint16_t>(mu16TypeID, "Group::Group(): invalid type creation");
}

Group::Group(uint16_t u16TypeID) :
  mu16TypeID(u16TypeID) {
  Factory<uint16_t, Group>::getInstance().registerType(this, u16TypeID);
}

Group::Group(const Group& other) :
  mu16TypeID(other.mu16TypeID) {
}

Group::~Group() {
}

uint16_t Group::getTypeID() const {
  return mu16TypeID;
}

Connection& operator >> (Connection& stream, Group& obj) {
  obj.read(stream);
  return stream;
}

std::ofstream& operator << (std::ofstream& stream, const Group& obj) {
  obj.write(stream);
  return stream;
}
