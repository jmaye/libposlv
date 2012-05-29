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

#include "visualization/ProgramControlTab.h"

#include <QtGui/QMessageBox>

#include "types/Message.h"
#include "types/Packet.h"
#include "types/ProgramControl.h"

#include "ui_ProgramControlTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ProgramControlTab::ProgramControlTab() :
    mUi(new Ui_ProgramControlTab()) {
  mUi->setupUi(this);
}

ProgramControlTab::~ProgramControlTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ProgramControlTab::connectPressed() {
  emit connect(true);
}

void ProgramControlTab::disconnectPressed() {
  emit connect(false);
}

void ProgramControlTab::resetPOSPressed() {
}

void ProgramControlTab::resetGAMSPressed() {
}

void ProgramControlTab::shutdownPressed() {
}

void ProgramControlTab::deviceConnected(bool connected) {
  if (connected) {
    mUi->connectButton->setEnabled(false);
    mUi->disconnectButton->setEnabled(true);
    mUi->resetPOSButton->setEnabled(true);
    mUi->resetGAMSButton->setEnabled(true);
    mUi->shutdownButton->setEnabled(true);
    QMessageBox::information(this, "Applanix POS LV View",
      "Device connected in control mode");
  }
  else {
    mUi->connectButton->setEnabled(true);
    mUi->disconnectButton->setEnabled(false);
    mUi->resetPOSButton->setEnabled(false);
    mUi->resetGAMSButton->setEnabled(false);
    mUi->shutdownButton->setEnabled(false);
    QMessageBox::information(this, "Applanix POS LV View",
      "Device disconnected from control mode");
  }
}
