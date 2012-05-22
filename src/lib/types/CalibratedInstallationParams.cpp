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

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

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
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mCalibrationStatus(other.mCalibrationStatus),
    mReferenceToPrimaryGPSXLeverArm(other.mReferenceToPrimaryGPSXLeverArm),
    mReferenceToPrimaryGPSYLeverArm(other.mReferenceToPrimaryGPSYLeverArm),
    mReferenceToPrimaryGPSZLeverArm(other.mReferenceToPrimaryGPSZLeverArm),
    mReferenceToPrimaryGPSLeverArmCalibrationFOM(
      other.mReferenceToPrimaryGPSLeverArmCalibrationFOM),
    mReferenceToAuxiliary1GPSXLeverArm(
      other.mReferenceToAuxiliary1GPSXLeverArm),
    mReferenceToAuxiliary1GPSYLeverArm(
      other.mReferenceToAuxiliary1GPSYLeverArm),
    mReferenceToAuxiliary1GPSZLeverArm(
      other.mReferenceToAuxiliary1GPSZLeverArm),
    mReferenceToAuxiliary1GPSLeverArmCalibrationFOM(
      other.mReferenceToAuxiliary1GPSLeverArmCalibrationFOM),
    mReferenceToAuxiliary2GPSXLeverArm(
      other.mReferenceToAuxiliary2GPSXLeverArm),
    mReferenceToAuxiliary2GPSYLeverArm(
      other.mReferenceToAuxiliary2GPSYLeverArm),
    mReferenceToAuxiliary2GPSZLeverArm(
      other.mReferenceToAuxiliary2GPSZLeverArm),
    mReferenceToAuxiliary2GPSLeverArmCalibrationFOM(
      other.mReferenceToAuxiliary2GPSLeverArmCalibrationFOM),
    mReferenceToDMIXLeverArm(other.mReferenceToDMIXLeverArm),
    mReferenceToDMIYLeverArm(other.mReferenceToDMIYLeverArm),
    mReferenceToDMIZLeverArm(other.mReferenceToDMIZLeverArm),
    mReferenceToDMILeverArmCalibrationFOM(
      other.mReferenceToDMILeverArmCalibrationFOM),
    mDMIScaleFactor(other.mDMIScaleFactor),
    mDMIScaleFactorCalibrationFOM(other.mDMIScaleFactorCalibrationFOM),
    mReserved1(other.mReserved1),
    mReserved2(other.mReserved2),
    mReserved3(other.mReserved3),
    mReserved4(other.mReserved4),
    mReserved5(other.mReserved5),
    mReserved6(other.mReserved6) {
}

CalibratedInstallationParams& CalibratedInstallationParams::operator =
    (const CalibratedInstallationParams& other) {
  Group::operator=(other);
  mTimeDistance = other.mTimeDistance;
  mCalibrationStatus = other.mCalibrationStatus;
  mReferenceToPrimaryGPSXLeverArm = other.mReferenceToPrimaryGPSXLeverArm;
  mReferenceToPrimaryGPSYLeverArm = other.mReferenceToPrimaryGPSYLeverArm;
  mReferenceToPrimaryGPSZLeverArm = other.mReferenceToPrimaryGPSZLeverArm;
  mReferenceToPrimaryGPSLeverArmCalibrationFOM =
    other.mReferenceToPrimaryGPSLeverArmCalibrationFOM;
  mReferenceToAuxiliary1GPSXLeverArm = other.mReferenceToAuxiliary1GPSXLeverArm;
  mReferenceToAuxiliary1GPSYLeverArm = other.mReferenceToAuxiliary1GPSYLeverArm;
  mReferenceToAuxiliary1GPSZLeverArm = other.mReferenceToAuxiliary1GPSZLeverArm;
  mReferenceToAuxiliary1GPSLeverArmCalibrationFOM =
    other.mReferenceToAuxiliary1GPSLeverArmCalibrationFOM;
  mReferenceToAuxiliary2GPSXLeverArm = other.mReferenceToAuxiliary2GPSXLeverArm;
  mReferenceToAuxiliary2GPSYLeverArm = other.mReferenceToAuxiliary2GPSYLeverArm;
  mReferenceToAuxiliary2GPSZLeverArm = other.mReferenceToAuxiliary2GPSZLeverArm;
  mReferenceToAuxiliary2GPSLeverArmCalibrationFOM =
    other.mReferenceToAuxiliary2GPSLeverArmCalibrationFOM;
  mReferenceToDMIXLeverArm = other.mReferenceToDMIXLeverArm;
  mReferenceToDMIYLeverArm = other.mReferenceToDMIYLeverArm;
  mReferenceToDMIZLeverArm = other.mReferenceToDMIZLeverArm;
  mReferenceToDMILeverArmCalibrationFOM =
    other.mReferenceToDMILeverArmCalibrationFOM;
  mDMIScaleFactor = other.mDMIScaleFactor;
  mDMIScaleFactorCalibrationFOM = other.mDMIScaleFactorCalibrationFOM;
  mReserved1 = other.mReserved1;
  mReserved2 = other.mReserved2;
  mReserved3 = other.mReserved3;
  mReserved4 = other.mReserved4;
  mReserved5 = other.mReserved5;
  mReserved6 = other.mReserved6;
  return *this;
}

CalibratedInstallationParams::~CalibratedInstallationParams() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void CalibratedInstallationParams::read(BinaryReader& stream) {
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
}

void CalibratedInstallationParams::read(std::istream& stream) {
}

void CalibratedInstallationParams::write(std::ostream& stream) const {
}

void CalibratedInstallationParams::read(std::ifstream& stream) {
}

void CalibratedInstallationParams::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mCalibrationStatus;
  stream << " ";
  stream << mReferenceToPrimaryGPSXLeverArm;
  stream << " ";
  stream << mReferenceToPrimaryGPSYLeverArm;
  stream << " ";
  stream << mReferenceToPrimaryGPSZLeverArm;
  stream << " ";
  stream << mReferenceToPrimaryGPSLeverArmCalibrationFOM;
  stream << " ";
  stream << mReferenceToAuxiliary1GPSXLeverArm;
  stream << " ";
  stream << mReferenceToAuxiliary1GPSYLeverArm;
  stream << " ";
  stream << mReferenceToAuxiliary1GPSZLeverArm;
  stream << " ";
  stream << mReferenceToAuxiliary1GPSLeverArmCalibrationFOM;
  stream << " ";
  stream << mReferenceToAuxiliary2GPSXLeverArm;
  stream << " ";
  stream << mReferenceToAuxiliary2GPSYLeverArm;
  stream << " ";
  stream << mReferenceToAuxiliary2GPSZLeverArm;
  stream << " ";
  stream << mReferenceToAuxiliary2GPSLeverArmCalibrationFOM;
  stream << " ";
  stream << mReferenceToDMIXLeverArm;
  stream << " ";
  stream << mReferenceToDMIYLeverArm;
  stream << " ";
  stream << mReferenceToDMIZLeverArm;
  stream << " ";
  stream << mReferenceToDMILeverArmCalibrationFOM;
  stream << " ";
  stream << mDMIScaleFactor;
  stream << " ";
  stream << mDMIScaleFactorCalibrationFOM;
  stream << " ";
  stream << mReserved1;
  stream << " ";
  stream << mReserved2;
  stream << " ";
  stream << mReserved3;
  stream << " ";
  stream << mReserved4;
  stream << " ";
  stream << mReserved5;
  stream << " ";
  stream << mReserved6;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

CalibratedInstallationParams* CalibratedInstallationParams::clone() const {
  return new CalibratedInstallationParams(*this);
}
