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

/** \file BaseGPS2Setup.h
    \brief This file defines the BaseGPS2Setup class, which
           represents the Base GPS 2 Control message from the Applanix
  */

#ifndef BASEGPS2SETUP_H
#define BASEGPS2SETUP_H

#include "types/Message.h"

/** The class BaseGPS2Setup represents the  Base GPS 2 Control message from
    the Applanix.
    \brief Base GPS 2 Control message
  */
class BaseGPS2Setup :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  BaseGPS2Setup();
  /// Copy constructor
  BaseGPS2Setup(const BaseGPS2Setup& other);
  /// Assignement operator
  BaseGPS2Setup& operator = (const BaseGPS2Setup& other);
  /// Destructor
  virtual ~BaseGPS2Setup();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual BaseGPS2Setup* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 240;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// Select Base GPS input type
  uint16_t mBaseGPSInputType;
  /// Line control
  uint8_t mLineControl;
  /// Modem control
  uint8_t mModemControl;
  /// Connection control
  uint8_t mConnectionControl;
  /// Phone number
  uint8_t mPhoneNumber[32];
  /// Number of redials
  uint8_t mNumRedials;
  /// Modem command string
  uint8_t mCommandString[64];
  /// Modem initialization string
  uint8_t mInitString[128];
  /// Data timeout length
  uint16_t mTimeoutLength;
  /// Prototype for this group
  static const BaseGPS2Setup mProto;
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

#endif // BASEGPS2SETUP_H
