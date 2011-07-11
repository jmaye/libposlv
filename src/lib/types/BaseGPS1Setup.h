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

/** \file BaseGPS1Setup.h
    \brief This file defines the BaseGPS1Setup class, which
           represents the Program Control message from the Applanix
  */

#ifndef BASEGPS1SETUP_H
#define BASEGPS1SETUP_H

#include "types/Message.h"

/** The class BaseGPS1Setup represents the Program Control message from the
    Applanix.
    \brief Program Control message
  */
class BaseGPS1Setup :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  BaseGPS1Setup();
  /// Copy constructor
  BaseGPS1Setup(const BaseGPS1Setup& other);
  /// Assignement operator
  BaseGPS1Setup& operator = (const BaseGPS1Setup& other);
  /// Destructor
  virtual ~BaseGPS1Setup();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual BaseGPS1Setup* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 240;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// GSP input type
  uint16_t mBaseGPSInputType;
  /// Line control
  uint8_t mLineControl;
  /// Modem control
  uint8_t mModemControl;
  /// Connection control
  uint8_t mConnectionControl;
  /// Phone number
  uint8_t mPhoneNumber[32];
  /// Redials numbers
  uint8_t mRedialsNumber;
  /// Modem command string
  uint8_t mModemCommandString[64];
  /// Modem init string
  uint8_t mModemInitString[128];
  /// Data timeout
  uint16_t mDataTimeout;
  /// Prototype for this group
  static const BaseGPS1Setup mProto;
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
  virtual void read(POSLVControl& stream);
  /// Writes to the network
  virtual void write(POSLVControl& stream) const;
  /** @}
    */

};

#endif // BASEGPS1SETUP_H
