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

#include "types/GAMSSolutionStatus.h"
#include "types/Group.h"
#include "ui_GAMSControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GAMSControl::GAMSControl() :
  mUi(new Ui_GAMSControl()) {
  mUi->setupUi(this);
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
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void GAMSControl::packetRead(boost::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<GAMSSolutionStatus>()) {
      const GAMSSolutionStatus& msg = group.typeCast<GAMSSolutionStatus>();
      mUi->satGAMSSpinBox->setValue(msg.mNumberOfSatellites);
      mUi->statusText->setText(mStatusMsg[msg.mSolutionStatus].c_str());
      mUi->antennaSpinBox->setValue(msg.mComputedAntennaSeparation);
      mUi->headingSpinBox->setValue(msg.mGAMSHeading);
      mUi->headingRMSSpinBox->setValue(msg.mGAMSHeadingRMSError);
      mUi->pdopSpinBox->setValue(msg.mAPrioriPDOP);
    }
  }
}
