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

#include "visualization/GAMSControl.h"

#include "visualization/ReadThread.h"
#include "types/GAMSSolutionStatus.h"
#include "ui_GAMSControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GAMSControl::GAMSControl() :
  mpUi(new Ui_GAMSControl()) {
  mpUi->setupUi(this);

  connect(&ReadThread::getInstance(), SIGNAL(groupRead(const Group*)), this,
    SLOT(groupRead(const Group*)));

  mStatusMsg[0] = "Fixed integer";
  mStatusMsg[1] = "Fixed integer test install data";
  mStatusMsg[2] = "Degraded fixed integer";
  mStatusMsg[3] = "Floated ambiguity";
  mStatusMsg[4] = "Degraded floated ambiguity";
  mStatusMsg[5] = "Solution without install data";
  mStatusMsg[6] = "Solution from navigator attitude and install data";
  mStatusMsg[7] = "No solution";
}

GAMSControl::~GAMSControl() {
  delete mpUi;
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void GAMSControl::groupRead(const Group* group) {
  if (group->instanceOf<GAMSSolutionStatus>() == true) {
    const GAMSSolutionStatus& msg = group->typeCast<GAMSSolutionStatus>();
    mpUi->satGAMSSpinBox->setValue(msg.mNumberOfSatellites);
    mpUi->statusText->setText(mStatusMsg[msg.mSolutionStatus].c_str());
    mpUi->antennaSpinBox->setValue(msg.mComputedAntennaSeparation);
    mpUi->headingSpinBox->setValue(msg.mGAMSHeading);
    mpUi->headingRMSSpinBox->setValue(msg.mGAMSHeadingRMSError);
    mpUi->pdopSpinBox->setValue(msg.mAPrioriPDOP);
  }
}
