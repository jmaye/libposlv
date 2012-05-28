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

#include "visualization/VersionTab.h"

#include "types/VersionStatistics.h"
#include "types/Group.h"
#include "types/Packet.h"

#include "ui_VersionTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

VersionTab::VersionTab() :
    mUi(new Ui_VersionTab()) {
  mUi->setupUi(this);
}

VersionTab::~VersionTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void VersionTab::enableFields() {
  mUi->sysVerText->setEnabled(true);
  mUi->primGPSVerText->setEnabled(true);
  mUi->secGPSVerText->setEnabled(true);
  mUi->totHoursSpinBox->setEnabled(true);
  mUi->runsNbrSpinBox->setEnabled(true);
  mUi->avgRunLengthSpinBox->setEnabled(true);
  mUi->longestRunSpinBox->setEnabled(true);
  mUi->currentRunSpinBox->setEnabled(true);
}

void VersionTab::disableFields() {
  mUi->sysVerText->setEnabled(false);
  mUi->primGPSVerText->setEnabled(false);
  mUi->secGPSVerText->setEnabled(false);
  mUi->totHoursSpinBox->setEnabled(false);
  mUi->runsNbrSpinBox->setEnabled(false);
  mUi->avgRunLengthSpinBox->setEnabled(false);
  mUi->longestRunSpinBox->setEnabled(false);
  mUi->currentRunSpinBox->setEnabled(false);
}

void VersionTab::readPacket(boost::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<VersionStatistics>()) {
      enableFields();
      const VersionStatistics& msg = group.typeCast<VersionStatistics>();
      mUi->sysVerText->setText((const char*)msg.mSystemVersion);
      mUi->primGPSVerText->setText((const char*)msg.mPrimaryGPSVersion);
      mUi->secGPSVerText->setText((const char*)msg.mSecondaryGPSversion);
      mUi->totHoursSpinBox->setValue(msg.mTotalHours);
      mUi->runsNbrSpinBox->setValue(msg.mNumberOfRuns);
      mUi->avgRunLengthSpinBox->setValue(msg.mAverageLengthOfRun);
      mUi->longestRunSpinBox->setValue(msg.mLongestRun);
      mUi->currentRunSpinBox->setValue(msg.mCurrentRun);
    }
  }
}
