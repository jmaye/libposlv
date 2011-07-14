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

/** \file COMPortControl.h
    \brief This file defines the COMPortControl class, which
           represents the COM Port Setup message from the Applanix
  */

#ifndef COMPORTCONTROL_H
#define COMPORTCONTROL_H

#include "types/Message.h"
#include "types/COMPortParameters.h"
#include "exceptions/IOException.h"

/** The class COMPortControl represents the COM Port Setup message from the
    Applanix.
    \brief COM Port Setup message
  */
class COMPortControl :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  COMPortControl();
  /// Copy constructor
  COMPortControl(const COMPortControl& other);
  /// Assignement operator
  COMPortControl& operator = (const COMPortControl& other);
  /// Destructor
  virtual ~COMPortControl();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual COMPortControl* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 12;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// Number of COM ports
  uint16_t mNumPorts;
  /// COM Port Parameters
  COMPortParameters mpParameters[10];
  /// Port mask
  uint16_t mPortMask;
  /// Prototype for this group
  static const COMPortControl mProto;
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
  virtual void write(POSLVMessageWrite& stream) const throw (IOException);
  /** @}
    */

};

#endif // COMPORTCONTROL_H
