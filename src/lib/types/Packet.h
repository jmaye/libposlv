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

/** \file Packet.h
    \brief This file defines the Packet class, which is the base class for all
           Applanix packets
  */

#ifndef PACKET_H
#define PACKET_H

#include <string>

#include "base/Serializable.h"
#include "exceptions/TypeCastException.h"

class BinaryReader;
class Group;
class Message;

/** The class Packet is the base class for all Applanix packets.
    \brief Base class for Applanix packets
  */
class Packet:
  public virtual Serializable {
  /// Stream operator
  friend BinaryReader& operator >> (BinaryReader& stream, Packet& obj);
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Constructs a new packet
  Packet(const std::string& start);
  /// Copy constructor
  Packet(const Packet& other);
  /// Assignement operator
  Packet& operator = (const Packet& other);
  /// Destructor
  virtual ~Packet();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the start of the packet
  const std::string& getStart() const;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Cast the packet into a group
  const Group& groupCast() const {
    if (this->mStart == "$GRP")
      return (const Group&)*this;
    else
      throw TypeCastException("Packet::groupCast(): cast failed");
  }
  /// Cast the packet into a group
  Group& groupCast() {
    if (this->mStart == "$GRP")
      return (Group&)*this;
    else
      throw TypeCastException("Packet::groupCast(): cast failed");
  }
  /// Check if a packet is an instance of a group
  bool instanceOfGroup() const {
    if (this->mStart == "$GRP")
      return true;
    else
      return false;
  }
  /// Check if a packet is an instance of a group
  bool instanceOfGroup() {
    if (this->mStart == "$GRP")
      return true;
    else
      return false;
  }
  /// Cast the packet into a message
  const Message& messageCast() const {
    if (this->mStart == "$MSG")
      return (const Message&)*this;
    else
      throw TypeCastException("Packet::messageCast(): cast failed");
  }
  /// Cast the packet into a message
  Message& messageCast() {
    if (this->mStart == "$MSG")
      return (Message&)*this;
    else
      throw TypeCastException("Packet::messageCast(): cast failed");
  }
  /// Check if a packet is an instance of a message
  bool instanceOfMessage() const {
    if (this->mStart == "$MSG")
      return true;
    else
      return false;
  }
  /// Check if a packet is an instance of a message
  bool instanceOfMessage() {
    if (this->mStart == "$MSG")
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
  /// Reads from the stream
  virtual void read(BinaryReader& stream) = 0;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Start string of the packet
  std::string mStart;
  /** @}
    */

};

#endif // PACKET_H
