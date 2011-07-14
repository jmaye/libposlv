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

/** \file ZUPDControl.h
    \brief This file defines the ZUPDControl class, which
           represents the ZUPD Control message from the Applanix
  */

#ifndef ZUPDCONTROL_H
#define ZUPDCONTROL_H

#include "types/Message.h"
#include "exceptions/IOException.h"

/** The class ZUPDControl represents the Zero Velocity Update Control
    message from the Applanix.
    \brief Zero Velocity Update Control message
  */
class ZUPDControl :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  ZUPDControl();
  /// Copy constructor
  ZUPDControl(const ZUPDControl& other);
  /// Assignement operator
  ZUPDControl& operator = (const ZUPDControl& other);
  /// Destructor
  virtual ~ZUPDControl();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual ZUPDControl* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 24;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// Control
  uint16_t mControl;
  /// Detect zero velocity threshold
  float mDetectZeroVelocityThreshold;
  /// Reject zero velocity threshold
  float mRejectZeroVelocityThreshold;
  /// Zero velocity test period
  float mZeroVelocityTestPeriod;
  /// ZUPD standard deviation
  float mZUPDStd;
  /// Prototype for this group
  static const ZUPDControl mProto;
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
  virtual void read(POSLVMessageRead& stream) throw (IOException);
  /// Writes to the network
  virtual void write(POSLVMessageWrite& stream) const;
  /** @}
    */

};

#endif // ZUPDCONTROL_H
