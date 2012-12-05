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

/** \file COMPortSetup.h
    \brief This file defines the COMPortSetup class, which
           represents the COM Port Setup message from the Applanix
  */

#ifndef COMPORTSETUP_H
#define COMPORTSETUP_H

#include "types/Message.h"
#include "types/COMPortParameters.h"

/** The class COMPortSetup represents the COM Port Setup message from the
    Applanix.
    \brief COM Port Setup message
  */
class COMPortSetup :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  COMPortSetup();
  /// Copy constructor
  COMPortSetup(const COMPortSetup& other);
  /// Assignement operator
  COMPortSetup& operator = (const COMPortSetup& other);
  /// Destructor
  virtual ~COMPortSetup();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual COMPortSetup* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 12;
  /// Read byte count
  uint16_t mReadByteCount;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// Number of COM ports
  uint16_t mNumPorts;
  /// COM Port Parameters
  COMPortParameters mpParameters[10];
  /// Port mask
  uint16_t mPortMask;
  /// Prototype for this group
  static const COMPortSetup mProto;
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

#endif // COMPORTSETUP_H
