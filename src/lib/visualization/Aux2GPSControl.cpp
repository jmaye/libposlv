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

#include "visualization/Aux2GPSControl.h"

#include "types/Auxiliary2GPSStatus.h"
#include "types/Group.h"
#include "types/Packet.h"

#include "ui_Aux2GPSControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

Aux2GPSControl::Aux2GPSControl() :
    mUi(new Ui_Aux2GPSControl()) {
  mUi->setupUi(this);
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
}

Aux2GPSControl::~Aux2GPSControl() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void Aux2GPSControl::readPacket(boost::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<Auxiliary2GPSStatus>()) {
      const Auxiliary2GPSStatus& msg = group.typeCast<Auxiliary2GPSStatus>();
      mUi->navAux2GPSText->setText(
        mStatusMsg[msg.mNavigationSolutionStatus].c_str());
      mUi->satAux2GPSSpinBox->setValue(msg.mNumberOfSVTracked);
      mUi->geoidalAux2GPSSpinBox->setValue(msg.mGeoidalSeparation);
      if (msg.mAux12InUse)
        mUi->activeAux2CheckBox->setChecked(true);
      else
        mUi->activeAux2CheckBox->setChecked(false);
    }
  }
}
