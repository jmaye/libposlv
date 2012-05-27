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

/** \file SecondaryGPSSetup.h
    \brief This file defines the SecondaryGPSSetup class, which
           represents the Primary GPS Setup message from the Applanix
  */

#ifndef SECONDARYGPSSETUP_H
#define SECONDARYGPSSETUP_H

#include "types/Message.h"

/** The class SecondaryGPSSetup represents the Primary GPS Setup
    message from the Applanix.
    \brief Primary GPS Setup message
  */
class SecondaryGPSSetup :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  SecondaryGPSSetup();
  /// Copy constructor
  SecondaryGPSSetup(const SecondaryGPSSetup& other);
  /// Assignement operator
  SecondaryGPSSetup& operator = (const SecondaryGPSSetup& other);
  /// Destructor
  virtual ~SecondaryGPSSetup();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual SecondaryGPSSetup* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 16;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// Select/deselect GPS AutoConfig
  uint8_t mGPSAutoConfig;
  /// Com port setup
  uint8_t mComPortRate;
  /// Reserved stuff
  uint8_t mReserved[6];
  /// Prototype for this group
  static const SecondaryGPSSetup mProto;
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

#endif // SECONDARYGPSSETUP_H
