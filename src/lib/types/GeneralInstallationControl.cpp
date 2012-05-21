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
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("GeneralInstallationControl::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTransactionNumber;
  mChecksum += mTransactionNumber;
  stream >> mTimeTypes;
  stream >> mDistanceType;
  mChecksum += (mDistanceType << 8) | mTimeTypes;
  stream >> mAutoStart;
  stream >> mRefIMUX;
  mChecksum += (((uint8_t*)&mRefIMUX)[0] << 8) | mAutoStart;
  mChecksum += (((uint8_t*)&mRefIMUX)[2] << 8) | ((uint8_t*)&mRefIMUX)[1];
  stream >> mRefIMUY;
  mChecksum += (((uint8_t*)&mRefIMUY)[0] << 8) | ((uint8_t*)&mRefIMUX)[3];
  mChecksum += (((uint8_t*)&mRefIMUY)[2] << 8) | ((uint8_t*)&mRefIMUY)[1];
  stream >> mRefIMUZ;
  mChecksum += (((uint8_t*)&mRefIMUZ)[0] << 8) | ((uint8_t*)&mRefIMUY)[3];
  mChecksum += (((uint8_t*)&mRefIMUZ)[2] << 8) | ((uint8_t*)&mRefIMUZ)[1];
  stream >> mRefPrimGPSX;
  mChecksum += (((uint8_t*)&mRefPrimGPSX)[0] << 8) | ((uint8_t*)&mRefIMUZ)[3];
  mChecksum += (((uint8_t*)&mRefPrimGPSX)[2] << 8) |
    ((uint8_t*)&mRefPrimGPSX)[1];
  stream >> mRefPrimGPSY;
  mChecksum += (((uint8_t*)&mRefPrimGPSY)[0] << 8) |
    ((uint8_t*)&mRefPrimGPSX)[3];
  mChecksum += (((uint8_t*)&mRefPrimGPSY)[2] << 8) |
    ((uint8_t*)&mRefPrimGPSY)[1];
  stream >> mRefPrimGPSZ;
  mChecksum += (((uint8_t*)&mRefPrimGPSZ)[0] << 8) |
    ((uint8_t*)&mRefPrimGPSY)[3];
  mChecksum += (((uint8_t*)&mRefPrimGPSZ)[2] << 8) |
    ((uint8_t*)&mRefPrimGPSZ)[1];
  stream >> mRefAux1GPSX;
  mChecksum += (((uint8_t*)&mRefAux1GPSX)[0] << 8) |
    ((uint8_t*)&mRefPrimGPSZ)[3];
  mChecksum += (((uint8_t*)&mRefAux1GPSX)[2] << 8) |
    ((uint8_t*)&mRefAux1GPSX)[1];
  stream >> mRefAux1GPSY;
  mChecksum += (((uint8_t*)&mRefAux1GPSY)[0] << 8) |
    ((uint8_t*)&mRefAux1GPSX)[3];
  mChecksum += (((uint8_t*)&mRefAux1GPSY)[2] << 8) |
    ((uint8_t*)&mRefAux1GPSY)[1];
  stream >> mRefAux1GPSZ;
  mChecksum += (((uint8_t*)&mRefAux1GPSZ)[0] << 8) |
    ((uint8_t*)&mRefAux1GPSY)[3];
  mChecksum += (((uint8_t*)&mRefAux1GPSZ)[2] << 8) |
    ((uint8_t*)&mRefAux1GPSZ)[1];
  stream >> mRefAux2GPSX;
  mChecksum += (((uint8_t*)&mRefAux2GPSX)[0] << 8) |
    ((uint8_t*)&mRefAux1GPSZ)[3];
  mChecksum += (((uint8_t*)&mRefAux2GPSX)[2] << 8) |
    ((uint8_t*)&mRefAux2GPSX)[1];
  stream >> mRefAux2GPSY;
  mChecksum += (((uint8_t*)&mRefAux2GPSY)[0] << 8) |
    ((uint8_t*)&mRefAux2GPSX)[3];
  mChecksum += (((uint8_t*)&mRefAux2GPSY)[2] << 8) |
    ((uint8_t*)&mRefAux2GPSY)[1];
  stream >> mRefAux2GPSZ;
  mChecksum += (((uint8_t*)&mRefAux2GPSZ)[0] << 8) |
    ((uint8_t*)&mRefAux2GPSY)[3];
  mChecksum += (((uint8_t*)&mRefAux2GPSZ)[2] << 8) |
    ((uint8_t*)&mRefAux2GPSZ)[1];
  stream >> mXIMURefMountingAngle;
  mChecksum += (((uint8_t*)&mXIMURefMountingAngle)[0] << 8) |
    ((uint8_t*)&mRefAux2GPSZ)[3];
  mChecksum += (((uint8_t*)&mXIMURefMountingAngle)[2] << 8) |
    ((uint8_t*)&mXIMURefMountingAngle)[1];
  stream >> mYIMURefMountingAngle;
  mChecksum += (((uint8_t*)&mYIMURefMountingAngle)[0] << 8) |
    ((uint8_t*)&mXIMURefMountingAngle)[3];
  mChecksum += (((uint8_t*)&mYIMURefMountingAngle)[2] << 8) |
    ((uint8_t*)&mYIMURefMountingAngle)[1];
  stream >> mZIMURefMountingAngle;
  mChecksum += (((uint8_t*)&mZIMURefMountingAngle)[0] << 8) |
    ((uint8_t*)&mYIMURefMountingAngle)[3];
  mChecksum += (((uint8_t*)&mZIMURefMountingAngle)[2] << 8) |
    ((uint8_t*)&mZIMURefMountingAngle)[1];
  stream >> mXRefVehicleMountingAngle;
  mChecksum += (((uint8_t*)&mXRefVehicleMountingAngle)[0] << 8) |
    ((uint8_t*)&mZIMURefMountingAngle)[3];
  mChecksum += (((uint8_t*)&mXRefVehicleMountingAngle)[2] << 8) |
    ((uint8_t*)&mXRefVehicleMountingAngle)[1];
  stream >> mYRefVehicleMountingAngle;
  mChecksum += (((uint8_t*)&mYRefVehicleMountingAngle)[0] << 8) |
    ((uint8_t*)&mXRefVehicleMountingAngle)[3];
  mChecksum += (((uint8_t*)&mYRefVehicleMountingAngle)[2] << 8) |
    ((uint8_t*)&mYRefVehicleMountingAngle)[1];
  stream >> mZRefVehicleMountingAngle;
  mChecksum += (((uint8_t*)&mZRefVehicleMountingAngle)[0] << 8) |
    ((uint8_t*)&mYRefVehicleMountingAngle)[3];
  mChecksum += (((uint8_t*)&mZRefVehicleMountingAngle)[2] << 8) |
    ((uint8_t*)&mZRefVehicleMountingAngle)[1];
  stream >> mMultipathEnvironment;
  mChecksum += (mMultipathEnvironment << 8) |
    ((uint8_t*)&mZRefVehicleMountingAngle)[3];
  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("GeneralInstallationControl::read(): wrong pad");
  mChecksum += pad;
  mChecksum = 65536 - mChecksum;
}

