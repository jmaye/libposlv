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

#include "visualization/IINStatusTab.h"

#include "types/IINSolutionStatus.h"
#include "types/Group.h"
#include "types/Packet.h"

#include "ui_IINStatusTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

IINStatusTab::IINStatusTab() :
    mUi(new Ui_IINStatusTab()) {
  mUi->setupUi(this);
  mStatusMsg[1] = "Fixed narrow lane RTK";
  mStatusMsg[2] = "Fixed wide lane RTK";
  mStatusMsg[3] = "Float RTK";
  mStatusMsg[4] = "Code DGPS";
  mStatusMsg[5] = "RTCM DGPS";
  mStatusMsg[6] = "Autonmous (C/A)";
  mStatusMsg[7] = "GPS navigation solution";
  mStatusMsg[8] = "No solution";
}

IINStatusTab::~IINStatusTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void IINStatusTab::enableFields() {
  mUi->satIINSpinBox->setEnabled(true);
  mUi->statusText->setEnabled(true);
  mUi->baselineSpinBox->setEnabled(true);
  mUi->pdopSpinBox->setEnabled(true);
}

void IINStatusTab::disableFields() {
  mUi->satIINSpinBox->setEnabled(false);
  mUi->statusText->setEnabled(false);
  mUi->baselineSpinBox->setEnabled(false);
  mUi->pdopSpinBox->setEnabled(false);
}

void IINStatusTab::readPacket(boost::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<IINSolutionStatus>()) {
      enableFields();
      const IINSolutionStatus& msg = group.typeCast<IINSolutionStatus>();
      mUi->satIINSpinBox->setValue(msg.mNumberOfSatellites);
      mUi->statusText->setText(mStatusMsg[msg.mIINProcessingStatus].c_str());
      mUi->baselineSpinBox->setValue(msg.mBaselineLength);
      mUi->pdopSpinBox->setValue(msg.mAPrioriPDOP);
    }
  }
}
