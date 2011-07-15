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

#include "visualization/ReadThreadGroup.h"
#include "types/VehicleNavigationPerformance.h"
#include "types/VehicleNavigationSolution.h"
#include "ui_NavigationControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

NavigationControl::NavigationControl() :
  mpUi(new Ui_NavigationControl()) {
  mpUi->setupUi(this);

  connect(&ReadThreadGroup::getInstance(), SIGNAL(groupRead(const Group*)),
    this, SLOT(groupRead(const Group*)));

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
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void NavigationControl::groupRead(const Group* group) {
  if (group->instanceOf<VehicleNavigationSolution>() == true) {
    const VehicleNavigationSolution& msg =
      group->typeCast<VehicleNavigationSolution>();
    mpUi->latSpinBox->setValue(msg.mLatitude);
    mpUi->longSpinBox->setValue(msg.mLongitude);
    mpUi->altSpinBox->setValue(msg.mAltitude);
    mpUi->velNorthSpinBox->setValue(msg.mNorthVelocity);
    mpUi->velEastSpinBox->setValue(msg.mEastVelocity);
    mpUi->velDownSpinBox->setValue(msg.mDownVelocity);
    mpUi->rollSpinBox->setValue(msg.mRoll);
    mpUi->pitchSpinBox->setValue(msg.mPitch);
    mpUi->headingSpinBox->setValue(msg.mHeading);
    mpUi->wanderSpinBox->setValue(msg.mWanderAngle);
    mpUi->trackSpinBox->setValue(msg.mTrackAngle);
    mpUi->speedSpinBox->setValue(msg.mSpeed);
    mpUi->rateLongSpinBox->setValue(msg.mAngularRateLong);
    mpUi->rateTransSpinBox->setValue(msg.mAngularRateTrans);
    mpUi->rateDownSpinBox->setValue(msg.mAngularRateDown);
    mpUi->accLongSpinBox->setValue(msg.mAccLong);
    mpUi->accTransSpinBox->setValue(msg.mAccTrans);
    mpUi->accDownSpinBox->setValue(msg.mAccDown);
    mpUi->alignmentText->setText(mStatusMsg[msg.mAlignementStatus].c_str());
  }
  else if (group->instanceOf<VehicleNavigationPerformance>() == true) {
    const VehicleNavigationPerformance& msg =
      group->typeCast<VehicleNavigationPerformance>();
    mpUi->posNorthRMSSpinBox->setValue(msg.mNorthPositionRMSError);
    mpUi->posEastRMSSpinBox->setValue(msg.mEastPositionRMSError);
    mpUi->posDownRMSSpinBox->setValue(msg.mDownPositionRMSError);
    mpUi->velNorthRMSSpinBox->setValue(msg.mNorthVelocityRMSError);
    mpUi->velEastRMSSpinBox->setValue(msg.mEastVelocityRMSError);
    mpUi->velDownRMSSpinBox->setValue(msg.mDownVelocityRMSError);
    mpUi->rollRMSSpinBox->setValue(msg.mRollRMSError);
    mpUi->pitchRMSSpinBox->setValue(msg.mPitchRMSError);
    mpUi->headingRMSSpinBox->setValue(msg.mHeadingRMSError);
    mpUi->semiMajorSpinBox->setValue(msg.mErrorEllipsoidSemiMajor);
    mpUi->semiMinorSpinBox->setValue(msg.mErrorEllipsoidSemiMinor);
    mpUi->orientationSpinBox->setValue(msg.mErrorEllipsoidOrientation);
  }
}
