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

/** \file Event2.h
    \brief This file defines the Event2 class, which represents the Event 2
           message from the Applanix
  */

#ifndef EVENT2_H
#define EVENT2_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class Event2 represents the Event 2 message from the Applanix.
    \brief Event 2 message
  */
class Event2 :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  Event2();
  /// Copy constructor
  Event2(const Event2& other);
  /// Assignement operator
  Event2& operator = (const Event2& other);
  /// Destructor
  virtual ~Event2();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual Event2* clone() const;
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
  static const Event2 mProto;
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
  virtual void read(POSLVGroupRead& stream) throw (IOException);
  /** @}
    */

};

#endif // EVENT2_H
