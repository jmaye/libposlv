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

/** \file LoggingParamStatus.h
    \brief This file defines the LoggingParamStatus class, which represents the
           Logging and Parameters Status message from the Applanix
  */

#ifndef LOGGINGPARAMSTATUS_H
#define LOGGINGPARAMSTATUS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class LoggingParamStatus represents the Logging and Parameters Status
    message from the Applanix.
    \brief Logging and Parameters Status message
  */
class LoggingParamStatus :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  LoggingParamStatus();
  /// Copy constructor
  LoggingParamStatus(const LoggingParamStatus& other);
  /// Assignement operator
  LoggingParamStatus& operator = (const LoggingParamStatus& other);
  /// Destructor
  virtual ~LoggingParamStatus();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual LoggingParamStatus* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 48;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Disk remaining
  uint32_t mDiskKbytesRemaining;
  /// Disk logged
  uint32_t mDiskKbytesLogged;
  /// Disk logging remaining
  float mDiskLoggingTimeRemaining;
  /// Disk total
  uint32_t mDiskKbytesTotal;
  /// Logging state
  uint8_t mLoggingState;
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
  static const LoggingParamStatus mProto;
  /** @}
    */

};

#endif // LOGGINGPARAMSTATUS_H
