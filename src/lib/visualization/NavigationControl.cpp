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

#include "visualization/NavigationControl.h"

#include "types/VehicleNavigationPerformance.h"
#include "types/VehicleNavigationSolution.h"
#include "types/Group.h"
#include "ui_NavigationControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

NavigationControl::NavigationControl() :
    mUi(new Ui_NavigationControl()) {
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

NavigationControl::~NavigationControl() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void NavigationControl::packetRead(boost::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<VehicleNavigationSolution>()) {
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
