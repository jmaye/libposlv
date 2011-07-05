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

#include "types/CalibratedInstallationParams.h"

#include "com/Connection.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const CalibratedInstallationParams CalibratedInstallationParams::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

CalibratedInstallationParams::CalibratedInstallationParams() :
  Group(14) {
}

CalibratedInstallationParams::CalibratedInstallationParams(const
  CalibratedInstallationParams& other) :
  Group(other) {
}

CalibratedInstallationParams& CalibratedInstallationParams::operator =
  (const CalibratedInstallationParams& other) {
  this->Group::operator=(other);
  return *this;
}

CalibratedInstallationParams::~CalibratedInstallationParams() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void CalibratedInstallationParams::read(Connection& stream) throw(IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("CalibratedInstallationParams::read(): wrong byte count");

  stream >> mTimeDistance;
  stream >> mCalibrationStatus;
  stream >> mReferenceToPrimaryGPSXLeverArm;
  stream >> mReferenceToPrimaryGPSYLeverArm;
  stream >> mReferenceToPrimaryGPSZLeverArm;
  stream >> mReferenceToPrimaryGPSLeverArmCalibrationFOM;
  stream >> mReferenceToAuxiliary1GPSXLeverArm;
  stream >> mReferenceToAuxiliary1GPSYLeverArm;
  stream >> mReferenceToAuxiliary1GPSZLeverArm;
  stream >> mReferenceToAuxiliary1GPSLeverArmCalibrationFOM;
  stream >> mReferenceToAuxiliary2GPSXLeverArm;
  stream >> mReferenceToAuxiliary2GPSYLeverArm;
  stream >> mReferenceToAuxiliary2GPSZLeverArm;
  stream >> mReferenceToAuxiliary2GPSLeverArmCalibrationFOM;
  stream >> mReferenceToDMIXLeverArm;
  stream >> mReferenceToDMIYLeverArm;
  stream >> mReferenceToDMIZLeverArm;
  stream >> mReferenceToDMILeverArmCalibrationFOM;
  stream >> mDMIScaleFactor;
  stream >> mDMIScaleFactorCalibrationFOM;
  stream >> mReserved1;
  stream >> mReserved2;
  stream >> mReserved3;
  stream >> mReserved4;
  stream >> mReserved5;
  stream >> mReserved6;

  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("CalibratedInstallationParams::read(): wrong pad");
}

void CalibratedInstallationParams::read(std::istream& stream) {
}

void CalibratedInstallationParams::write(std::ostream& stream) const {
}

void CalibratedInstallationParams::read(std::ifstream& stream) {
}

void CalibratedInstallationParams::write(std::ofstream& stream) const {
//  stream << mu16TypeID;
//  stream << " ";
//  stream << mTimeDistance;
//  stream << mu16CalibrationStatus;
//  stream << " ";
//  stream << mf32ReferenceToPrimaryGPSXLeverArm;
//  stream << " ";
//  stream << mf32ReferenceToPrimaryGPSYLeverArm;
//  stream << " ";
//  stream << mf32ReferenceToPrimaryGPSZLeverArm;
//  stream << " ";
//  stream << mu16ReferenceToPrimaryGPSLeverArmCalibrationFOM;
//  stream << " ";
//  stream << mf32ReferenceToAuxiliary1GPSXLeverArm;
//  stream << " ";
//  stream << mf32ReferenceToAuxiliary1GPSYLeverArm;
//  stream << " ";
//  stream << mf32ReferenceToAuxiliary1GPSZLeverArm;
//  stream << " ";
//  stream << mu16ReferenceToAuxiliary1GPSLeverArmCalibrationFOM;
//  stream << " ";
//  stream << mf32ReferenceToAuxiliary2GPSXLeverArm;
//  stream << " ";
//  stream << mf32ReferenceToAuxiliary2GPSYLeverArm;
//  stream << " ";
//  stream << mf32ReferenceToAuxiliary2GPSZLeverArm;
//  stream << " ";
//  stream << mu16ReferenceToAuxiliary2GPSLeverArmCalibrationFOM;
//  stream << " ";
//  stream << mf32ReferenceToDMIXLeverArm;
//  stream << " ";
//  stream << mf32ReferenceToDMIYLeverArm;
//  stream << " ";
//  stream << mf32ReferenceToDMIZLeverArm;
//  stream << " ";
//  stream << mu16ReferenceToDMILeverArmCalibrationFOM;
//  stream << " ";
//  stream << mf32DMIScaleFactor;
//  stream << " ";
//  stream << mu16DMIScaleFactorCalibrationFOM;
//  stream << " ";
//  stream << mf32Reserved1;
//  stream << " ";
//  stream << mf32Reserved2;
//  stream << " ";
//  stream << mf32Reserved3;
//  stream << " ";
//  stream << mf32Reserved4;
//  stream << " ";
//  stream << mf32Reserved5;
//  stream << " ";
//  stream << mf32Reserved6;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

CalibratedInstallationParams* CalibratedInstallationParams::clone() const {
  return new CalibratedInstallationParams(*this);
}
