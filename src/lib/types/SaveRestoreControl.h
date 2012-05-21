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

/** \file SaveRestoreControl.h
    \brief This file defines the SaveRestoreControl class, which
           represents the Save and Restore Control message from the Applanix
  */

#ifndef SAVERESTORECONTROL_H
#define SAVERESTORECONTROL_H

#include "types/Message.h"

/** The class SaveRestoreControl represents the Save and Restore Control
    message from the Applanix.
    \brief Save and Restore Control message
  */
class SaveRestoreControl :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  SaveRestoreControl();
  /// Copy constructor
  SaveRestoreControl(const SaveRestoreControl& other);
  /// Assignement operator
  SaveRestoreControl& operator = (const SaveRestoreControl& other);
  /// Destructor
  virtual ~SaveRestoreControl();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual SaveRestoreControl* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 8;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// Control to apply
  uint8_t mControl;
  /// Prototype for this group
  static const SaveRestoreControl mProto;
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

#endif // SAVERESTORECONTROL_H
