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

#include "visualization/AutoCalibrationTab.h"

#include <bitset>

#include "base/Factory.h"
#include "types/Packet.h"
#include "types/Message.h"
#include "types/InstallationCalibrationControl.h"
#include "types/GAMSCalibrationControl.h"

#include "ui_AutoCalibrationTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

AutoCalibrationTab::AutoCalibrationTab() :
    mUi(new Ui_AutoCalibrationTab()),
    mControlMode(false) {
  mUi->setupUi(this);
  setReadOnlyFields(true);
}

AutoCalibrationTab::~AutoCalibrationTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void AutoCalibrationTab::enableFields(bool enable) {
  mUi->stopGAMSRadioButton->setEnabled(enable);
  mUi->beginGAMSRadioButton->setEnabled(enable);
  mUi->suspendGAMSRadioButton->setEnabled(enable);
  mUi->forceGAMSRadioButton->setEnabled(enable);
  mUi->noActionRadioButton->setEnabled(enable);
  mUi->stopGeneralRadioButton->setEnabled(enable);
  mUi->manualGeneralRadioButton->setEnabled(enable);
  mUi->autoGeneralRadioButton->setEnabled(enable);
  mUi->normalGeneralRadioButton->setEnabled(enable);
  mUi->forcedGeneralRadioButton->setEnabled(enable);
  mUi->gpsCheckBox->setEnabled(enable);
  mUi->dmiLeverCheckBox->setEnabled(enable);
  mUi->dmiScaleCheckBox->setEnabled(enable);
  mUi->posCheckBox->setEnabled(enable);

}

void AutoCalibrationTab::setReadOnlyFields(bool readonly) {
  mUi->stopGAMSRadioButton->setCheckable(readonly);
  mUi->beginGAMSRadioButton->setCheckable(readonly);
  mUi->suspendGAMSRadioButton->setCheckable(readonly);
  mUi->forceGAMSRadioButton->setCheckable(readonly);
  mUi->gpsCheckBox->setCheckable(readonly);
  mUi->dmiLeverCheckBox->setCheckable(readonly);
  mUi->dmiScaleCheckBox->setCheckable(readonly);
  mUi->posCheckBox->setCheckable(readonly);
}

void AutoCalibrationTab::applyGeneralPressed() {
  uint8_t control;
  if (mUi->stopGeneralRadioButton->isChecked())
    control = 1;
  else if (mUi->manualGeneralRadioButton->isChecked())
    control = 2;
  else if (mUi->autoGeneralRadioButton->isChecked())
    control = 3;
  else if (mUi->normalGeneralRadioButton->isChecked())
    control = 4;
  else if (mUi->forcedGeneralRadioButton->isChecked())
    control = 5;
  else
    control = 0;
  std::bitset<8> selectBitSet;
  if (mUi->gpsCheckBox->isChecked())
    selectBitSet.set(0);
  if (mUi->dmiLeverCheckBox->isChecked())
    selectBitSet.set(3);
  if (mUi->dmiScaleCheckBox->isChecked())
    selectBitSet.set(4);
  if (mUi->posCheckBox->isChecked())
    selectBitSet.set(7);
  uint8_t select = selectBitSet.to_ulong();
  boost::shared_ptr<Packet> packet(
    Factory<uint16_t, Message>::getInstance().create(57));
  InstallationCalibrationControl& calMsg =
    packet->messageCast().typeCast<InstallationCalibrationControl>();
  calMsg.mCalibrationAction = control;
  calMsg.mCalibrationSelect = select;
  emit writePacket(packet);
}

void AutoCalibrationTab::applyGAMSPressed() {
  uint8_t control;
  if (mUi->stopGAMSRadioButton->isChecked())
    control = 0;
  else if (mUi->beginGAMSRadioButton->isChecked())
    control = 1;
  else if (mUi->suspendGAMSRadioButton->isChecked())
    control = 2;
  else if (mUi->forceGAMSRadioButton->isChecked())
    control = 3;
  else
    control = 0;
  boost::shared_ptr<Packet> packet(
    Factory<uint16_t, Message>::getInstance().create(58));
  GAMSCalibrationControl& calMsg =
    packet->messageCast().typeCast<GAMSCalibrationControl>();
  calMsg.mCalibrationAction = control;
  emit writePacket(packet);
}

void AutoCalibrationTab::readPacket(boost::shared_ptr<Packet> packet) {
  if (mControlMode)
    return;
  if (packet->instanceOfMessage()) {
    const Message& message = packet->messageCast();
    if (message.instanceOf<GAMSCalibrationControl>()) {
      enableFields(true);
      const GAMSCalibrationControl& msg =
        message.typeCast<GAMSCalibrationControl>();
      switch (msg.mCalibrationAction) {
        case 0:
          mUi->stopGAMSRadioButton->setChecked(true);
          break;
        case 1:
          mUi->beginGAMSRadioButton->setChecked(true);
          break;
        case 2:
          mUi->suspendGAMSRadioButton->setChecked(true);
          break;
        case 3:
          mUi->forceGAMSRadioButton->setChecked(true);
          break;
        default:
          break;
      }
    }
    if (message.instanceOf<InstallationCalibrationControl>()) {
      enableFields(true);
      const InstallationCalibrationControl& msg =
        message.typeCast<InstallationCalibrationControl>();
      switch (msg.mCalibrationAction) {
        case 0:
          mUi->noActionRadioButton->setChecked(true);
          break;
        case 1:
          mUi->stopGeneralRadioButton->setChecked(true);
          break;
        case 2:
          mUi->manualGeneralRadioButton->setChecked(true);
          break;
        case 3:
          mUi->autoGeneralRadioButton->setChecked(true);
          break;
        case 4:
          mUi->normalGeneralRadioButton->setChecked(true);
          break;
        case 5:
          mUi->forcedGeneralRadioButton->setChecked(true);
          break;
        default:
          break;
      }
      std::bitset<8> selectBitSet(msg.mCalibrationSelect);
      if (selectBitSet.test(0))
        mUi->gpsCheckBox->setChecked(true);
      else
        mUi->gpsCheckBox->setChecked(false);
      if (selectBitSet.test(3))
        mUi->dmiLeverCheckBox->setChecked(true);
      else
        mUi->dmiLeverCheckBox->setChecked(false);
      if (selectBitSet.test(4))
        mUi->dmiScaleCheckBox->setChecked(true);
      else
        mUi->dmiScaleCheckBox->setChecked(false);
      if (selectBitSet.test(7))
        mUi->posCheckBox->setChecked(true);
      else
        mUi->posCheckBox->setChecked(false);
    }
  }
}

void AutoCalibrationTab::deviceConnected(bool connected) {
  if (connected) {
    setReadOnlyFields(false);
    mControlMode = true;
    mUi->applyGAMSButton->setEnabled(true);
    mUi->applyGeneralButton->setEnabled(true);
  }
  else {
    setReadOnlyFields(true);
    mControlMode = false;
    mUi->applyGAMSButton->setEnabled(false);
    mUi->applyGeneralButton->setEnabled(false);
  }
}
