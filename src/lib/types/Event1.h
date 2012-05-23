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

/** \file Event1.h
    \brief This file defines the Event1 class, which represents the Event 1
           message from the Applanix
  */

#ifndef EVENT1_H
#define EVENT1_H

#include "types/Group.h"
#include "types/TimeDistance.h"

/** The class Event1 represents the Event 1 message from the Applanix.
    \brief Event 1 message
  */
class Event1 :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  Event1();
  /// Copy constructor
  Event1(const Event1& other);
  /// Assignement operator
  Event1& operator = (const Event1& other);
  /// Destructor
  virtual ~Event1();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual Event1* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 36;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Pulse number
  uint32_t mEventPulseNumber;
  /// Prototype for this group
  static const Event1 mProto;
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

#endif // EVENT1_H
