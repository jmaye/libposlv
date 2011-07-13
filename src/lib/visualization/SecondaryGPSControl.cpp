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

#include "visualization/SecondaryGPSControl.h"

#include "visualization/ReadThread.h"
#include "types/SecondaryGPSStatus.h"
#include "ui_SecondaryGPSControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SecondaryGPSControl::SecondaryGPSControl() :
  mpUi(new Ui_SecondaryGPSControl()) {
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
}

SecondaryGPSControl::~SecondaryGPSControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void SecondaryGPSControl::groupRead(const Group* group) {
  if (group->instanceOf<SecondaryGPSStatus>() == true) {
    const SecondaryGPSStatus& msg = group->typeCast<SecondaryGPSStatus>();
    mpUi->navSecGPSText->setText(
      mStatusMsg[msg.mNavigationSolutionStatus].c_str());
    mpUi->satSecGPSSpinBox->setValue(msg.mNumberOfSVTracked);
    mpUi->secGPSTypeText->setText(mGPSTypeMsg[msg.mGPSReceiverType].c_str());
    mpUi->geoidalSecGPSSpinBox->setValue(msg.mGeoidalSeparation);
    mpUi->hdopSpinBox->setValue(msg.mHDOP);
    mpUi->vdopSpinBox->setValue(msg.mVDOP);
    mpUi->dgpsIDSpinBox->setValue(msg.mDGPSReferenceID);
    mpUi->corrLatencySpinBox->setValue(msg.mDGPSCorrectionLatency);
    mpUi->navLatencySpinBox->setValue(msg.mGPSNavigationMessageLatency);
    mpUi->weekSpinBox->setValue(msg.mGPSUTCWeekNumber);
    mpUi->offsetSpinBox->setValue(msg.mGPSUTCTimeOffset);
  }
}
