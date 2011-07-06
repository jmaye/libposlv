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

/** \file RawEvent2.h
    \brief This file defines the RawEvent2 class, which
           represents the Raw Event 2 message from the Applanix
  */

#ifndef RAWEVENT2_H
#define RAWEVENT2_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

/** The class RawEvent2 represents the Raw Event 2 message from the Applanix.
    \brief Raw Event 2 message
  */
class RawEvent2 :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  RawEvent2();
  /// Copy constructor
  RawEvent2(const RawEvent2& other);
  /// Assignement operator
  RawEvent2& operator = (const RawEvent2& other);
  /// Destructor
  virtual ~RawEvent2();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual RawEvent2* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 36;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Event 2 pulse count
  uint32_t mEvent2PulseCount;
  /// Prototype for this group
  static const RawEvent2 mProto;
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
  virtual void read(Connection& stream) throw (IOException);
  /** @}
    */

};

#endif // RAWEVENT2_H
