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

/** \file GAMSInstallationControl.h
    \brief This file defines the GAMSInstallationControl class, which
           represents the GAMS Installation Control message from the Applanix
  */

#ifndef GAMSINSTALLATIONCONTROL_H
#define GAMSINSTALLATIONCONTROL_H

#include "types/Message.h"
#include "exceptions/IOException.h"

/** The class GAMSInstallationControl represents the GAMS Installation Control
    message from the Applanix.
    \brief GAMS Installation Control message
  */
class GAMSInstallationControl :
  public Message {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  GAMSInstallationControl();
  /// Copy constructor
  GAMSInstallationControl(const GAMSInstallationControl& other);
  /// Assignement operator
  GAMSInstallationControl& operator = (const GAMSInstallationControl& other);
  /// Destructor
  virtual ~GAMSInstallationControl();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual GAMSInstallationControl* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 32;
  /// Transaction number
  uint16_t mTransactionNumber;
  /// Primary-secondary antenna separation
  float mAntennaSeparation;
  /// Baseline vector X component
  float mBaselineX;
  /// Baseline vector Y component
  float mBaselineY;
  /// Baseline vector Z component
  float mBaselineZ;
  /// Maximum heading error RMS for calibration
  float mMaxHeadingError;
  /// Heading correction
  float mHeadingCorrection;
  /// Checksum when receiving
  uint16_t mChecksum;
  /// Prototype for this group
  static const GAMSInstallationControl mProto;
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

#endif // GAMSINSTALLATIONCONTROL_H
