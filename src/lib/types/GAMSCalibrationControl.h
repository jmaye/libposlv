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

/** \file GAMSCalibrationControl.h
    \brief This file defines the GAMSCalibrationControl class, which
           represents the Installation Calibration Control message from the
           Applanix
  */

#ifndef GAMSCALIBRATIONCONTROL_H
#define GAMSCALIBRATIONCONTROL_H

#include "types/Message.h"

/** The class GAMSCalibrationControl represents the Installation
    Calibration Control message from the Applanix.
    \brief Installation Calibration Control message
  */
class GAMSCalibrationControl :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  GAMSCalibrationControl();
  /// Copy constructor
  GAMSCalibrationControl(const GAMSCalibrationControl& other);
  /// Assignement operator
  GAMSCalibrationControl& operator =
    (const GAMSCalibrationControl& other);
  /// Destructor
  virtual ~GAMSCalibrationControl();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual GAMSCalibrationControl* clone() const;
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
  /// Prototype for this group
  static const GAMSCalibrationControl mProto;
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
  virtual void read(POSLVControl& stream);
  /// Writes to the network
  virtual void write(POSLVControl& stream) const;
  /** @}
    */

};

#endif // GAMSCALIBRATIONCONTROL_H
