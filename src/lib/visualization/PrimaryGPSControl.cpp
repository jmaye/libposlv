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

#include "visualization/PrimaryGPSControl.h"

#include "visualization/ReadThread.h"
#include "types/PrimaryGPSStatus.h"
#include "types/PPSTimeRecoveryStatus.h"
#include "ui_PrimaryGPSControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PrimaryGPSControl::PrimaryGPSControl() :
  mpUi(new Ui_PrimaryGPSControl()) {
  mpUi->setupUi(this);

  connect(&ReadThread::getInstance(), SIGNAL(groupRead(const Group*)), this,
    SLOT(groupRead(const Group*)));

  mStatusMsg[-1] = "Unknown";
  mStatusMsg[0] = "No data from receiver";
  mStatusMsg[1] = "Horizontal C/A mode";
  mStatusMsg[2] = "3-dimension C/A mode";
  mStatusMsg[3] = "Horizontal DGPS mode";
  mStatusMsg[4] = "3-dimension DGPS mode";
  mStatusMsg[5] = "Float RTK mode";
  mStatusMsg[6] = "Integer wide lane RTK mode";
  mStatusMsg[7] = "Integer narrow lane RTK mode";
  mStatusMsg[8] = "P-code";

  mGPSTypeMsg[0] = "No receiver";
  for (size_t i = 1; i <= 7; i++)
    mGPSTypeMsg[i] = "Reserved";
  mGPSTypeMsg[8] = "Trimble BD112";
  mGPSTypeMsg[9] = "Trimble BD750";
  mGPSTypeMsg[10] = "Reserved";
  mGPSTypeMsg[11] = "Reserved";
  mGPSTypeMsg[12] = "Trimble BD132";
  mGPSTypeMsg[13] = "Trimble BD950";
  mGPSTypeMsg[14] = "Reserved";
  mGPSTypeMsg[15] = "Reserved";
  mGPSTypeMsg[16] = "Trimble BD960";

  mTimeSyncMsg[0] = "Not synchronized";
  mTimeSyncMsg[1] = "Synchronizing";
  mTimeSyncMsg[2] = "Fully synchronized";
  mTimeSyncMsg[3] = "Using old offset";
}

PrimaryGPSControl::~PrimaryGPSControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void PrimaryGPSControl::groupRead(const Group* group) {
  if (group->instanceOf<PrimaryGPSStatus>() == true) {
    const PrimaryGPSStatus& msg = group->typeCast<PrimaryGPSStatus>();
    mpUi->navPrimGPSText->setText(
      mStatusMsg[msg.mNavigationSolutionStatus].c_str());
    mpUi->satPrimGPSSpinBox->setValue(msg.mNumberOfSVTracked);
    mpUi->primGPSTypeText->setText(mGPSTypeMsg[msg.mGPSReceiverType].c_str());
    mpUi->geoidalPrimGPSSpinBox->setValue(msg.mGeoidalSeparation);
  }
  if (group->instanceOf<PPSTimeRecoveryStatus>() == true) {
    const PPSTimeRecoveryStatus& msg = group->typeCast<PPSTimeRecoveryStatus>();
    mpUi->timeStatusText->setText(mTimeSyncMsg[msg.mTimeSynchroStatus].c_str());
  }
}
