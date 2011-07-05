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

#include <iosfwd>

#include <stdint.h>

class Connection;

/** The class Group is the base class for all Applanix messages.
    \brief Base class for Applanix messages
  */
class Group {
  /// Stream operator for reading from a connection
  friend Connection& operator >> (Connection& stream, Group& obj);
   /// Stream operator for writing to a file
  friend std::ofstream& operator << (std::ofstream& stream, const Group &obj);
  /// Reads from a connection
  virtual void read(Connection& stream) = 0;
  /// Writes to a file
  virtual void write(std::ofstream& stream) const = 0;

public:
  virtual ~Group();

  virtual Group* clone() const = 0;

  virtual uint16_t getTypeID() const;

  template<class O> const O& typeCast() const throw (TypeCastException) {
    if (this->mu16TypeID == O::mProto.mu16TypeID)
      return (const O&)*this;
    else
      throw TypeCastException("Group::typeCast(): cast failed");
  }

  template<class O> O& typeCast() throw (TypeCastException) {
    if (this->mu16TypeID == O::mProto.mu16TypeID)
      return (O&)*this;
    else
      throw TypeCastException("Group::typeCast(): cast failed");
  }

  template<class O> bool instanceof() const {
    if (this->mu16TypeID == O::mProto.mu16TypeID)
      return true;
    else
      return false;
  }

  template<class O> bool instanceof() {
    if (this->mu16TypeID == O::mProto.mu16TypeID)
      return true;
    else
      return false;
  }

protected:
  Group() throw (TypeCreationException<uint16_t>);
  Group(uint16_t u16TypeID);
  Group(const Group& other);
  Group& operator = (const Group& other);

  const uint16_t mu16TypeID;

};

#endif // GROUP_H
