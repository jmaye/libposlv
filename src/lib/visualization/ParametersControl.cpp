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

#include "visualization/ParametersControl.h"

#include "visualization/ReadThread.h"
#include "types/IPControl.h"
#include "types/AidingSensorControl.h"
#include "types/GAMSInstallationControl.h"
#include "types/GravityControl.h"
#include "types/ZUPDControl.h"
#include "types/UserAccuracyControl.h"
#include "types/NavigationModeControl.h"
#include "types/GeneralInstallationControl.h"
#include "ui_ParametersControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ParametersControl::ParametersControl() :
  mpUi(new Ui_ParametersControl()) {
  mpUi->setupUi(this);

  connect(&ReadThread::getInstance(), SIGNAL(messageRead(const Message*)), this,
    SLOT(messageRead(const Message*)));

  mZUPDCtrlMsg[0] = "no ZUPD";
  mZUPDCtrlMsg[1] = "manual ZUPD";
  mZUPDCtrlMsg[2] = "SNV-detected Auto-ZUPD";
  mZUPDCtrlMsg[3] = "DMI-detected Auto-ZUPD";
  mZUPDCtrlMsg[4] = "GPS-detected Auto-ZUPD";

  mNavModeMsg[0] = "No operation";
  mNavModeMsg[1] = "Standby";
  mNavModeMsg[2] = "Navigate";

  mTimeTypesMsg[0] = "POS time";
  mTimeTypesMsg[1] = "GPS time";
  mTimeTypesMsg[2] = "UTC time";
  mTimeTypesMsg[3] = "User time";

  mDistanceTypeMsg[0] = "N/A";
  mDistanceTypeMsg[1] = "POS distance";
  mDistanceTypeMsg[2] = "DMI distance";

  mAutoStartMsg[0] = "AutoStart disabled";
  mAutoStartMsg[1] = "AutoStart enabled";

  mMultiEnvMsg[0] = "Low";
  mMultiEnvMsg[1] = "Medium";
  mMultiEnvMsg[2] = "High";
}

