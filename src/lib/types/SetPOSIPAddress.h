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

/** \file SetPOSIPAddress.h
    \brief This file defines the SetPOSIPAddress class, which
           represents the IP Control message from the Applanix
  */

#ifndef SETPOSIPADDRESS_H
#define SETPOSIPADDRESS_H

#include "types/Message.h"

/** The class SetPOSIPAddress represents the IP Control message from the
    Applanix.
    \brief IP Control message
  */
class SetPOSIPAddress :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  SetPOSIPAddress();
  /// Copy constructor
  SetPOSIPAddress(const SetPOSIPAddress& other);
  /// Assignement operator
  SetPOSIPAddress& operator = (const SetPOSIPAddress& other);
  /// Destructor
  virtual ~SetPOSIPAddress();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual SetPOSIPAddress* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 16;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// IP Address: Network part 1
  uint8_t mNetworkPart1;
  /// IP Address: Network part 2
  uint8_t mNetworkPart2;
  /// IP Address: Host part 1
  uint8_t mHostPart1;
  /// IP Address: Host part 2
  uint8_t mHostPart2;
  /// Subnet: Network part 1
  uint8_t mSubNetworkPart1;
  /// Subnet: Network part 2
  uint8_t mSubNetworkPart2;
  /// Subnet: Host part 1
  uint8_t mSubHostPart1;
  /// Subnet: Host part 2
  uint8_t mSubHostPart2;
  /// Prototype for this group
  static const SetPOSIPAddress mProto;
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

#endif // SETPOSIPADDRESS_H
