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

/** \file PPSTimeRecoveryStatus.h
    \brief This file defines the PPSTimeRecoveryStatus class, which represents
           the PPS Time Recovery Status message from the Applanix
  */

#ifndef PPSTIMERECOVERYSTATUS_H
#define PPSTIMERECOVERYSTATUS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class PPSTimeRecoveryStatus represents the PPS Time Recovery Status
    message message from the Applanix.
    \brief PPS Time Recovery Status message
  */
class PPSTimeRecoveryStatus :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  PPSTimeRecoveryStatus();
  /// Copy constructor
  PPSTimeRecoveryStatus(const PPSTimeRecoveryStatus& other);
  /// Assignement operator
  PPSTimeRecoveryStatus& operator = (const PPSTimeRecoveryStatus& other);
  /// Destructor
  virtual ~PPSTimeRecoveryStatus();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual PPSTimeRecoveryStatus* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 36;
  /// Time/Distance field of the message
  TimeDistance mTimeDistance;
  /// PPS count
  uint32_t mPPSCount;
  /// Time synchro
  uint8_t mTimeSynchroStatus;
  /// Prototype for this group
  static const PPSTimeRecoveryStatus mProto;
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
  /// Reads from the network
  virtual void read(POSLVGroupRead& stream) throw (IOException);
  /** @}
    */

};

#endif // PPSTIMERECOVERYSTATUS_H