ParametersControl::~ParametersControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ParametersControl::messageRead(const Message* message) {
  if (message->instanceOf<IPControl>() == true) {
    const IPControl& msg = message->typeCast<IPControl>();
    mpUi->net1SpinBox->setValue(msg.mNetworkPart1);
    mpUi->net2SpinBox->setValue(msg.mNetworkPart2);
    mpUi->net3SpinBox->setValue(msg.mHostPart1);
    mpUi->net4SpinBox->setValue(msg.mHostPart2);
    mpUi->subnet1SpinBox->setValue(msg.mSubNetworkPart1);
    mpUi->subnet2SpinBox->setValue(msg.mSubNetworkPart2);
    mpUi->subnet3SpinBox->setValue(msg.mSubHostPart1);
    mpUi->subnet4SpinBox->setValue(msg.mSubHostPart2);
  }
  if (message->instanceOf<AidingSensorControl>() == true) {
    const AidingSensorControl& msg = message->typeCast<AidingSensorControl>();
    mpUi->dmiScaleSpinBox->setValue(msg.mDMIScaleFactor);
    mpUi->dmiXSpinBox->setValue(msg.mRefDMIX);
    mpUi->dmiYSpinBox->setValue(msg.mRefDMIY);
    mpUi->dmiZSpinBox->setValue(msg.mRefDMIZ);
  }
  if (message->instanceOf<GAMSInstallationControl>() == true) {
    const GAMSInstallationControl& msg =
      message->typeCast<GAMSInstallationControl>();
    mpUi->antennaSpinBox->setValue(msg.mAntennaSeparation);
    mpUi->baseXSpinBox->setValue(msg.mBaselineX);
    mpUi->baseYSpinBox->setValue(msg.mBaselineY);
    mpUi->baseZSpinBox->setValue(msg.mBaselineZ);
    mpUi->maxHeadSpinBox->setValue(msg.mMaxHeadingError);
    mpUi->headCorrSpinBox->setValue(msg.mHeadingCorrection);
  }
  if (message->instanceOf<GravityControl>() == true) {
    const GravityControl& msg = message->typeCast<GravityControl>();
    mpUi->magnitudeSpinBox->setValue(msg.mMagnitude);
    mpUi->northDefSpinBox->setValue(msg.mNorthDeflection);
    mpUi->eastDefSpinBox->setValue(msg.mEastDeflection);
    mpUi->latValSpinBox->setValue(msg.mLatitudeValidity);
    mpUi->longValSpinBox->setValue(msg.mLongitudeValidity);
    mpUi->altValSpinBox->setValue(msg.mAltitudeValidity);
  }
  if (message->instanceOf<ZUPDControl>() == true) {
    const ZUPDControl& msg = message->typeCast<ZUPDControl>();
    mpUi->zupdCtrlText->setText(mZUPDCtrlMsg[msg.mControl].c_str());
    mpUi->detectSpinBox->setValue(msg.mDetectZeroVelocityThreshold);
    mpUi->rejectSpinBox->setValue(msg.mRejectZeroVelocityThreshold);
    mpUi->testSpinBox->setValue(msg.mZeroVelocityTestPeriod);
    mpUi->zupdStdSpinBox->setValue(msg.mZUPDStd);
  }
  if (message->instanceOf<UserAccuracyControl>() == true) {
    const UserAccuracyControl& msg = message->typeCast<UserAccuracyControl>();
    mpUi->attAccSpinBox->setValue(msg.mAttitudeAccuracy);
    mpUi->headingAccSpinBox->setValue(msg.mHeadingAccuracy);
    mpUi->posAccSpinBox->setValue(msg.mPositionAccuracy);
    mpUi->velAccSpinBox->setValue(msg.mVelocityAccuracy);
  }
  if (message->instanceOf<NavigationModeControl>() == true) {
    const NavigationModeControl& msg =
      message->typeCast<NavigationModeControl>();
    mpUi->navModeText->setText(mNavModeMsg[msg.mNavigationMode].c_str());
  }
  if (message->instanceOf<GeneralInstallationControl>() == true) {
    const GeneralInstallationControl& msg =
      message->typeCast<GeneralInstallationControl>();
  mpUi->time1Text->setText(mTimeTypesMsg[msg.mTimeTypes & 0x0F].c_str());
  mpUi->time1Text->setText(mTimeTypesMsg[(msg.mTimeTypes >> 4) & 0x0F].c_str());
  mpUi->distTypeText->setText(mDistanceTypeMsg[msg.mDistanceType].c_str());
  mpUi->autoStartText->setText(mAutoStartMsg[msg.mAutoStart].c_str());
  mpUi->refIMUXSpinBox->setValue(msg.mRefIMUX);
  mpUi->refIMUYSpinBox->setValue(msg.mRefIMUY);
  mpUi->refIMUZSpinBox->setValue(msg.mRefIMUZ);
  mpUi->refPrimGPSXSpinBox->setValue(msg.mRefPrimGPSX);
  mpUi->refPrimGPSYSpinBox->setValue(msg.mRefPrimGPSY);
  mpUi->refPrimGPSZSpinBox->setValue(msg.mRefPrimGPSZ);
  mpUi->xIMURefMountingAngleSpinBox->setValue(msg.mXIMURefMountingAngle);
  mpUi->yIMURefMountingAngleSpinBox->setValue(msg.mYIMURefMountingAngle);
  mpUi->zIMURefMountingAngleSpinBox->setValue(msg.mZIMURefMountingAngle);
  mpUi->xRefVehicMountingAngleSpinBox->setValue(msg.mXRefVehicleMountingAngle);
  mpUi->yRefVehicMountingAngleSpinBox->setValue(msg.mYRefVehicleMountingAngle);
  mpUi->zRefVehicMountingAngleSpinBox->setValue(msg.mZRefVehicleMountingAngle);
  mpUi->multiPathText->setText(mMultiEnvMsg[msg.mMultipathEnvironment].c_str());
  }
}
