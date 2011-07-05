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

/** \file Group.h
    \brief This file defines the Group class, which is the base class for all
           Applanix messages
  */

#ifndef GROUP_H
#define GROUP_H

#include "exceptions/TypeCastException.h"
#include "exceptions/TypeCreationException.h"
#include "base/Serializable.h"

#include <stdint.h>

class Connection;

/** The class Group is the base class for all Applanix messages.
    \brief Base class for Applanix messages
  */
class Group :
  public virtual Serializable {
  /// Stream operator for reading from a connection
  friend Connection& operator >> (Connection& stream, Group& obj);

public:
  /** \name Constructors/Destructor
    @{
    */
  /// Constructs a new group with given type ID
  Group(uint16_t typeID);
  /// Copy constructor
  Group(const Group& other);
  /// Assignement operator
  Group& operator = (const Group& other);
  /// Destructor
  virtual ~Group();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the type ID of the group
  uint16_t getTypeID() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual Group* clone() const = 0;
  /// Cast the group into something else
  template<class O> const O& typeCast() const throw (TypeCastException) {
    if (this->mTypeID == O::mProto.mTypeID)
      return (const O&)*this;
    else
      throw TypeCastException("Group::typeCast(): cast failed");
  }
  /// Cast the group into something else
  template<class O> O& typeCast() throw (TypeCastException) {
    if (this->mTypeID == O::mProto.mTypeID)
      return (O&)*this;
    else
      throw TypeCastException("Group::typeCast(): cast failed");
  }
  /// Check if a group is an instance of something
  template<class O> bool instanceof() const {
    if (this->mTypeID == O::mProto.mTypeID)
      return true;
    else
      return false;
  }
  /// Check if a group is an instance of something
  template<class O> bool instanceof() {
    if (this->mTypeID == O::mProto.mTypeID)
      return true;
    else
      return false;
  }
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream) = 0;
  /// Writes to standard output
  virtual void write(std::ostream& stream) const = 0;
  /// Reads from a file
  virtual void read(std::ifstream& stream) = 0;
  /// Writes to a file
  virtual void write(std::ofstream& stream) const = 0;
  /// Reads from the network
  virtual void read(Connection& stream) = 0;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Type ID
  uint16_t mTypeID;
  /** @}
    */

};

#endif // GROUP_H
