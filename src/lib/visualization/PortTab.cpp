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

#include "visualization/PortTab.h"

#include <sstream>

#include "types/DisplayPortControl.h"
#include "types/PrimaryDataPortControl.h"
#include "types/SecondaryDataPortControl.h"
#include "types/COMPortSetup.h"
#include "types/Message.h"
#include "types/Packet.h"

#include "ui_PortTab.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PortTab::PortTab() :
    mUi(new Ui_PortTab()) {
  mUi->setupUi(this);
  mBaudrateMap[0] = 2400;
  mBaudrateMap[1] = 4800;
  mBaudrateMap[2] = 9600;
  mBaudrateMap[3] = 19200;
  mBaudrateMap[4] = 38400;
  mBaudrateMap[5] = 57600;
  mBaudrateMap[6] = 76800;
  mBaudrateMap[7] = 115200;
  mParityMap[0] ="no parity";
  mParityMap[1] ="even parity";
  mParityMap[2] ="odd parity";
  mParityMap[3] ="Reserved";
  mStopMap[0] ="7 data, 1 stop";
  mStopMap[1] ="7 data, 2 stop";
  mStopMap[2] ="8 data, 1 stop";
  mStopMap[3] ="8 data, 2 stop";
  mFlowMap[0] ="none";
  mFlowMap[1] ="hardware";
  mFlowMap[2] ="XON/XOFF";
  mInputMap[0] ="No input";
  mInputMap[1] ="Auxiliary 1 GPS";
  mInputMap[2] ="Auxiliary 2 GPS";
  mInputMap[3] ="Reserved";
  mInputMap[4] ="Base GPS 1";
  mInputMap[5] ="Base GPS 2";
  mOutputMap[0] ="No output";
  mOutputMap[1] ="NMEA messages";
  mOutputMap[2] ="Real-time binary";
  mOutputMap[3] ="Base GPS 1";
  mOutputMap[4] ="Base GPS 2";
}

PortTab::~PortTab() {
  delete mUi;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void PortTab::readPacket(boost::shared_ptr<Packet> packet) {
  if (packet->instanceOfMessage()) {
    const Message& message = packet->messageCast();
    if (message.instanceOf<DisplayPortControl>()) {
      const DisplayPortControl& msg = message.typeCast<DisplayPortControl>();
      std::stringstream portStream;
      for (size_t i = 0; i < msg.mNumGroups; i++)
        portStream << msg.mGroupsIDVector[i] << std::endl;
      mUi->displayPortText->setText(portStream.str().c_str());
    }
    if (message.instanceOf<PrimaryDataPortControl>()) {
      const PrimaryDataPortControl& msg =
        message.typeCast<PrimaryDataPortControl>();
      std::stringstream portStream;
      for (size_t i = 0; i < msg.mNumGroups; i++)
        portStream << msg.mGroupsIDVector[i] << std::endl;
      portStream << "Data Rate: " << msg.mOutputRate << " [Hz]" << std::endl;
      mUi->primDataPortText->setText(portStream.str().c_str());
    }
    if (message.instanceOf<SecondaryDataPortControl>()) {
      const SecondaryDataPortControl& msg =
        message.typeCast<SecondaryDataPortControl>();
      std::stringstream portStream;
      for (size_t i = 0; i < msg.mNumGroups; i++)
        portStream << msg.mGroupsIDVector[i] << std::endl;
      portStream << "Data Rate: " << msg.mOutputRate << " [Hz]" << std::endl;
      mUi->secDataPortText->setText(portStream.str().c_str());
    }
    if (message.instanceOf<COMPortSetup>()) {
      const COMPortSetup& msg = message.typeCast<COMPortSetup>();
      mUi->com1BaudSpinBox->setValue(mBaudrateMap[msg.mpParameters[0].
        mBaudrate]);
      mUi->com2BaudSpinBox->setValue(mBaudrateMap[msg.mpParameters[1].
        mBaudrate]);
      mUi->com1ParityText->setText(mParityMap[msg.mpParameters[0].
        mParity].c_str());
      mUi->com2ParityText->setText(mParityMap[msg.mpParameters[1].
        mParity].c_str());
      mUi->com1StopText->setText(mStopMap[msg.mpParameters[0].
        mDataStopBits].c_str());
      mUi->com2StopText->setText(mStopMap[msg.mpParameters[1].
        mDataStopBits].c_str());
      mUi->com1FlowText->setText(mFlowMap[msg.mpParameters[0].
        mFlowControl].c_str());
      mUi->com2FlowText->setText(mFlowMap[msg.mpParameters[1].
        mFlowControl].c_str());
      mUi->com1InputText->setText(mInputMap[msg.mpParameters[0].
        mInputSelect].c_str());
      mUi->com2InputText->setText(mInputMap[msg.mpParameters[1].
        mInputSelect].c_str());
      mUi->com1OutputText->setText(mOutputMap[msg.mpParameters[0].
        mOutputSelect].c_str());
      mUi->com2OutputText->setText(mOutputMap[msg.mpParameters[1].
        mOutputSelect].c_str());
    }
  }
}
