/******************************************************************************
 * Copyright (C) 2011 by Jerome Maye                                          *
 * jerome.maye@gmail.com                                                      *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#include "serialization/TypesFactory.h"

#include "types/Group.h"

std::map<size_t, const Group*> TypesFactory::mTypesMap;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

TypesFactory::TypesFactory() {
}

TypesFactory::~TypesFactory() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

TypesFactory& TypesFactory::getInstance() {
  static TypesFactory* instance = new TypesFactory();
  return *instance;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void TypesFactory::registerType(const Group* groupPtr, size_t typeID) {
  if (mTypesMap.find(typeID) == mTypesMap.end())
    mTypesMap[typeID] = groupPtr;
}

Group* TypesFactory::createGroup(size_t typeID) throw(GroupCreationException) {
  if (mTypesMap.find(typeID) != mTypesMap.end())
    return mTypesMap[typeID]->clone();
  else
    throw GroupCreationException("TypesFactory::createGroup(): unknown group ID");
}
