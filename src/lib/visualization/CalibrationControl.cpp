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

#include "visualization/CalibrationControl.h"

#include "visualization/ReadThread.h"
#include "types/CalibratedInstallationParams.h"
#include "ui_CalibrationControl.h"

#include <sstream>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

CalibrationControl::CalibrationControl() :
  mpUi(new Ui_CalibrationControl()) {
  mpUi->setupUi(this);

  connect(&ReadThread::getInstance(), SIGNAL(groupRead(const Group*)), this,
    SLOT(groupRead(const Group*)));

  mStatusMsg[0] = "Reference to Primary GPS lever arm calibration in progress";
  mStatusMsg[1] = "Reference to Auxiliary 1 GPS lever arm calibration in progress";
  mStatusMsg[2] = "Reference to Auxiliary 2 GPS lever arm calibration in progress";
  mStatusMsg[3] = "Reference to DMI lever arm calibration in progress";
  mStatusMsg[4] = "DMI scale factor calibration in progress";
  mStatusMsg[5] = "Reserved";
  mStatusMsg[6] = "Reference to Position Fix lever arm calibration in progress";
  mStatusMsg[7] = "Reserved";
  mStatusMsg[8] = "Reference to Primary GPS lever arm calibration completed";
  mStatusMsg[9] = "Reference to Auxiliary 1 GPS lever arm calibration completed";
  mStatusMsg[10] = "Reference to Auxiliary 2 GPS lever arm calibration completed";
  mStatusMsg[11] = "Reference to DMI lever arm calibration completed";
  mStatusMsg[12] = "DMI scale factor calibration completed";
  mStatusMsg[13] = "Reserved";
  mStatusMsg[14] = "Reference to Position Fix lever arm calibration completed";
  mStatusMsg[15] = "Reserved";
}

CalibrationControl::~CalibrationControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void CalibrationControl::groupRead(const Group* group) {
  if (group->instanceOf<CalibratedInstallationParams>() == true) {
    const CalibratedInstallationParams& msg =
      group->typeCast<CalibratedInstallationParams>();
    std::stringstream status;
    for (size_t i = 0; i <= 15; i++)
      if ((msg.mCalibrationStatus >> i) & 0x0001)
        status << mStatusMsg[i] << std::endl;
    mpUi->statusText->setText(status.str().c_str());
    mpUi->primGPSXSpinBox->setValue(msg.mReferenceToPrimaryGPSXLeverArm);
    mpUi->primGPSYSpinBox->setValue(msg.mReferenceToPrimaryGPSYLeverArm);
    mpUi->primGPSZSpinBox->setValue(msg.mReferenceToPrimaryGPSZLeverArm);
    mpUi->primGPSFOMSpinBox->setValue(
      msg.mReferenceToPrimaryGPSLeverArmCalibrationFOM);
    mpUi->aux1GPSXSpinBox->setValue(msg.mReferenceToAuxiliary1GPSXLeverArm);
    mpUi->aux1GPSYSpinBox->setValue(msg.mReferenceToAuxiliary1GPSYLeverArm);
    mpUi->aux1GPSZSpinBox->setValue(msg.mReferenceToAuxiliary1GPSZLeverArm);
    mpUi->aux1GPSFOMSpinBox->setValue(
      msg.mReferenceToAuxiliary1GPSLeverArmCalibrationFOM);
    mpUi->aux2GPSXSpinBox->setValue(msg.mReferenceToAuxiliary2GPSXLeverArm);
    mpUi->aux2GPSYSpinBox->setValue(msg.mReferenceToAuxiliary2GPSYLeverArm);
    mpUi->aux2GPSZSpinBox->setValue(msg.mReferenceToAuxiliary2GPSZLeverArm);
    mpUi->aux2GPSFOMSpinBox->setValue(
      msg.mReferenceToAuxiliary2GPSLeverArmCalibrationFOM);
    mpUi->dmiXSpinBox->setValue(msg.mReferenceToDMIXLeverArm);
    mpUi->dmiYSpinBox->setValue(msg.mReferenceToDMIYLeverArm);
    mpUi->dmiZSpinBox->setValue(msg.mReferenceToDMIZLeverArm);
    mpUi->dmiFOMSpinBox->setValue(msg.mReferenceToDMILeverArmCalibrationFOM);
    mpUi->dmiScaleSpinBox->setValue(msg.mDMIScaleFactor);
    mpUi->dmiScaleFOMSpinBox->setValue(msg.mDMIScaleFactorCalibrationFOM);
  }
}
