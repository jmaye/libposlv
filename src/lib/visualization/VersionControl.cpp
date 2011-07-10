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

#include "visualization/VersionControl.h"

#include "visualization/ReadThread.h"
#include "types/VersionStatistics.h"
#include "ui_VersionControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

VersionControl::VersionControl() :
  mpUi(new Ui_VersionControl()) {
  mpUi->setupUi(this);

  connect(&ReadThread::getInstance(), SIGNAL(groupRead(const Group*)), this,
    SLOT(groupRead(const Group*)));
}

VersionControl::~VersionControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void VersionControl::groupRead(const Group* group) {
  if (group->instanceOf<VersionStatistics>() == true) {
    const VersionStatistics& msg = group->typeCast<VersionStatistics>();
    mpUi->sysVerText->setText((const char*)msg.mau8SystemVersion);
    mpUi->primGPSVerText->setText((const char*)msg.mau8PrimaryGPSVersion);
    mpUi->secGPSVerText->setText((const char*)msg.mau8SecondaryGPSversion);
    mpUi->totHoursSpinBox->setValue(msg.mTotalHours);
    mpUi->runsNbrSpinBox->setValue(msg.mNumberOfRuns);
    mpUi->avgRunLengthSpinBox->setValue(msg.mAverageLengthOfRun);
    mpUi->longestRunSpinBox->setValue(msg.mLongestRun);
    mpUi->currentRunSpinBox->setValue(msg.mCurrentRun);
  }
}
