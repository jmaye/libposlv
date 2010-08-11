#ifndef CALIBRATEDINSTALLATIONPARAMS_H
#define CALIBRATEDINSTALLATIONPARAMS_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class CalibratedInstallationParams : public Group {
  CalibratedInstallationParams();
  CalibratedInstallationParams(const CalibratedInstallationParams &other);
  CalibratedInstallationParams&
    operator = (const CalibratedInstallationParams &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 116;

  TimeDistance mTimeDistance;
  uint16_t mu16CalibrationStatus;
  float mf32ReferenceToPrimaryGPSXLeverArm;
  float mf32ReferenceToPrimaryGPSYLeverArm;
  float mf32ReferenceToPrimaryGPSZLeverArm;
  uint16_t mu16ReferenceToPrimaryGPSLeverArmCalibrationFOM;
  float mf32ReferenceToAuxiliary1GPSXLeverArm;
  float mf32ReferenceToAuxiliary1GPSYLeverArm;
  float mf32ReferenceToAuxiliary1GPSZLeverArm;
  uint16_t mu16ReferenceToAuxiliary1GPSLeverArmCalibrationFOM;
  float mf32ReferenceToAuxiliary2GPSXLeverArm;
  float mf32ReferenceToAuxiliary2GPSYLeverArm;
  float mf32ReferenceToAuxiliary2GPSZLeverArm;
  uint16_t mu16ReferenceToAuxiliary2GPSLeverArmCalibrationFOM;
  float mf32ReferenceToDMIXLeverArm;
  float mf32ReferenceToDMIYLeverArm;
  float mf32ReferenceToDMIZLeverArm;
  uint16_t mu16ReferenceToDMILeverArmCalibrationFOM;
  float mf32DMIScaleFactor;
  uint16_t mu16DMIScaleFactorCalibrationFOM;
  float mf32Reserved1;
  float mf32Reserved2;
  float mf32Reserved3;
  float mf32Reserved4;
  float mf32Reserved5;
  float mf32Reserved6;

public:
  ~CalibratedInstallationParams();

  virtual CalibratedInstallationParams* clone() const;

  static const CalibratedInstallationParams mProto;

protected:
};

#endif // CALIBRATEDINSTALLATIONPARAMS_H
