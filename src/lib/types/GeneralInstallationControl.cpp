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

#include "types/GeneralInstallationControl.h"

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const GeneralInstallationControl GeneralInstallationControl::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GeneralInstallationControl::GeneralInstallationControl() :
    Message(20) {
}

GeneralInstallationControl::GeneralInstallationControl(const
    GeneralInstallationControl& other) :
    Message(other),
    mTransactionNumber(other.mTransactionNumber),
    mTimeTypes(other.mTimeTypes),
    mDistanceType(other.mDistanceType),
    mAutoStart(other.mAutoStart),
    mRefIMUX(other.mRefIMUX),
    mRefIMUY(other.mRefIMUY),
    mRefIMUZ(other.mRefIMUZ),
    mRefPrimGPSX(other.mRefPrimGPSX),
    mRefPrimGPSY(other.mRefPrimGPSY),
    mRefPrimGPSZ(other.mRefPrimGPSZ),
    mRefAux1GPSX(other.mRefAux1GPSX),
    mRefAux1GPSY(other.mRefAux1GPSY),
    mRefAux1GPSZ(other.mRefAux1GPSZ),
    mRefAux2GPSX(other.mRefAux2GPSX),
    mRefAux2GPSY(other.mRefAux2GPSY),
    mRefAux2GPSZ(other.mRefAux2GPSZ),
    mXIMURefMountingAngle(other.mXIMURefMountingAngle),
    mYIMURefMountingAngle(other.mYIMURefMountingAngle),
    mZIMURefMountingAngle(other.mZIMURefMountingAngle),
    mXRefVehicleMountingAngle(other.mXRefVehicleMountingAngle),
    mYRefVehicleMountingAngle(other.mYRefVehicleMountingAngle),
    mZRefVehicleMountingAngle(other.mZRefVehicleMountingAngle),
    mMultipathEnvironment(other.mMultipathEnvironment) {
}

GeneralInstallationControl& GeneralInstallationControl::operator =
    (const GeneralInstallationControl& other) {
  if (this != &other) {
    Message::operator=(other);
    mTransactionNumber = other.mTransactionNumber;
    mTimeTypes = other.mTimeTypes;
    mDistanceType = other.mDistanceType;
    mAutoStart = other.mAutoStart;
    mRefIMUX = other.mRefIMUX;
    mRefIMUY = other.mRefIMUY;
    mRefIMUZ = other.mRefIMUZ;
    mRefPrimGPSX = other.mRefPrimGPSX;
    mRefPrimGPSY = other.mRefPrimGPSY;
    mRefPrimGPSZ = other.mRefPrimGPSZ;
    mRefAux1GPSX = other.mRefAux1GPSX;
    mRefAux1GPSY = other.mRefAux1GPSY;
    mRefAux1GPSZ = other.mRefAux1GPSZ;
    mRefAux2GPSX = other.mRefAux2GPSX;
    mRefAux2GPSY = other.mRefAux2GPSY;
    mRefAux2GPSZ = other.mRefAux2GPSZ;
    mXIMURefMountingAngle = other.mXIMURefMountingAngle;
    mYIMURefMountingAngle = other.mYIMURefMountingAngle;
    mZIMURefMountingAngle = other.mZIMURefMountingAngle;
    mXRefVehicleMountingAngle = other.mXRefVehicleMountingAngle;
    mYRefVehicleMountingAngle = other.mYRefVehicleMountingAngle;
    mZRefVehicleMountingAngle = other.mZRefVehicleMountingAngle;
    mMultipathEnvironment = other.mMultipathEnvironment;
  }
  return *this;
}

GeneralInstallationControl::~GeneralInstallationControl() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GeneralInstallationControl::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("GeneralInstallationControl::read(): wrong byte count");
  stream >> mTransactionNumber;
  stream >> mTimeTypes;
  stream >> mDistanceType;
  stream >> mAutoStart;
  stream >> mRefIMUX;
  stream >> mRefIMUY;
  stream >> mRefIMUZ;
  stream >> mRefPrimGPSX;
  stream >> mRefPrimGPSY;
  stream >> mRefPrimGPSZ;
  stream >> mRefAux1GPSX;
  stream >> mRefAux1GPSY;
  stream >> mRefAux1GPSZ;
  stream >> mRefAux2GPSX;
  stream >> mRefAux2GPSY;
  stream >> mRefAux2GPSZ;
  stream >> mXIMURefMountingAngle;
  stream >> mYIMURefMountingAngle;
  stream >> mZIMURefMountingAngle;
  stream >> mXRefVehicleMountingAngle;
  stream >> mYRefVehicleMountingAngle;
  stream >> mZRefVehicleMountingAngle;
  stream >> mMultipathEnvironment;
}

void GeneralInstallationControl::write(BinaryWriter& stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTransactionNumber;
  stream << mTimeTypes;
  stream << mDistanceType;
  stream << mAutoStart;
  stream << mRefIMUX;
  stream << mRefIMUY;
  stream << mRefIMUZ;
  stream << mRefPrimGPSX;
  stream << mRefPrimGPSY;
  stream << mRefPrimGPSZ;
  stream << mRefAux1GPSX;
  stream << mRefAux1GPSY;
  stream << mRefAux1GPSZ;
  stream << mRefAux2GPSX;
  stream << mRefAux2GPSY;
  stream << mRefAux2GPSZ;
  stream << mXIMURefMountingAngle;
  stream << mYIMURefMountingAngle;
  stream << mZIMURefMountingAngle;
  stream << mXRefVehicleMountingAngle;
  stream << mYRefVehicleMountingAngle;
  stream << mZRefVehicleMountingAngle;
  stream << mMultipathEnvironment;
}

void GeneralInstallationControl::read(std::istream& stream) {
}

void GeneralInstallationControl::write(std::ostream& stream) const {
}

void GeneralInstallationControl::read(std::ifstream& stream) {
}

void GeneralInstallationControl::write(std::ofstream& stream) const {
  stream << mTypeID;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

GeneralInstallationControl* GeneralInstallationControl::clone() const {
  return new GeneralInstallationControl(*this);
}
