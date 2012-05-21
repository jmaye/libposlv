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

#include "types/IPControl.h"
#include "types/AidingSensorControl.h"
#include "types/GAMSInstallationControl.h"
#include "types/GravityControl.h"
#include "types/ZUPDControl.h"
#include "types/UserAccuracyControl.h"
#include "types/NavigationModeControl.h"
#include "types/GeneralInstallationControl.h"
#include "types/Message.h"
#include "ui_ParametersControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ParametersControl::ParametersControl() :
    mUi(new Ui_ParametersControl()) {
  mUi->setupUi(this);
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
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ParametersControl::packetRead(boost::shared_ptr<Packet> packet) {
  if (packet->instanceOfMessage()) {
    const Message& message = packet->messageCast();
    if (message.instanceOf<IPControl>()) {
      const IPControl& msg = message.typeCast<IPControl>();
      mUi->net1SpinBox->setValue(msg.mNetworkPart1);
      mUi->net2SpinBox->setValue(msg.mNetworkPart2);
      mUi->net3SpinBox->setValue(msg.mHostPart1);
      mUi->net4SpinBox->setValue(msg.mHostPart2);
      mUi->subnet1SpinBox->setValue(msg.mSubNetworkPart1);
      mUi->subnet2SpinBox->setValue(msg.mSubNetworkPart2);
      mUi->subnet3SpinBox->setValue(msg.mSubHostPart1);
      mUi->subnet4SpinBox->setValue(msg.mSubHostPart2);
    }
    if (message.instanceOf<AidingSensorControl>()) {
      const AidingSensorControl& msg = message.typeCast<AidingSensorControl>();
      mUi->dmiScaleSpinBox->setValue(msg.mDMIScaleFactor);
      mUi->dmiXSpinBox->setValue(msg.mRefDMIX);
      mUi->dmiYSpinBox->setValue(msg.mRefDMIY);
      mUi->dmiZSpinBox->setValue(msg.mRefDMIZ);
    }
    if (message.instanceOf<GAMSInstallationControl>()) {
      const GAMSInstallationControl& msg =
        message.typeCast<GAMSInstallationControl>();
      mUi->antennaSpinBox->setValue(msg.mAntennaSeparation);
      mUi->baseXSpinBox->setValue(msg.mBaselineX);
      mUi->baseYSpinBox->setValue(msg.mBaselineY);
      mUi->baseZSpinBox->setValue(msg.mBaselineZ);
      mUi->maxHeadSpinBox->setValue(msg.mMaxHeadingError);
      mUi->headCorrSpinBox->setValue(msg.mHeadingCorrection);
    }
    if (message.instanceOf<GravityControl>()) {
      const GravityControl& msg = message.typeCast<GravityControl>();
      std::cout << msg.mMagnitude << std::endl;
      mUi->magnitudeSpinBox->setValue(msg.mMagnitude);
      mUi->northDefSpinBox->setValue(msg.mNorthDeflection);
      mUi->eastDefSpinBox->setValue(msg.mEastDeflection);
      mUi->latValSpinBox->setValue(msg.mLatitudeValidity);
      mUi->longValSpinBox->setValue(msg.mLongitudeValidity);
      mUi->altValSpinBox->setValue(msg.mAltitudeValidity);
    }
    if (message.instanceOf<ZUPDControl>()) {
      const ZUPDControl& msg = message.typeCast<ZUPDControl>();
      mUi->zupdCtrlText->setText(mZUPDCtrlMsg[msg.mControl].c_str());
      mUi->detectSpinBox->setValue(msg.mDetectZeroVelocityThreshold);
      mUi->rejectSpinBox->setValue(msg.mRejectZeroVelocityThreshold);
      mUi->testSpinBox->setValue(msg.mZeroVelocityTestPeriod);
      mUi->zupdStdSpinBox->setValue(msg.mZUPDStd);
    }
    if (message.instanceOf<UserAccuracyControl>()) {
      const UserAccuracyControl& msg = message.typeCast<UserAccuracyControl>();
      mUi->attAccSpinBox->setValue(msg.mAttitudeAccuracy);
      mUi->headingAccSpinBox->setValue(msg.mHeadingAccuracy);
      mUi->posAccSpinBox->setValue(msg.mPositionAccuracy);
      mUi->velAccSpinBox->setValue(msg.mVelocityAccuracy);
    }
    if (message.instanceOf<NavigationModeControl>()) {
      const NavigationModeControl& msg =
        message.typeCast<NavigationModeControl>();
      mUi->navModeText->setText(mNavModeMsg[msg.mNavigationMode].c_str());
    }
    if (message.instanceOf<GeneralInstallationControl>()) {
      const GeneralInstallationControl& msg =
        message.typeCast<GeneralInstallationControl>();
    mUi->time1Text->setText(mTimeTypesMsg[msg.mTimeTypes & 0x0F].c_str());
    mUi->time2Text->setText(
      mTimeTypesMsg[(msg.mTimeTypes >> 4) & 0x0F].c_str());
    mUi->distTypeText->setText(mDistanceTypeMsg[msg.mDistanceType].c_str());
    mUi->autoStartText->setText(mAutoStartMsg[msg.mAutoStart].c_str());
    mUi->refIMUXSpinBox->setValue(msg.mRefIMUX);
    mUi->refIMUYSpinBox->setValue(msg.mRefIMUY);
    mUi->refIMUZSpinBox->setValue(msg.mRefIMUZ);
    mUi->refPrimGPSXSpinBox->setValue(msg.mRefPrimGPSX);
    mUi->refPrimGPSYSpinBox->setValue(msg.mRefPrimGPSY);
    mUi->refPrimGPSZSpinBox->setValue(msg.mRefPrimGPSZ);
    mUi->xIMURefMountingAngleSpinBox->setValue(msg.mXIMURefMountingAngle);
    mUi->yIMURefMountingAngleSpinBox->setValue(msg.mYIMURefMountingAngle);
    mUi->zIMURefMountingAngleSpinBox->setValue(msg.mZIMURefMountingAngle);
    mUi->xRefVehicMountingAngleSpinBox->setValue(msg.mXRefVehicleMountingAngle);
    mUi->yRefVehicMountingAngleSpinBox->setValue(msg.mYRefVehicleMountingAngle);
    mUi->zRefVehicMountingAngleSpinBox->setValue(msg.mZRefVehicleMountingAngle);
    mUi->multiPathText->setText(
      mMultiEnvMsg[msg.mMultipathEnvironment].c_str());
    }
  }
}
