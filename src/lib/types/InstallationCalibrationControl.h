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

/** \file InstallationCalibrationControl.h
    \brief This file defines the InstallationCalibrationControl class, which
           represents the Installation Calibration Control message from the
           Applanix
  */

#ifndef INSTALLATIONCALIBRATIONCONTROL_H
#define INSTALLATIONCALIBRATIONCONTROL_H

#include "types/Message.h"

/** The class InstallationCalibrationControl represents the Installation
    Calibration Control message from the Applanix.
    \brief Installation Calibration Control message
  */
class InstallationCalibrationControl :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  InstallationCalibrationControl();
  /// Copy constructor
  InstallationCalibrationControl(const InstallationCalibrationControl& other);
  /// Assignement operator
  InstallationCalibrationControl& operator =
    (const InstallationCalibrationControl& other);
  /// Destructor
  virtual ~InstallationCalibrationControl();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual InstallationCalibrationControl* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 8;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// Calibration action
  uint8_t mCalibrationAction;
  /// Calibration select
  uint8_t mCalibrationSelect;
  /// Prototype for this group
  static const InstallationCalibrationControl mProto;
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

#endif // INSTALLATIONCALIBRATIONCONTROL_H
