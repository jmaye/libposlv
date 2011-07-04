#include "utils/TypesFactory.h"

#include "types/Group.h"

using namespace std;

map<uint16_t, const Group*> TypesFactory::mTypesMap;

TypesFactory::TypesFactory() {
}

TypesFactory& TypesFactory::getInstance() {
  static TypesFactory* instance = new TypesFactory();
  return *instance;
}

void TypesFactory::registerType(const Group *groupPtr, uint16_t u16TypeID) {
  if (mTypesMap.find(u16TypeID) == mTypesMap.end())
    mTypesMap[u16TypeID] = groupPtr;
}

Group* TypesFactory::createGroup(uint16_t u16TypeID)
  throw(GroupCreationException)
{
  if (mTypesMap.find(u16TypeID) != mTypesMap.end())
    return mTypesMap[u16TypeID]->clone();
  else
    throw GroupCreationException("TypesFactory: Unknown group ID");
}
