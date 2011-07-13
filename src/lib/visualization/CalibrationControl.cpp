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

#include <bitset>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

CalibrationControl::CalibrationControl() :
  mpUi(new Ui_CalibrationControl()) {
  mpUi->setupUi(this);

  connect(&ReadThread::getInstance(), SIGNAL(groupRead(const Group*)), this,
    SLOT(groupRead(const Group*)));

  mpUi->primGPSProgressLed->setColor(Qt::red);
  mpUi->dmiLeverProgressLed->setColor(Qt::red);
  mpUi->dmiScaleProgressLed->setColor(Qt::red);
  mpUi->fixLeverProgressLed->setColor(Qt::red);
  mpUi->primGPSCompleteLed->setColor(Qt::red);
  mpUi->dmiLeverCompleteLed->setColor(Qt::red);
  mpUi->dmiScaleCompleteLed->setColor(Qt::red);
  mpUi->fixLeverCompleteLed->setColor(Qt::red);
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

    std::bitset<16> status(msg.mCalibrationStatus);
    for (size_t i = 0; i < 16; i++) {
      switch (i) {
        case 0:
          if (status.test(i))
            mpUi->primGPSProgressLed->setColor(Qt::green);
          else
            mpUi->primGPSProgressLed->setColor(Qt::red);
          break;
        case 3:
          if (status.test(i))
            mpUi->dmiLeverProgressLed->setColor(Qt::green);
          else
            mpUi->dmiLeverProgressLed->setColor(Qt::red);
          break;
        case 4:
          if (status.test(i))
            mpUi->dmiScaleProgressLed->setColor(Qt::green);
          else
            mpUi->dmiScaleProgressLed->setColor(Qt::red);
          break;
        case 6:
          if (status.test(i))
            mpUi->fixLeverProgressLed->setColor(Qt::green);
          else
            mpUi->fixLeverProgressLed->setColor(Qt::red);
          break;
        case 8:
          if (status.test(i))
            mpUi->primGPSCompleteLed->setColor(Qt::green);
          else
            mpUi->primGPSCompleteLed->setColor(Qt::red);
          break;
        case 11:
          if (status.test(i))
            mpUi->dmiLeverCompleteLed->setColor(Qt::green);
          else
            mpUi->dmiLeverCompleteLed->setColor(Qt::red);
          break;
        case 12:
          if (status.test(i))
            mpUi->dmiScaleCompleteLed->setColor(Qt::green);
          else
            mpUi->dmiScaleCompleteLed->setColor(Qt::red);
          break;
        case 14:
          if (status.test(i))
            mpUi->fixLeverCompleteLed->setColor(Qt::green);
          else
            mpUi->fixLeverCompleteLed->setColor(Qt::red);
          break;
        default:
          break;
      }
    }
  }
}
