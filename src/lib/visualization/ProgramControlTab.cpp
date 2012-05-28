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

#include "types/Message.h"
#include "types/Packet.h"
#include "types/ProgramControl.h"

#include "ui_ProgramControlTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ProgramControlTab::ProgramControlTab() :
    mUi(new Ui_ProgramControlTab()),
    mControlMode(false) {
  mUi->setupUi(this);
  setReadOnlyFields(true);
}

ProgramControlTab::~ProgramControlTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void ProgramControlTab::enableFields(bool enable) {
  mUi->connectButton->setEnabled(enable);
  mUi->disconnectButton->setEnabled(enable);
  mUi->resetPOSButton->setEnabled(enable);
  mUi->resetGAMSButton->setEnabled(enable);
  mUi->shutdownButton->setEnabled(enable);
}

void ProgramControlTab::setReadOnlyFields(bool readonly) {
  mUi->connectButton->setCheckable(readonly);
  mUi->disconnectButton->setCheckable(readonly);
  mUi->resetPOSButton->setCheckable(readonly);
  mUi->resetGAMSButton->setCheckable(readonly);
  mUi->shutdownButton->setCheckable(readonly);
}
