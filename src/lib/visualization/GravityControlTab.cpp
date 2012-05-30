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

#include "visualization/GravityControlTab.h"

#include "types/Message.h"
#include "types/Packet.h"
#include "types/PreciseGravitySpec.h"

#include "ui_GravityControlTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GravityControlTab::GravityControlTab() :
    mUi(new Ui_GravityControlTab()),
    mControlMode(false) {
  mUi->setupUi(this);
  setReadOnlyFields(true);
}

GravityControlTab::~GravityControlTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void GravityControlTab::enableFields(bool enable) {
  mUi->magnitudeSpinBox->setEnabled(enable);
  mUi->northDefSpinBox->setEnabled(enable);
  mUi->eastDefSpinBox->setEnabled(enable);
  mUi->latValSpinBox->setEnabled(enable);
  mUi->longValSpinBox->setEnabled(enable);
  mUi->altValSpinBox->setEnabled(enable);
}

void GravityControlTab::setReadOnlyFields(bool readonly) {
  mUi->magnitudeSpinBox->setReadOnly(readonly);
  mUi->northDefSpinBox->setReadOnly(readonly);
  mUi->eastDefSpinBox->setReadOnly(readonly);
  mUi->latValSpinBox->setReadOnly(readonly);
  mUi->longValSpinBox->setReadOnly(readonly);
  mUi->altValSpinBox->setReadOnly(readonly);
}

void GravityControlTab::applyPressed() {
  static uint16_t transactionNumber = 0;
}

void GravityControlTab::readPacket(boost::shared_ptr<Packet> packet) {
  if (mControlMode)
    return;
  if (packet->instanceOfMessage()) {
    const Message& message = packet->messageCast();
    if (message.instanceOf<PreciseGravitySpec>()) {
      enableFields(true);
      const PreciseGravitySpec& msg = message.typeCast<PreciseGravitySpec>();
      mUi->magnitudeSpinBox->setValue(msg.mMagnitude);
      mUi->northDefSpinBox->setValue(msg.mNorthDeflection);
      mUi->eastDefSpinBox->setValue(msg.mEastDeflection);
      mUi->latValSpinBox->setValue(msg.mLatitudeValidity);
      mUi->longValSpinBox->setValue(msg.mLongitudeValidity);
      mUi->altValSpinBox->setValue(msg.mAltitudeValidity);
    }
  }
}

void GravityControlTab::deviceConnected(bool connected) {
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
