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

#include "visualization/AidingSensorInstallParamsTab.h"

#include "types/Message.h"
#include "types/Packet.h"
#include "types/AidingSensorInstallParams.h"

#include "ui_AidingSensorInstallParamsTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

AidingSensorInstallParamsTab::AidingSensorInstallParamsTab() :
    mUi(new Ui_AidingSensorInstallParamsTab()),
    mControlMode(false) {
  mUi->setupUi(this);
  setReadOnlyFields(true);
}

AidingSensorInstallParamsTab::~AidingSensorInstallParamsTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void AidingSensorInstallParamsTab::enableFields(bool enable) {
  mUi->dmiScaleSpinBox->setEnabled(enable);
  mUi->dmiXSpinBox->setEnabled(enable);
  mUi->dmiYSpinBox->setEnabled(enable);
  mUi->dmiZSpinBox->setEnabled(enable);
}

void AidingSensorInstallParamsTab::setReadOnlyFields(bool readonly) {
  mUi->dmiScaleSpinBox->setReadOnly(readonly);
  mUi->dmiXSpinBox->setReadOnly(readonly);
  mUi->dmiYSpinBox->setReadOnly(readonly);
  mUi->dmiZSpinBox->setReadOnly(readonly);
}

void AidingSensorInstallParamsTab::applyPressed() {
}

void AidingSensorInstallParamsTab::readPacket(boost::shared_ptr<Packet>
    packet) {
  if (mControlMode)
    return;
  if (packet->instanceOfMessage()) {
    const Message& message = packet->messageCast();
    if (message.instanceOf<AidingSensorInstallParams>()) {
      enableFields(true);
      const AidingSensorInstallParams& msg =
        message.typeCast<AidingSensorInstallParams>();
      mUi->dmiScaleSpinBox->setValue(msg.mDMIScaleFactor);
      mUi->dmiXSpinBox->setValue(msg.mRefDMIX);
      mUi->dmiYSpinBox->setValue(msg.mRefDMIY);
      mUi->dmiZSpinBox->setValue(msg.mRefDMIZ);
    }
  }
}
