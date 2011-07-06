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

/** \file UserTimeStatus.h
    \brief This file defines the UserTimeStatus class, which
           represents the User Time Status message from the Applanix
  */

#ifndef USERTIMESTATUS_H
#define USERTIMESTATUS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class UserTimeStatus represents the User Time Status message from
    the Applanix.
    \brief User Time Status message
  */
class UserTimeStatus :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  UserTimeStatus();
  /// Copy constructor
  UserTimeStatus(const UserTimeStatus& other);
  /// Assignement operator
  UserTimeStatus& operator = (const UserTimeStatus& other);
  /// Destructor
  virtual ~UserTimeStatus();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual UserTimeStatus* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 40;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Number fo time sync message rejections
  uint32_t mNumberOfTimeSynchMessageRejections;
  /// Number of user time resynchronizations
  uint32_t mNumberOfUserTimeResynchronizations;
  /// User time valid
  uint8_t mUserTimeValid;
  /// Time Sync message received
  uint8_t mTimeSynchMessageReceived;
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

  /** \name Protected members
    @{
    */
  /// Prototype for this group
  static const UserTimeStatus mProto;
  /** @}
    */

};

#endif // USERTIMESTATUS_H
