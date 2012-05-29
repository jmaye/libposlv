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

#include "visualization/NavigationModeControlTab.h"

#include "types/Message.h"
#include "types/Packet.h"
#include "types/NavigationModeControl.h"

#include "ui_NavigationModeControlTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

NavigationModeControlTab::NavigationModeControlTab() :
    mUi(new Ui_NavigationModeControlTab()),
    mControlMode(false) {
  mUi->setupUi(this);
  setReadOnlyFields(true);
}

NavigationModeControlTab::~NavigationModeControlTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void NavigationModeControlTab::enableFields(bool enable) {
  mUi->noOpRadioButton->setEnabled(enable);
  mUi->standbyRadioButton->setEnabled(enable);
  mUi->navigateRadioButton->setEnabled(enable);
}

void NavigationModeControlTab::setReadOnlyFields(bool readonly) {
  mUi->noOpRadioButton->setCheckable(readonly);
  mUi->standbyRadioButton->setCheckable(readonly);
  mUi->navigateRadioButton->setCheckable(readonly);
}

void NavigationModeControlTab::applyPressed() {
}

void NavigationModeControlTab::readPacket(boost::shared_ptr<Packet> packet) {
  if (mControlMode)
    return;
  if (packet->instanceOfMessage()) {
    const Message& message = packet->messageCast();
    if (message.instanceOf<NavigationModeControl>()) {
      enableFields(true);
      const NavigationModeControl& msg =
        message.typeCast<NavigationModeControl>();
      switch (msg.mNavigationMode) {
        case 0:
          mUi->noOpRadioButton->setChecked(true);
          break;
        case 1:
          mUi->standbyRadioButton->setChecked(true);
          break;
        case 2:
          mUi->navigateRadioButton->setChecked(true);
          break;
        default:
          break;
      }
    }
  }
}

void NavigationModeControlTab::deviceConnected(bool connected) {
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
