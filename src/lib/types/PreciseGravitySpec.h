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

/** \file PreciseGravitySpec.h
    \brief This file defines the PreciseGravitySpec class, which
           represents the Gravity Control message from the Applanix
  */

#ifndef PRECISEGRAVITYSPEC_H
#define PRECISEGRAVITYSPEC_H

#include "types/Message.h"

/** The class PreciseGravitySpec represents the Gravity Control
    message from the Applanix.
    \brief Gravity Control message
  */
class PreciseGravitySpec :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  PreciseGravitySpec();
  /// Copy constructor
  PreciseGravitySpec(const PreciseGravitySpec& other);
  /// Assignement operator
  PreciseGravitySpec& operator = (const PreciseGravitySpec& other);
  /// Destructor
  virtual ~PreciseGravitySpec();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual PreciseGravitySpec* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 56;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// Magnitude
  double mMagnitude;
  /// North deflection
  double mNorthDeflection;
  /// East deflection
  double mEastDeflection;
  /// Latitude of validity
  double mLatitudeValidity;
  /// Longitude of validity
  double mLongitudeValidity;
  /// Altitude of validity
  double mAltitudeValidity;
  /// Prototype for this group
  static const PreciseGravitySpec mProto;
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

#endif // PRECISEGRAVITYSPEC_H
