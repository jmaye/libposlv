#include "types/Group.h"

#include "serialization/TypesFactory.h"

#include <fstream>

using namespace std;

Group::Group() throw(GroupCreationException) : mu16TypeID(0xffff) {
  throw GroupCreationException("Group: Wrong creation");
}

Group::Group(uint16_t u16TypeID) : mu16TypeID(u16TypeID) {
  TypesFactory::getInstance().registerType(this, u16TypeID);
}

Group::Group(const Group &other) : mu16TypeID(other.mu16TypeID) {
}

Group::~Group() {
}

uint16_t Group::getTypeID() const {
  return mu16TypeID;
}

Connection& operator >> (Connection &stream, Group &obj) throw(IOException) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream &stream,
  const Group &obj) {
  obj.write(stream);
  return stream;
}
