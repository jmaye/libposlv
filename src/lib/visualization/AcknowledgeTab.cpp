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

#include "visualization/AcknowledgeTab.h"

#include <QtGui/QLineEdit>
#include <QtGui/QSpinBox>

#include "types/Packet.h"
#include "types/Message.h"
#include "types/Acknowledge.h"

#include "ui_AcknowledgeTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

AcknowledgeTab::AcknowledgeTab() :
    mUi(new Ui_AcknowledgeTab()) {
  mUi->setupUi(this);
  mStatusMsg[0] = "Not applicable";
  mStatusMsg[1] = "Message accepted";
  mStatusMsg[2] = "Message accepted - too long";
  mStatusMsg[3] = "Message accepted - too short";
  mStatusMsg[4] = "Message parameter error";
  mStatusMsg[5] = "Not applicable in current state";
  mStatusMsg[6] = "Data not available";
  mStatusMsg[7] = "Message start error";
  mStatusMsg[8] = "Message end error";
  mStatusMsg[9] = "Byte count error";
  mStatusMsg[10] = "Checksum error";
}

AcknowledgeTab::~AcknowledgeTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void AcknowledgeTab::readPacket(boost::shared_ptr<Packet> packet) {
    if (packet->instanceOfMessage())
      if (packet->messageCast().instanceOf<Acknowledge>()) {
        const Acknowledge& msg = packet->messageCast().typeCast<Acknowledge>();
        mUi->ackWidget->insertRow(mUi->ackWidget->rowCount());
        QSpinBox* transactionNumber = new QSpinBox;
        transactionNumber->setReadOnly(true);
        transactionNumber->setValue(msg.mTransactionNumber);
        transactionNumber->setButtonSymbols(QAbstractSpinBox::NoButtons);
        mUi->ackWidget->setCellWidget(mUi->ackWidget->rowCount() - 1, 0,
          transactionNumber);
        QSpinBox* id = new QSpinBox;
        id->setReadOnly(true);
        id->setValue(msg.mID);
        id->setButtonSymbols(QAbstractSpinBox::NoButtons);
        mUi->ackWidget->setCellWidget(mUi->ackWidget->rowCount() - 1, 1, id);
        QLineEdit* response = new QLineEdit;
        response->setReadOnly(true);
        response->setText(mStatusMsg[msg.mResponseCode].c_str());
        mUi->ackWidget->setCellWidget(mUi->ackWidget->rowCount() - 1, 2,
          response);
        QLineEdit* status = new QLineEdit;
        status->setReadOnly(true);
        std::string statusString;
        if (msg.mNewParamsStatus == 0)
          statusString = "No change in parameters";
        else if (msg.mNewParamsStatus == 1)
          statusString = "Some parameters changed";
        status->setText(statusString.c_str());
        mUi->ackWidget->setCellWidget(mUi->ackWidget->rowCount() - 1, 3,
          status);
        QLineEdit* name = new QLineEdit;
        name->setReadOnly(true);
        name->setText(reinterpret_cast<const char*>(msg.mParameterName));
        mUi->ackWidget->setCellWidget(mUi->ackWidget->rowCount() - 1, 4, name);
      }
}

void AcknowledgeTab::clearPressed() {
  while (mUi->ackWidget->rowCount())
    mUi->ackWidget->removeRow(mUi->ackWidget->rowCount() - 1);
}
