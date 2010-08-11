#ifndef TYPESFACTORY_H
#define TYPESFACTORY_H

#include "GroupCreationException.h"

#include <map>

#include <stdint.h>

class Group;

class TypesFactory {
  static std::map<uint16_t, const Group*> mTypesMap;

  TypesFactory();

public:
  static void registerType(const Group *groupPtr, uint16_t u16TypeID);

  static Group* createGroup(uint16_t u16TypeID) throw(GroupCreationException);

  static TypesFactory& getInstance();

protected:

};

#endif // TYPESFACTORY_H
