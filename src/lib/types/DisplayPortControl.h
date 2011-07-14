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

/** \file DisplayPortControl.h
    \brief This file defines the DisplayPortControl class, which
           represents the Display Port Control message from the Applanix
  */

#ifndef DISPLAYPORTCONTROL_H
#define DISPLAYPORTCONTROL_H

#include "types/Message.h"
#include "exceptions/IOException.h"

#include <vector>

/** The class DisplayPortControl represents the Display Port Control
    message from the Applanix.
    \brief Display Port Control message
  */
class DisplayPortControl :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  DisplayPortControl();
  /// Copy constructor
  DisplayPortControl(const DisplayPortControl& other);
  /// Assignement operator
  DisplayPortControl& operator = (const DisplayPortControl& other);
  /// Destructor
  virtual ~DisplayPortControl();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual DisplayPortControl* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 10;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// Number of groups selected for Display Port
  uint16_t mNumGroups;
  /// Groups ID to output
  std::vector<uint16_t> mGroupsIDVector;
  /// Reserved stuff
  uint16_t mReserved;
  /// Checksum when receiving
  uint16_t mChecksum;
  /// Prototype for this group
  static const DisplayPortControl mProto;
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
  virtual void write(POSLVControl& stream) const throw (IOException);
  /** @}
    */

};

#endif // DISPLAYPORTCONTROL_H
