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

#include "visualization/SecondaryGPSStatusTab.h"

#include "types/SecondaryGPSStatus.h"
#include "types/Group.h"
#include "types/Packet.h"

#include "ui_SecondaryGPSStatusTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

SecondaryGPSStatusTab::SecondaryGPSStatusTab() :
    mUi(new Ui_SecondaryGPSStatusTab()) {
  mUi->setupUi(this);
  mStatusMsg[-1] = "Unknown";
  mStatusMsg[0] = "No data from receiver";
  mStatusMsg[1] = "Horizontal C/A mode";
  mStatusMsg[2] = "3-dimension C/A mode";
  mStatusMsg[3] = "Horizontal DGPS mode";
  mStatusMsg[4] = "3-dimension DGPS mode";
  mStatusMsg[5] = "Float RTK mode";
  mStatusMsg[6] = "Integer wide lane RTK mode";
  mStatusMsg[7] = "Integer narrow lane RTK mode";
  mStatusMsg[8] = "P-code";
  mGPSTypeMsg[0] = "No receiver";
  for (size_t i = 1; i <= 7; i++)
    mGPSTypeMsg[i] = "Reserved";
  mGPSTypeMsg[8] = "Trimble BD112";
  mGPSTypeMsg[9] = "Trimble BD750";
  mGPSTypeMsg[10] = "Reserved";
  mGPSTypeMsg[11] = "Reserved";
  mGPSTypeMsg[12] = "Trimble BD132";
  mGPSTypeMsg[13] = "Trimble BD950";
  mGPSTypeMsg[14] = "Reserved";
  mGPSTypeMsg[15] = "Reserved";
  mGPSTypeMsg[16] = "Trimble BD960";
  mChannelStatusMsg[0] = "L1 idle";
  mChannelStatusMsg[1] = "Reserved";
  mChannelStatusMsg[2] = "L1 acquisition";
  mChannelStatusMsg[3] = "L1 code lock";
  mChannelStatusMsg[4] = "Reserved";
  mChannelStatusMsg[5] = "L1 phase lock";
}

SecondaryGPSStatusTab::~SecondaryGPSStatusTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void SecondaryGPSStatusTab::enableFields(bool enable) {
  mUi->navSecGPSText->setEnabled(enable);
  mUi->satSecGPSSpinBox->setEnabled(enable);
  mUi->secGPSTypeText->setEnabled(enable);
  mUi->geoidalSecGPSSpinBox->setEnabled(enable);
  mUi->hdopSpinBox->setEnabled(enable);
  mUi->vdopSpinBox->setEnabled(enable);
  mUi->dgpsIDSpinBox->setEnabled(enable);
  mUi->corrLatencySpinBox->setEnabled(enable);
  mUi->navLatencySpinBox->setEnabled(enable);
  mUi->weekSpinBox->setEnabled(enable);
  mUi->offsetSpinBox->setEnabled(enable);
}

void SecondaryGPSStatusTab::readPacket(boost::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<SecondaryGPSStatus>()) {
      enableFields(true);
      const SecondaryGPSStatus& msg = group.typeCast<SecondaryGPSStatus>();
      mUi->navSecGPSText->setText(
        mStatusMsg[msg.mNavigationSolutionStatus].c_str());
      mUi->satSecGPSSpinBox->setValue(msg.mNumberOfSVTracked);
      mUi->secGPSTypeText->setText(mGPSTypeMsg[msg.mGPSReceiverType].c_str());
      mUi->geoidalSecGPSSpinBox->setValue(msg.mGeoidalSeparation);
      mUi->hdopSpinBox->setValue(msg.mHDOP);
      mUi->vdopSpinBox->setValue(msg.mVDOP);
      mUi->dgpsIDSpinBox->setValue(msg.mDGPSReferenceID);
      mUi->corrLatencySpinBox->setValue(msg.mDGPSCorrectionLatency);
      mUi->navLatencySpinBox->setValue(msg.mGPSNavigationMessageLatency);
      mUi->weekSpinBox->setValue(msg.mGPSUTCWeekNumber);
      mUi->offsetSpinBox->setValue(msg.mGPSUTCTimeOffset);
      while (mUi->channelsTable->rowCount())
        mUi->channelsTable->removeRow(mUi->channelsTable->rowCount() - 1);
      for (size_t i = 0; i < msg.mChannelNumber; ++i) {
        mUi->channelsTable->insertRow(mUi->channelsTable->rowCount());
        QSpinBox* PRN = new QSpinBox;
        PRN->setReadOnly(true);
        PRN->setValue(msg.mChannelStatusData[i].mSVPRN);
        PRN->setButtonSymbols(QAbstractSpinBox::NoButtons);
        mUi->channelsTable->setCellWidget(mUi->channelsTable->rowCount() - 1, 0,
          PRN);
        QLineEdit* status = new QLineEdit;
        status->setReadOnly(true);
        status->setText(mChannelStatusMsg[
          msg.mChannelStatusData[i].mChannelTrackingStatus].c_str());
        mUi->channelsTable->setCellWidget(mUi->channelsTable->rowCount() - 1, 1,
          status);
        QDoubleSpinBox* azimuth = new QDoubleSpinBox;
        azimuth->setReadOnly(true);
        azimuth->setValue(msg.mChannelStatusData[i].mSVAzimuth);
        azimuth->setButtonSymbols(QAbstractSpinBox::NoButtons);
        mUi->channelsTable->setCellWidget(mUi->channelsTable->rowCount() - 1, 2,
          azimuth);
        QDoubleSpinBox* elevation = new QDoubleSpinBox;
        elevation->setReadOnly(true);
        elevation->setValue(msg.mChannelStatusData[i].mSVElevation);
        elevation->setButtonSymbols(QAbstractSpinBox::NoButtons);
        mUi->channelsTable->setCellWidget(mUi->channelsTable->rowCount() - 1, 3,
          elevation);
        QDoubleSpinBox* l1snr = new QDoubleSpinBox;
        l1snr->setReadOnly(true);
        l1snr->setValue(msg.mChannelStatusData[i].mSVL1SNR);
        l1snr->setButtonSymbols(QAbstractSpinBox::NoButtons);
        mUi->channelsTable->setCellWidget(mUi->channelsTable->rowCount() - 1, 4,
          l1snr);
        QDoubleSpinBox* l2snr = new QDoubleSpinBox;
        l2snr->setReadOnly(true);
        l2snr->setValue(msg.mChannelStatusData[i].mSVL2SNR);
        l2snr->setButtonSymbols(QAbstractSpinBox::NoButtons);
        mUi->channelsTable->setCellWidget(mUi->channelsTable->rowCount() - 1, 5,
          l2snr);
      }
    }
  }
}
