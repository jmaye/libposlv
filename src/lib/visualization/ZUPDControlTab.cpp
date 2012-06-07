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

#include "visualization/ZUPDControlTab.h"

#include "types/Message.h"
#include "types/Packet.h"
#include "types/ZUPDControl.h"

#include "ui_ZUPDControlTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ZUPDControlTab::ZUPDControlTab() :
    mUi(new Ui_ZUPDControlTab()),
    mControlMode(false) {
  mUi->setupUi(this);
  setReadOnlyFields(true);
}

ZUPDControlTab::~ZUPDControlTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ZUPDControlTab::enableFields(bool enable) {
  mUi->detectSpinBox->setEnabled(enable);
  mUi->rejectSpinBox->setEnabled(enable);
  mUi->testSpinBox->setEnabled(enable);
  mUi->zupdStdSpinBox->setEnabled(enable);
  mUi->noZUPDRadioButton->setEnabled(enable);
  mUi->manualZUPDRadioButton->setEnabled(enable);
  mUi->snvRadioButton->setEnabled(enable);
  mUi->dmiRadioButton->setEnabled(enable);
  mUi->gpsRadioButton->setEnabled(enable);
}

void ZUPDControlTab::setReadOnlyFields(bool readonly) {
  mUi->detectSpinBox->setReadOnly(readonly);
  mUi->rejectSpinBox->setReadOnly(readonly);
  mUi->testSpinBox->setReadOnly(readonly);
  mUi->zupdStdSpinBox->setReadOnly(readonly);
}

void ZUPDControlTab::applyPressed() {
  static uint16_t transactionNumber = 0;
}

void ZUPDControlTab::readPacket(std::shared_ptr<Packet> packet) {
  if (mControlMode)
    return;
  if (packet->instanceOfMessage()) {
    const Message& message = packet->messageCast();
    if (message.instanceOf<ZUPDControl>()) {
      enableFields(true);
      const ZUPDControl& msg = message.typeCast<ZUPDControl>();
      mUi->detectSpinBox->setValue(msg.mDetectZeroVelocityThreshold);
      mUi->rejectSpinBox->setValue(msg.mRejectZeroVelocityThreshold);
      mUi->testSpinBox->setValue(msg.mZeroVelocityTestPeriod);
      mUi->zupdStdSpinBox->setValue(msg.mZUPDStd);
      switch (msg.mControl) {
        case 0:
          mUi->noZUPDRadioButton->setChecked(true);
          break;
        case 1:
          mUi->manualZUPDRadioButton->setChecked(true);
          break;
        case 2:
          mUi->snvRadioButton->setChecked(true);
          break;
        case 3:
          mUi->dmiRadioButton->setChecked(true);
          break;
        case 4:
          mUi->gpsRadioButton->setChecked(true);
          break;
        default:
          break;
      }
    }
  }
}

void ZUPDControlTab::deviceConnected(bool connected) {
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