void GeneralInstallationControl::write(BinaryWriter& stream) const {
  uint16_t checksum = mChecksum;
  stream << mTypeID;
  checksum += mTypeID;
  stream << mByteCount;
  checksum += mByteCount;
  stream << mTransactionNumber;
  checksum += mTransactionNumber;
  stream << mTimeTypes;
  stream << mDistanceType;
  checksum += (mDistanceType << 8) | mTimeTypes;
  stream << mAutoStart;
  stream << mRefIMUX;
  checksum += (((uint8_t*)&mRefIMUX)[0] << 8) | mAutoStart;
  checksum += (((uint8_t*)&mRefIMUX)[2] << 8) | ((uint8_t*)&mRefIMUX)[1];
  stream << mRefIMUY;
  checksum += (((uint8_t*)&mRefIMUY)[0] << 8) | ((uint8_t*)&mRefIMUX)[3];
  checksum += (((uint8_t*)&mRefIMUY)[2] << 8) | ((uint8_t*)&mRefIMUY)[1];
  stream << mRefIMUZ;
  checksum += (((uint8_t*)&mRefIMUZ)[0] << 8) | ((uint8_t*)&mRefIMUY)[3];
  checksum += (((uint8_t*)&mRefIMUZ)[2] << 8) | ((uint8_t*)&mRefIMUZ)[1];
  stream << mRefPrimGPSX;
  checksum += (((uint8_t*)&mRefPrimGPSX)[0] << 8) | ((uint8_t*)&mRefIMUZ)[3];
  checksum += (((uint8_t*)&mRefPrimGPSX)[2] << 8) |
    ((uint8_t*)&mRefPrimGPSX)[1];
  stream << mRefPrimGPSY;
  checksum += (((uint8_t*)&mRefPrimGPSY)[0] << 8) |
    ((uint8_t*)&mRefPrimGPSX)[3];
  checksum += (((uint8_t*)&mRefPrimGPSY)[2] << 8) |
    ((uint8_t*)&mRefPrimGPSY)[1];
  stream << mRefPrimGPSZ;
  checksum += (((uint8_t*)&mRefPrimGPSZ)[0] << 8) |
    ((uint8_t*)&mRefPrimGPSY)[3];
  checksum += (((uint8_t*)&mRefPrimGPSZ)[2] << 8) |
    ((uint8_t*)&mRefPrimGPSZ)[1];
  stream << mRefAux1GPSX;
  checksum += (((uint8_t*)&mRefAux1GPSX)[0] << 8) |
    ((uint8_t*)&mRefPrimGPSZ)[3];
  checksum += (((uint8_t*)&mRefAux1GPSX)[2] << 8) |
    ((uint8_t*)&mRefAux1GPSX)[1];
  stream << mRefAux1GPSY;
  checksum += (((uint8_t*)&mRefAux1GPSY)[0] << 8) |
    ((uint8_t*)&mRefAux1GPSX)[3];
  checksum += (((uint8_t*)&mRefAux1GPSY)[2] << 8) |
    ((uint8_t*)&mRefAux1GPSY)[1];
  stream << mRefAux1GPSZ;
  checksum += (((uint8_t*)&mRefAux1GPSZ)[0] << 8) |
    ((uint8_t*)&mRefAux1GPSY)[3];
  checksum += (((uint8_t*)&mRefAux1GPSZ)[2] << 8) |
    ((uint8_t*)&mRefAux1GPSZ)[1];
  stream << mRefAux2GPSX;
  checksum += (((uint8_t*)&mRefAux2GPSX)[0] << 8) |
    ((uint8_t*)&mRefAux1GPSZ)[3];
  checksum += (((uint8_t*)&mRefAux2GPSX)[2] << 8) |
    ((uint8_t*)&mRefAux2GPSX)[1];
  stream << mRefAux2GPSY;
  checksum += (((uint8_t*)&mRefAux2GPSY)[0] << 8) |
    ((uint8_t*)&mRefAux2GPSX)[3];
  checksum += (((uint8_t*)&mRefAux2GPSY)[2] << 8) |
    ((uint8_t*)&mRefAux2GPSY)[1];
  stream << mRefAux2GPSZ;
  checksum += (((uint8_t*)&mRefAux2GPSZ)[0] << 8) |
    ((uint8_t*)&mRefAux2GPSY)[3];
  checksum += (((uint8_t*)&mRefAux2GPSZ)[2] << 8) |
    ((uint8_t*)&mRefAux2GPSZ)[1];
  stream << mXIMURefMountingAngle;
  checksum += (((uint8_t*)&mXIMURefMountingAngle)[0] << 8) |
    ((uint8_t*)&mRefAux2GPSZ)[3];
  checksum += (((uint8_t*)&mXIMURefMountingAngle)[2] << 8) |
    ((uint8_t*)&mXIMURefMountingAngle)[1];
  stream << mYIMURefMountingAngle;
  checksum += (((uint8_t*)&mYIMURefMountingAngle)[0] << 8) |
    ((uint8_t*)&mXIMURefMountingAngle)[3];
  checksum += (((uint8_t*)&mYIMURefMountingAngle)[2] << 8) |
    ((uint8_t*)&mYIMURefMountingAngle)[1];
  stream << mZIMURefMountingAngle;
  checksum += (((uint8_t*)&mZIMURefMountingAngle)[0] << 8) |
    ((uint8_t*)&mYIMURefMountingAngle)[3];
  checksum += (((uint8_t*)&mZIMURefMountingAngle)[2] << 8) |
    ((uint8_t*)&mZIMURefMountingAngle)[1];
  stream << mXRefVehicleMountingAngle;
  checksum += (((uint8_t*)&mXRefVehicleMountingAngle)[0] << 8) |
    ((uint8_t*)&mZIMURefMountingAngle)[3];
  checksum += (((uint8_t*)&mXRefVehicleMountingAngle)[2] << 8) |
    ((uint8_t*)&mXRefVehicleMountingAngle)[1];
  stream << mYRefVehicleMountingAngle;
  checksum += (((uint8_t*)&mYRefVehicleMountingAngle)[0] << 8) |
    ((uint8_t*)&mXRefVehicleMountingAngle)[3];
  checksum += (((uint8_t*)&mYRefVehicleMountingAngle)[2] << 8) |
    ((uint8_t*)&mYRefVehicleMountingAngle)[1];
  stream << mZRefVehicleMountingAngle;
  checksum += (((uint8_t*)&mZRefVehicleMountingAngle)[0] << 8) |
    ((uint8_t*)&mYRefVehicleMountingAngle)[3];
  checksum += (((uint8_t*)&mZRefVehicleMountingAngle)[2] << 8) |
    ((uint8_t*)&mZRefVehicleMountingAngle)[1];
  stream << mMultipathEnvironment;
  checksum += (mMultipathEnvironment << 8) |
    ((uint8_t*)&mZRefVehicleMountingAngle)[3];
  uint16_t pad = 0;
  stream << pad;
  checksum += pad;
  checksum = 65536 - checksum;
  stream << checksum;
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
