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

#include "visualization/UserAccuracySpecTab.h"

#include "types/Message.h"
#include "types/Packet.h"
#include "types/UserAccuracySpec.h"

#include "ui_UserAccuracySpecTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

UserAccuracySpecTab::UserAccuracySpecTab() :
    mUi(new Ui_UserAccuracySpecTab()),
    mControlMode(false) {
  mUi->setupUi(this);
  setReadOnlyFields(true);
}

UserAccuracySpecTab::~UserAccuracySpecTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void UserAccuracySpecTab::enableFields(bool enable) {
  mUi->attAccSpinBox->setEnabled(enable);
  mUi->headingAccSpinBox->setEnabled(enable);
  mUi->posAccSpinBox->setEnabled(enable);
  mUi->velAccSpinBox->setEnabled(enable);
}

void UserAccuracySpecTab::setReadOnlyFields(bool readonly) {
  mUi->attAccSpinBox->setReadOnly(readonly);
  mUi->headingAccSpinBox->setReadOnly(readonly);
  mUi->posAccSpinBox->setReadOnly(readonly);
  mUi->velAccSpinBox->setReadOnly(readonly);
}

void UserAccuracySpecTab::applyPressed() {
}

void UserAccuracySpecTab::readPacket(boost::shared_ptr<Packet> packet) {
  if (mControlMode)
    return;
  if (packet->instanceOfMessage()) {
    const Message& message = packet->messageCast();
    if (message.instanceOf<UserAccuracySpec>()) {
      enableFields(true);
      const UserAccuracySpec& msg = message.typeCast<UserAccuracySpec>();
      mUi->attAccSpinBox->setValue(msg.mAttitudeAccuracy);
      mUi->headingAccSpinBox->setValue(msg.mHeadingAccuracy);
      mUi->posAccSpinBox->setValue(msg.mPositionAccuracy);
      mUi->velAccSpinBox->setValue(msg.mVelocityAccuracy);
    }
  }
}

void UserAccuracySpecTab::deviceConnected(bool connected) {
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
