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

#include "visualization/SaveRestoreControlTab.h"

#include "types/Message.h"
#include "types/Packet.h"
#include "types/SaveRestoreControl.h"
#include "base/Factory.h"

#include "ui_SaveRestoreControlTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SaveRestoreControlTab::SaveRestoreControlTab() :
    mUi(new Ui_SaveRestoreControlTab()),
    mControlMode(false) {
  mUi->setupUi(this);
}

SaveRestoreControlTab::~SaveRestoreControlTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void SaveRestoreControlTab::applyPressed() {
  boost::shared_ptr<Packet> packet(
    Factory<uint16_t, Message>::getInstance().create(54));
  SaveRestoreControl& msg =
    packet->messageCast().typeCast<SaveRestoreControl>();
  uint8_t control;
  if (mUi->noOpRadioButton->isChecked())
    control = 0;
  else if (mUi->saveRadioButton->isChecked())
    control = 1;
  else if (mUi->restoreNVMRadioButton->isChecked())
    control = 2;
  else if (mUi->restoreFactoryRadioButton->isChecked())
    control = 3;
  else
    control = 0;
  msg.mControl = control;
  emit writePacket(packet);
}

void SaveRestoreControlTab::deviceConnected(bool connected) {
  if (connected) {
    mControlMode = true;
    mUi->applyButton->setEnabled(true);
  }
  else {
    mControlMode = false;
    mUi->applyButton->setEnabled(false);
  }
}
