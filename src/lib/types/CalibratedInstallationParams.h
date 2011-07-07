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

/** \file CalibratedInstallationParams.h
    \brief This file defines the CalibratedInstallationParams class, which
           represents the Calibrated Installation Parameters message from the
           Applanix
  */

#ifndef CALIBRATEDINSTALLATIONPARAMS_H
#define CALIBRATEDINSTALLATIONPARAMS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class CalibratedInstallationParams represents the Calibrated
    Installation Parameters message from the Applanix.
    \brief Calibrated Installation Parameters message
  */
class CalibratedInstallationParams :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  CalibratedInstallationParams();
  /// Copy constructor
  CalibratedInstallationParams(const CalibratedInstallationParams& other);
  /// Assignement operations
  CalibratedInstallationParams& operator =
    (const CalibratedInstallationParams& other);
  /// Destructor
  virtual ~CalibratedInstallationParams();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual CalibratedInstallationParams* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 116;
  /// Time/Distance field of the message
  TimeDistance mTimeDistance;
  /// Calibration status
  uint16_t mCalibrationStatus;
  /// Reference to primary GPS X lever arm
  float mReferenceToPrimaryGPSXLeverArm;
  /// Reference to primary GPS Y lever arm
  float mReferenceToPrimaryGPSYLeverArm;
  /// Reference to primary GPS Z lever arm
  float mReferenceToPrimaryGPSZLeverArm;
  /// Reference to primary GPS FOM
  uint16_t mReferenceToPrimaryGPSLeverArmCalibrationFOM;
  /// Reference to auxiliary 1 GPS X lever arm
  float mReferenceToAuxiliary1GPSXLeverArm;
  /// Reference to auxiliary 1 GPS Y lever arm
  float mReferenceToAuxiliary1GPSYLeverArm;
  /// Reference to auxiliary 1 GPS Z lever arm
  float mReferenceToAuxiliary1GPSZLeverArm;
  /// Reference to auxiliary 1 GPS FOM
  uint16_t mReferenceToAuxiliary1GPSLeverArmCalibrationFOM;
  /// Reference to auxiliary 2 GPS X lever arm
  float mReferenceToAuxiliary2GPSXLeverArm;
  /// Reference to auxiliary 2 GPS Y lever arm
  float mReferenceToAuxiliary2GPSYLeverArm;
  /// Reference to auxiliary 2 GPS Z lever arm
  float mReferenceToAuxiliary2GPSZLeverArm;
  /// Reference to auxiliary 2 GPS FOM
  uint16_t mReferenceToAuxiliary2GPSLeverArmCalibrationFOM;
  /// Reference to DMI X lever arm
  float mReferenceToDMIXLeverArm;
  /// Reference to DMI Y lever arm
  float mReferenceToDMIYLeverArm;
  /// Reference to DMI Z lever arm
  float mReferenceToDMIZLeverArm;
  /// Reference to DMI FOM
  uint16_t mReferenceToDMILeverArmCalibrationFOM;
  /// DMI scale factor
  float mDMIScaleFactor;
  /// DMI FOM
  uint16_t mDMIScaleFactorCalibrationFOM;
  /// Reserved stuff
  float mReserved1;
  /// Reserved stuff
  float mReserved2;
  /// Reserved stuff
  float mReserved3;
  /// Reserved stuff
  uint16_t mReserved4;
  /// Reserved stuff
  float mReserved5;
  /// Reserved stuff
  uint16_t mReserved6;
  /// Prototype of this group
  static const CalibratedInstallationParams mProto;
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
  virtual void read(POSLVGroupRead& stream) throw (IOException);
  /** @}
    */

};

#endif // CALIBRATEDINSTALLATIONPARAMS_H
