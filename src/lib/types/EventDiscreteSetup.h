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

/** \file EventDiscreteSetup.h
    \brief This file defines the EventDiscreteSetup class, which
           represents the Primary GPS Setup message from the Applanix
  */

#ifndef EVENTDISCRETESETUP_H
#define EVENTDISCRETESETUP_H

#include "types/Message.h"

/** The class EventDiscreteSetup represents the Primary GPS Setup
    message from the Applanix.
    \brief Primary GPS Setup message
  */
class EventDiscreteSetup :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  EventDiscreteSetup();
  /// Copy constructor
  EventDiscreteSetup(const EventDiscreteSetup& other);
  /// Assignement operator
  EventDiscreteSetup& operator = (const EventDiscreteSetup& other);
  /// Destructor
  virtual ~EventDiscreteSetup();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual EventDiscreteSetup* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 8;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// Event 1 trigger
  uint8_t mEvent1Trigger;
  /// Event 2 trigger
  uint8_t mEvent2Trigger;
  /// Prototype for this group
  static const EventDiscreteSetup mProto;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const ;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /// Reads from the network
  virtual void read(BinaryReader& stream);
  /// Writes to the network
  virtual void write(BinaryWriter& stream) const;
  /** @}
    */

};

#endif // EVENTDISCRETESETUP_H
