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

/** \file TypesFactory.h
    \brief This file defines the TypesFactory class, which implements the object
           factory design pattern
  */
#ifndef TYPESFACTORY_H
#define TYPESFACTORY_H

#include "exceptions/GroupCreationException.h"

#include <map>

class Group;

/** The class TypesFactory implements the object factory design pattern.
    \brief Types factory design pattern
  */
class TypesFactory {
  /** \name Private members
    @{
    */
  /// Contains the mapping between types and ID
  static std::map<size_t, const Group*> mTypesMap;
  /** @}
    */

  /** \name Private constructors/destructor
    @{
    */
  /// Default constructor
  TypesFactory();
  /// Destructor
  ~TypesFactory();
  /** @}
    */

public:
  /** \name Accessors
    @{
    */
  /// Access the static instance of the factory
  static TypesFactory& getInstance();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Register a type to the factory
  static void registerType(const Group* groupPtr, size_t typeID);
  /// Creates a group from a typeID
  static Group* createGroup(size_t typeID) throw (GroupCreationException);
  /** @}
    */

protected:

};

#endif // TYPESFACTORY_H
