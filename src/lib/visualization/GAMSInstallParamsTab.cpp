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

#include "visualization/GAMSInstallParamsTab.h"

#include "types/Message.h"
#include "types/Packet.h"
#include "types/GAMSInstallParams.h"

#include "ui_GAMSInstallParamsTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GAMSInstallParamsTab::GAMSInstallParamsTab() :
    mUi(new Ui_GAMSInstallParamsTab()),
    mControlMode(false) {
  mUi->setupUi(this);
  setReadOnlyFields(true);
}

GAMSInstallParamsTab::~GAMSInstallParamsTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void GAMSInstallParamsTab::enableFields(bool enable) {
  mUi->antennaSpinBox->setEnabled(enable);
  mUi->baseXSpinBox->setEnabled(enable);
  mUi->baseYSpinBox->setEnabled(enable);
  mUi->baseZSpinBox->setEnabled(enable);
  mUi->maxHeadSpinBox->setEnabled(enable);
  mUi->headCorrSpinBox->setEnabled(enable);
}

void GAMSInstallParamsTab::setReadOnlyFields(bool readonly) {
  mUi->antennaSpinBox->setReadOnly(readonly);
  mUi->baseXSpinBox->setReadOnly(readonly);
  mUi->baseYSpinBox->setReadOnly(readonly);
  mUi->baseZSpinBox->setReadOnly(readonly);
  mUi->maxHeadSpinBox->setReadOnly(readonly);
  mUi->headCorrSpinBox->setReadOnly(readonly);
}

void GAMSInstallParamsTab::applyPressed() {
}

void GAMSInstallParamsTab::readPacket(boost::shared_ptr<Packet> packet) {
  if (mControlMode)
    return;
  if (packet->instanceOfMessage()) {
    const Message& message = packet->messageCast();
    if (message.instanceOf<GAMSInstallParams>()) {
      enableFields(true);
      const GAMSInstallParams& msg = message.typeCast<GAMSInstallParams>();
      mUi->antennaSpinBox->setValue(msg.mAntennaSeparation);
      mUi->baseXSpinBox->setValue(msg.mBaselineX);
      mUi->baseYSpinBox->setValue(msg.mBaselineY);
      mUi->baseZSpinBox->setValue(msg.mBaselineZ);
      mUi->maxHeadSpinBox->setValue(msg.mMaxHeadingError);
      mUi->headCorrSpinBox->setValue(msg.mHeadingCorrection);
    }
  }
}

void GAMSInstallParamsTab::deviceConnected(bool connected) {
  if (connected) {
    setReadOnlyFields(false);
    mControlMode = true;
    mUi->applyButton->setEnabled(true);
  }
  else {
    setReadOnlyFields(true);
    mControlMode = false;
    mUi->applyButton->setEnabled(false);
  }
}
