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

#include "ui_SaveRestoreControlTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SaveRestoreControlTab::SaveRestoreControlTab() :
    mUi(new Ui_SaveRestoreControlTab()),
    mControlMode(false) {
  mUi->setupUi(this);
  setReadOnlyFields(true);
}

SaveRestoreControlTab::~SaveRestoreControlTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void SaveRestoreControlTab::enableFields(bool enable) {
  mUi->noOpRadioButton->setEnabled(enable);
  mUi->saveRadioButton->setEnabled(enable);
  mUi->restoreNVMRadioButton->setEnabled(enable);
  mUi->restoreFactoryRadioButton->setEnabled(enable);
}

void SaveRestoreControlTab::setReadOnlyFields(bool readonly) {
  mUi->noOpRadioButton->setCheckable(readonly);
  mUi->saveRadioButton->setCheckable(readonly);
  mUi->restoreNVMRadioButton->setCheckable(readonly);
  mUi->restoreFactoryRadioButton->setCheckable(readonly);
}

void SaveRestoreControlTab::applyPressed() {
}

void SaveRestoreControlTab::deviceConnected(bool connected) {
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
