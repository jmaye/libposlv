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

void NavigationTab::enableFields() {
  mUi->latSpinBox->setEnabled(true);
  mUi->longSpinBox->setEnabled(true);
  mUi->altSpinBox->setEnabled(true);
  mUi->velNorthSpinBox->setEnabled(true);
  mUi->velEastSpinBox->setEnabled(true);
  mUi->velDownSpinBox->setEnabled(true);
  mUi->rollSpinBox->setEnabled(true);
  mUi->pitchSpinBox->setEnabled(true);
  mUi->headingSpinBox->setEnabled(true);
  mUi->wanderSpinBox->setEnabled(true);
  mUi->trackSpinBox->setEnabled(true);
  mUi->speedSpinBox->setEnabled(true);
  mUi->rateLongSpinBox->setEnabled(true);
  mUi->rateTransSpinBox->setEnabled(true);
  mUi->rateDownSpinBox->setEnabled(true);
  mUi->accLongSpinBox->setEnabled(true);
  mUi->accTransSpinBox->setEnabled(true);
  mUi->accDownSpinBox->setEnabled(true);
  mUi->alignmentText->setEnabled(true);
  mUi->posNorthRMSSpinBox->setEnabled(true);
  mUi->posEastRMSSpinBox->setEnabled(true);
  mUi->posDownRMSSpinBox->setEnabled(true);
  mUi->velNorthRMSSpinBox->setEnabled(true);
  mUi->velEastRMSSpinBox->setEnabled(true);
  mUi->velDownRMSSpinBox->setEnabled(true);
  mUi->rollRMSSpinBox->setEnabled(true);
  mUi->pitchRMSSpinBox->setEnabled(true);
  mUi->headingRMSSpinBox->setEnabled(true);
  mUi->semiMajorSpinBox->setEnabled(true);
  mUi->semiMinorSpinBox->setEnabled(true);
  mUi->orientationSpinBox->setEnabled(true);
}

void NavigationTab::disableFields() {
  mUi->latSpinBox->setEnabled(false);
  mUi->longSpinBox->setEnabled(false);
  mUi->altSpinBox->setEnabled(false);
  mUi->velNorthSpinBox->setEnabled(false);
  mUi->velEastSpinBox->setEnabled(false);
  mUi->velDownSpinBox->setEnabled(false);
  mUi->rollSpinBox->setEnabled(false);
  mUi->pitchSpinBox->setEnabled(false);
  mUi->headingSpinBox->setEnabled(false);
  mUi->wanderSpinBox->setEnabled(false);
  mUi->trackSpinBox->setEnabled(false);
  mUi->speedSpinBox->setEnabled(false);
  mUi->rateLongSpinBox->setEnabled(false);
  mUi->rateTransSpinBox->setEnabled(false);
  mUi->rateDownSpinBox->setEnabled(false);
  mUi->accLongSpinBox->setEnabled(false);
  mUi->accTransSpinBox->setEnabled(false);
  mUi->accDownSpinBox->setEnabled(false);
  mUi->alignmentText->setEnabled(false);
  mUi->posNorthRMSSpinBox->setEnabled(false);
  mUi->posEastRMSSpinBox->setEnabled(false);
  mUi->posDownRMSSpinBox->setEnabled(false);
  mUi->velNorthRMSSpinBox->setEnabled(false);
  mUi->velEastRMSSpinBox->setEnabled(false);
  mUi->velDownRMSSpinBox->setEnabled(false);
  mUi->rollRMSSpinBox->setEnabled(false);
  mUi->pitchRMSSpinBox->setEnabled(false);
  mUi->headingRMSSpinBox->setEnabled(false);
  mUi->semiMajorSpinBox->setEnabled(false);
  mUi->semiMinorSpinBox->setEnabled(false);
  mUi->orientationSpinBox->setEnabled(false);
}

void NavigationTab::readPacket(boost::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<VehicleNavigationSolution>()) {
      enableFields();
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
    }
  }
}
