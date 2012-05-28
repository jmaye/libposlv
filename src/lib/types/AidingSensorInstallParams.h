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

/** \file AidingSensorInstallParams.h
    \brief This file defines the AidingSensorInstallParams class, which
           represents the Aiding Sensor Control message from the Applanix
  */

#ifndef AIDINGSENSORINSTALLPARAMS_H
#define AIDINGSENSORINSTALLPARAMS_H

#include "types/Message.h"

/** The class AidingSensorInstallParams represents the Aiding Sensor Control
    message from the Applanix.
    \brief Aiding Sensor Control message
  */
class AidingSensorInstallParams :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  AidingSensorInstallParams();
  /// Copy constructor
  AidingSensorInstallParams(const AidingSensorInstallParams& other);
  /// Assignement operator
  AidingSensorInstallParams& operator = (const AidingSensorInstallParams&
    other);
  /// Destructor
  virtual ~AidingSensorInstallParams();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual AidingSensorInstallParams* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 52;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// DMI scale factor
  float mDMIScaleFactor;
  /// Ref. to DMI X
  float mRefDMIX;
  /// Ref. to DMI Y
  float mRefDMIY;
  /// Ref. to DMI Z
  float mRefDMIZ;
  /// Reserved stuff
  float mReserved[7];
  /// Prototype for this group
  static const AidingSensorInstallParams mProto;
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

#endif // AIDINGSENSORINSTALLPARAMS_H
