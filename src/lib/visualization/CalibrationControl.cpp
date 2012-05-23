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

#include <bitset>

#include "types/CalibratedInstallationParams.h"
#include "types/Group.h"
#include "types/Packet.h"

#include "ui_CalibrationControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

CalibrationControl::CalibrationControl() :
    mUi(new Ui_CalibrationControl()) {
  mUi->setupUi(this);
  mUi->primGPSProgressLed->setColor(Qt::red);
  mUi->dmiLeverProgressLed->setColor(Qt::red);
  mUi->dmiScaleProgressLed->setColor(Qt::red);
  mUi->fixLeverProgressLed->setColor(Qt::red);
  mUi->primGPSCompleteLed->setColor(Qt::red);
  mUi->dmiLeverCompleteLed->setColor(Qt::red);
  mUi->dmiScaleCompleteLed->setColor(Qt::red);
  mUi->fixLeverCompleteLed->setColor(Qt::red);
}

CalibrationControl::~CalibrationControl() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void CalibrationControl::packetRead(boost::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<CalibratedInstallationParams>()) {
      const CalibratedInstallationParams& msg =
        group.typeCast<CalibratedInstallationParams>();
      mUi->primGPSXSpinBox->setValue(msg.mReferenceToPrimaryGPSXLeverArm);
      mUi->primGPSYSpinBox->setValue(msg.mReferenceToPrimaryGPSYLeverArm);
      mUi->primGPSZSpinBox->setValue(msg.mReferenceToPrimaryGPSZLeverArm);
      mUi->primGPSFOMSpinBox->setValue(
        msg.mReferenceToPrimaryGPSLeverArmCalibrationFOM);
      mUi->aux1GPSXSpinBox->setValue(msg.mReferenceToAuxiliary1GPSXLeverArm);
      mUi->aux1GPSYSpinBox->setValue(msg.mReferenceToAuxiliary1GPSYLeverArm);
      mUi->aux1GPSZSpinBox->setValue(msg.mReferenceToAuxiliary1GPSZLeverArm);
      mUi->aux1GPSFOMSpinBox->setValue(
        msg.mReferenceToAuxiliary1GPSLeverArmCalibrationFOM);
      mUi->aux2GPSXSpinBox->setValue(msg.mReferenceToAuxiliary2GPSXLeverArm);
      mUi->aux2GPSYSpinBox->setValue(msg.mReferenceToAuxiliary2GPSYLeverArm);
      mUi->aux2GPSZSpinBox->setValue(msg.mReferenceToAuxiliary2GPSZLeverArm);
      mUi->aux2GPSFOMSpinBox->setValue(
        msg.mReferenceToAuxiliary2GPSLeverArmCalibrationFOM);
      mUi->dmiXSpinBox->setValue(msg.mReferenceToDMIXLeverArm);
      mUi->dmiYSpinBox->setValue(msg.mReferenceToDMIYLeverArm);
      mUi->dmiZSpinBox->setValue(msg.mReferenceToDMIZLeverArm);
      mUi->dmiFOMSpinBox->setValue(msg.mReferenceToDMILeverArmCalibrationFOM);
      mUi->dmiScaleSpinBox->setValue(msg.mDMIScaleFactor);
      mUi->dmiScaleFOMSpinBox->setValue(msg.mDMIScaleFactorCalibrationFOM);
      std::bitset<16> status(msg.mCalibrationStatus);
      for (size_t i = 0; i < 16; i++) {
        switch (i) {
          case 0:
            if (status.test(i))
              mUi->primGPSProgressLed->setColor(Qt::green);
            else
              mUi->primGPSProgressLed->setColor(Qt::red);
            break;
          case 3:
            if (status.test(i))
              mUi->dmiLeverProgressLed->setColor(Qt::green);
            else
              mUi->dmiLeverProgressLed->setColor(Qt::red);
            break;
          case 4:
            if (status.test(i))
              mUi->dmiScaleProgressLed->setColor(Qt::green);
            else
              mUi->dmiScaleProgressLed->setColor(Qt::red);
            break;
          case 6:
            if (status.test(i))
              mUi->fixLeverProgressLed->setColor(Qt::green);
            else
              mUi->fixLeverProgressLed->setColor(Qt::red);
            break;
          case 8:
            if (status.test(i))
              mUi->primGPSCompleteLed->setColor(Qt::green);
            else
              mUi->primGPSCompleteLed->setColor(Qt::red);
            break;
          case 11:
            if (status.test(i))
              mUi->dmiLeverCompleteLed->setColor(Qt::green);
            else
              mUi->dmiLeverCompleteLed->setColor(Qt::red);
            break;
          case 12:
            if (status.test(i))
              mUi->dmiScaleCompleteLed->setColor(Qt::green);
            else
              mUi->dmiScaleCompleteLed->setColor(Qt::red);
            break;
          case 14:
            if (status.test(i))
              mUi->fixLeverCompleteLed->setColor(Qt::green);
            else
              mUi->fixLeverCompleteLed->setColor(Qt::red);
            break;
          default:
            break;
        }
      }
    }
  }
}
