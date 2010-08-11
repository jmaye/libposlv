#include "CalibratedInstallationParams.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const CalibratedInstallationParams CalibratedInstallationParams::mProto;

CalibratedInstallationParams::CalibratedInstallationParams() : Group(14) {
}

CalibratedInstallationParams::
  CalibratedInstallationParams(const CalibratedInstallationParams &other)
  : Group(other) {
}

CalibratedInstallationParams::~CalibratedInstallationParams() {
}

void CalibratedInstallationParams::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("CalibratedInstallationParams::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mu16CalibrationStatus;
  stream >> mf32ReferenceToPrimaryGPSXLeverArm;
  stream >> mf32ReferenceToPrimaryGPSYLeverArm;
  stream >> mf32ReferenceToPrimaryGPSZLeverArm;
  stream >> mu16ReferenceToPrimaryGPSLeverArmCalibrationFOM;
  stream >> mf32ReferenceToAuxiliary1GPSXLeverArm;
  stream >> mf32ReferenceToAuxiliary1GPSYLeverArm;
  stream >> mf32ReferenceToAuxiliary1GPSZLeverArm;
  stream >> mu16ReferenceToAuxiliary1GPSLeverArmCalibrationFOM;
  stream >> mf32ReferenceToAuxiliary2GPSXLeverArm;
  stream >> mf32ReferenceToAuxiliary2GPSYLeverArm;
  stream >> mf32ReferenceToAuxiliary2GPSZLeverArm;
  stream >> mu16ReferenceToAuxiliary2GPSLeverArmCalibrationFOM;
  stream >> mf32ReferenceToDMIXLeverArm;
  stream >> mf32ReferenceToDMIYLeverArm;
  stream >> mf32ReferenceToDMIZLeverArm;
  stream >> mu16ReferenceToDMILeverArmCalibrationFOM;
  stream >> mf32DMIScaleFactor;
  stream >> mu16DMIScaleFactorCalibrationFOM;
  stream >> mf32Reserved1;
  stream >> mf32Reserved2;
  stream >> mf32Reserved3;
  stream >> mf32Reserved4;
  stream >> mf32Reserved5;
  stream >> mf32Reserved6;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("CalibratedInstallationParams::read: Wrong pad");
}

void CalibratedInstallationParams::write(ofstream &stream) const {
}

CalibratedInstallationParams* CalibratedInstallationParams::clone() const {
  return new CalibratedInstallationParams(*this);
}
