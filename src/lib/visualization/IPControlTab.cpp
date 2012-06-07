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

#include "visualization/IPControlTab.h"

#include "types/Message.h"
#include "types/Packet.h"
#include "types/SetPOSIPAddress.h"
#include "base/Factory.h"

#include "ui_IPControlTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

IPControlTab::IPControlTab() :
    mUi(new Ui_IPControlTab()),
    mControlMode(false) {
  mUi->setupUi(this);
  setReadOnlyFields(true);
}

IPControlTab::~IPControlTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void IPControlTab::enableFields(bool enable) {
  mUi->net1SpinBox->setEnabled(enable);
  mUi->net2SpinBox->setEnabled(enable);
  mUi->net3SpinBox->setEnabled(enable);
  mUi->net4SpinBox->setEnabled(enable);
  mUi->subnet1SpinBox->setEnabled(enable);
  mUi->subnet2SpinBox->setEnabled(enable);
  mUi->subnet3SpinBox->setEnabled(enable);
  mUi->subnet4SpinBox->setEnabled(enable);
}

void IPControlTab::setReadOnlyFields(bool readonly) {
  mUi->net1SpinBox->setReadOnly(readonly);
  mUi->net2SpinBox->setReadOnly(readonly);
  mUi->net3SpinBox->setReadOnly(readonly);
  mUi->net4SpinBox->setReadOnly(readonly);
  mUi->subnet1SpinBox->setReadOnly(readonly);
  mUi->subnet2SpinBox->setReadOnly(readonly);
  mUi->subnet3SpinBox->setReadOnly(readonly);
  mUi->subnet4SpinBox->setReadOnly(readonly);
}

void IPControlTab::applyPressed() {
  static uint16_t transactionNumber = 0;
  std::shared_ptr<Packet> packet(
    Factory<uint16_t, Message>::getInstance().create(32));
  SetPOSIPAddress& msg =
    packet->messageCast().typeCast<SetPOSIPAddress>();
  msg.mNetworkPart1 = mUi->net1SpinBox->value();
  msg.mNetworkPart2 = mUi->net2SpinBox->value();
  msg.mHostPart1 = mUi->net3SpinBox->value();
  msg.mHostPart2 = mUi->net4SpinBox->value();
  msg.mSubNetworkPart1 = mUi->subnet1SpinBox->value();
  msg.mSubNetworkPart2 = mUi->subnet2SpinBox->value();
  msg.mSubHostPart1 = mUi->subnet3SpinBox->value();
  msg.mSubHostPart2 = mUi->subnet4SpinBox->value();
  msg.mTransactionNumber = transactionNumber++;
  emit writePacket(packet);
}

void IPControlTab::readPacket(std::shared_ptr<Packet> packet) {
  if (mControlMode)
    return;
  if (packet->instanceOfMessage()) {
    const Message& message = packet->messageCast();
    if (message.instanceOf<SetPOSIPAddress>()) {
      enableFields(true);
      const SetPOSIPAddress& msg = message.typeCast<SetPOSIPAddress>();
      mUi->net1SpinBox->setValue(msg.mNetworkPart1);
      mUi->net2SpinBox->setValue(msg.mNetworkPart2);
      mUi->net3SpinBox->setValue(msg.mHostPart1);
      mUi->net4SpinBox->setValue(msg.mHostPart2);
      mUi->subnet1SpinBox->setValue(msg.mSubNetworkPart1);
      mUi->subnet2SpinBox->setValue(msg.mSubNetworkPart2);
      mUi->subnet3SpinBox->setValue(msg.mSubHostPart1);
      mUi->subnet4SpinBox->setValue(msg.mSubHostPart2);
    }
  }
}

void IPControlTab::deviceConnected(bool connected) {
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
