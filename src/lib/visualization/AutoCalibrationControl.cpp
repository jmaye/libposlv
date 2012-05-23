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

#include "visualization/AutoCalibrationControl.h"

#include <bitset>

#include <boost/shared_ptr.hpp>

#include "base/Factory.h"
#include "types/Message.h"
#include "types/InstallationCalibrationControl.h"
#include "types/GAMSCalibrationControl.h"

#include "ui_AutoCalibrationControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

AutoCalibrationControl::AutoCalibrationControl() :
    mUi(new Ui_AutoCalibrationControl()) {
  mUi->setupUi(this);
}

AutoCalibrationControl::~AutoCalibrationControl() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void AutoCalibrationControl::applyGeneralPressed() {
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
  boost::shared_ptr<Message> msg(
    Factory<uint16_t, Message>::getInstance().create(57));
  InstallationCalibrationControl& calMsg =
    msg->typeCast<InstallationCalibrationControl>();
  calMsg.mCalibrationAction = control;
  calMsg.mCalibrationSelect = select;
  sendMessage(msg);
}

void AutoCalibrationControl::applyGAMSPressed() {
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
  boost::shared_ptr<Message> msg(
    Factory<uint16_t, Message>::getInstance().create(58));
  GAMSCalibrationControl& calMsg =
    msg->typeCast<GAMSCalibrationControl>();
  calMsg.mCalibrationAction = control;
  sendMessage(msg);
}
