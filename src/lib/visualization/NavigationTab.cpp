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

#include "visualization/NavigationTab.h"

#include "types/VehicleNavigationPerformance.h"
#include "types/VehicleNavigationSolution.h"
#include "types/Group.h"
#include "types/Packet.h"

#include "ui_NavigationTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

NavigationTab::NavigationTab() :
    mUi(new Ui_NavigationTab()) {
  mUi->setupUi(this);
  mStatusMsg[0] = "Full navigation";
  mStatusMsg[1] = "Fine alignment active";
  mStatusMsg[2] = "GC CHI 2";
  mStatusMsg[3] = "PC CHI 2";
  mStatusMsg[4] = "GC CHI 1";
  mStatusMsg[5] = "PC CHI 1";
  mStatusMsg[6] = "Coarse leveling active";
  mStatusMsg[7] = "Initial solution assigned";
  mStatusMsg[8] = "No valid solution";
}

NavigationTab::~NavigationTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void NavigationTab::enableFields(bool enable) {
  mUi->latSpinBox->setEnabled(enable);
  mUi->longSpinBox->setEnabled(enable);
  mUi->altSpinBox->setEnabled(enable);
  mUi->velNorthSpinBox->setEnabled(enable);
  mUi->velEastSpinBox->setEnabled(enable);
  mUi->velDownSpinBox->setEnabled(enable);
  mUi->rollSpinBox->setEnabled(enable);
  mUi->pitchSpinBox->setEnabled(enable);
  mUi->headingSpinBox->setEnabled(enable);
  mUi->wanderSpinBox->setEnabled(enable);
  mUi->trackSpinBox->setEnabled(enable);
  mUi->speedSpinBox->setEnabled(enable);
  mUi->rateLongSpinBox->setEnabled(enable);
  mUi->rateTransSpinBox->setEnabled(enable);
  mUi->rateDownSpinBox->setEnabled(enable);
  mUi->accLongSpinBox->setEnabled(enable);
  mUi->accTransSpinBox->setEnabled(enable);
  mUi->accDownSpinBox->setEnabled(enable);
  mUi->alignmentText->setEnabled(enable);
  mUi->posNorthRMSSpinBox->setEnabled(enable);
  mUi->posEastRMSSpinBox->setEnabled(enable);
  mUi->posDownRMSSpinBox->setEnabled(enable);
  mUi->velNorthRMSSpinBox->setEnabled(enable);
  mUi->velEastRMSSpinBox->setEnabled(enable);
  mUi->velDownRMSSpinBox->setEnabled(enable);
  mUi->rollRMSSpinBox->setEnabled(enable);
  mUi->pitchRMSSpinBox->setEnabled(enable);
  mUi->headingRMSSpinBox->setEnabled(enable);
  mUi->semiMajorSpinBox->setEnabled(enable);
  mUi->semiMinorSpinBox->setEnabled(enable);
  mUi->orientationSpinBox->setEnabled(enable);
}

void NavigationTab::readPacket(std::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<VehicleNavigationSolution>()) {
      enableFields(true);
      const VehicleNavigationSolution& msg =
        group.typeCast<VehicleNavigationSolution>();
      mUi->latSpinBox->setValue(msg.mLatitude);
      mUi->longSpinBox->setValue(msg.mLongitude);
      mUi->altSpinBox->setValue(msg.mAltitude);
      mUi->velNorthSpinBox->setValue(msg.mNorthVelocity);
      mUi->velEastSpinBox->setValue(msg.mEastVelocity);
      mUi->velDownSpinBox->setValue(msg.mDownVelocity);
      mUi->rollSpinBox->setValue(msg.mRoll);
      mUi->pitchSpinBox->setValue(msg.mPitch);
      mUi->headingSpinBox->setValue(msg.mHeading);
      mUi->wanderSpinBox->setValue(msg.mWanderAngle);
      mUi->trackSpinBox->setValue(msg.mTrackAngle);
      mUi->speedSpinBox->setValue(msg.mSpeed);
      mUi->rateLongSpinBox->setValue(msg.mAngularRateLong);
      mUi->rateTransSpinBox->setValue(msg.mAngularRateTrans);
      mUi->rateDownSpinBox->setValue(msg.mAngularRateDown);
      mUi->accLongSpinBox->setValue(msg.mAccLong);
      mUi->accTransSpinBox->setValue(msg.mAccTrans);
      mUi->accDownSpinBox->setValue(msg.mAccDown);
      mUi->alignmentText->setText(mStatusMsg[msg.mAlignementStatus].c_str());
      emit updatePosition(msg.mLatitude, msg.mLongitude, msg.mAltitude);
    }
    else if (group.instanceOf<VehicleNavigationPerformance>()) {
      const VehicleNavigationPerformance& msg =
        group.typeCast<VehicleNavigationPerformance>();
      mUi->posNorthRMSSpinBox->setValue(msg.mNorthPositionRMSError);
      mUi->posEastRMSSpinBox->setValue(msg.mEastPositionRMSError);
      mUi->posDownRMSSpinBox->setValue(msg.mDownPositionRMSError);
      mUi->velNorthRMSSpinBox->setValue(msg.mNorthVelocityRMSError);
      mUi->velEastRMSSpinBox->setValue(msg.mEastVelocityRMSError);
      mUi->velDownRMSSpinBox->setValue(msg.mDownVelocityRMSError);
      mUi->rollRMSSpinBox->setValue(msg.mRollRMSError);
      mUi->pitchRMSSpinBox->setValue(msg.mPitchRMSError);
      mUi->headingRMSSpinBox->setValue(msg.mHeadingRMSError);
      mUi->semiMajorSpinBox->setValue(msg.mErrorEllipsoidSemiMajor);
      mUi->semiMinorSpinBox->setValue(msg.mErrorEllipsoidSemiMinor);
      mUi->orientationSpinBox->setValue(msg.mErrorEllipsoidOrientation);
      emit updateUncertainty(msg.mNorthPositionRMSError,
        msg.mEastPositionRMSError, msg.mDownPositionRMSError);
    }
  }
}
