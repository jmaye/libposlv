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

/** \file Acknowledge.h
    \brief This file defines the Acknowledge class, which
           represents the Acknowledge message from the Applanix
  */

#ifndef ACKNOWLDEGE_H
#define ACKNOWLDEGE_H

#include "types/Message.h"
#include "exceptions/IOException.h"

/** The class Acknowledge represents the Acknowledge message from the Applanix.
    \brief Acknowledge message
  */
class Acknowledge :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  Acknowledge();
  /// Copy constructor
  Acknowledge(const Acknowledge& other);
  /// Assignement operator
  Acknowledge& operator = (const Acknowledge& other);
  /// Destructor
  virtual ~Acknowledge();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual Acknowledge* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 44;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// ID of message
  uint16_t mID;
  /// Response code
  uint16_t mResponseCode;
  /// New parameters status
  uint8_t mNewParamsStatus;
  /// Name of rejected parameter
  uint8_t mParameterName[32];
  /// Prototype for this group
  static const Acknowledge mProto;
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
  virtual void read(POSLVControl& stream) throw (IOException);
  /// Writes to the network
  virtual void write(POSLVControl& stream) const;
  /** @}
    */

};

#endif // ACKNOWLDEGE_H
