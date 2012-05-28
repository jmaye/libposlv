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

/** \file UserAccuracySpec.h
    \brief This file defines the UserAccuracySpec class, which
           represents the User Accuracy Control message from the Applanix
  */

#ifndef USERACCURACYSPEC_H
#define USERACCURACYSPEC_H

#include "types/Message.h"

/** The class UserAccuracySpec represents the User Accuracy Control
    message from the Applanix.
    \brief User Accuracy Control message
  */
class UserAccuracySpec :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  UserAccuracySpec();
  /// Copy constructor
  UserAccuracySpec(const UserAccuracySpec& other);
  /// Assignement operator
  UserAccuracySpec& operator = (const UserAccuracySpec& other);
  /// Destructor
  virtual ~UserAccuracySpec();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual UserAccuracySpec* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 24;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// Attitude accuracy
  float mAttitudeAccuracy;
  /// Heading accuracy
  float mHeadingAccuracy;
  /// Position accuracy
  float mPositionAccuracy;
  /// Velocity accuracy
  float mVelocityAccuracy;
  /// Prototype for this group
  static const UserAccuracySpec mProto;
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

#endif // USERACCURACYSPEC_H
