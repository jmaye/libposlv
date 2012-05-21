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

/** \file Message.h
    \brief This file defines the Message class, which is the base class for all
           Applanix messages
  */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <stdint.h>

#include "exceptions/TypeCastException.h"
#include "types/Packet.h"

class BinaryReader;
class BinaryWriter;

/** The class Message is the base class for all Applanix messages.
    \brief Base class for Applanix messages
  */
class Message :
//  public virtual Serializable,
  public Packet {
  /// Stream operator for writing to a connection
  friend BinaryWriter& operator << (BinaryWriter& stream, const
    Message& obj);
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Constructs a new Message with given type ID
  Message(uint16_t typeID);
  /// Copy constructor
  Message(const Message& other);
  /// Assignement operator
  Message& operator = (const Message& other);
  /// Destructor
  virtual ~Message();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the type ID of the Message
  uint16_t getTypeID() const;
  /// Returns the checksum of the Message
  uint16_t getChecksum() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this Message
  virtual Message* clone() const = 0;
  /// Cast the Message into something else
  template<class O> const O& typeCast() const {
    if (this->mTypeID == O::mProto.mTypeID)
      return (const O&)*this;
    else
      throw TypeCastException("Message::typeCast(): cast failed");
  }
  /// Cast the Message into something else
  template<class O> O& typeCast() {
    if (this->mTypeID == O::mProto.mTypeID)
      return (O&)*this;
    else
      throw TypeCastException("Message::typeCast(): cast failed");
  }
  /// Check if a Message is an instance of something
  template<class O> bool instanceOf() const {
    if (this->mTypeID == O::mProto.mTypeID)
      return true;
    else
      return false;
  }
  /// Check if a Message is an instance of something
  template<class O> bool instanceOf() {
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
  /// Writes to the network
  virtual void write(BinaryWriter& stream) const = 0;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Type ID
  uint16_t mTypeID;
  /// Computed checksum when reading
  uint16_t mChecksum;
  /** @}
    */

};

#endif // MESSAGE_H
