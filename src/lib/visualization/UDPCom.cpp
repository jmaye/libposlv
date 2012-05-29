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

#include "visualization/UDPCom.h"

#include "sensor/POSLVComUDP.h"
#include "com/UDPConnectionServer.h"
#include "types/Packet.h"
#include "exceptions/IOException.h"
#include "exceptions/SystemException.h"
#include "exceptions/TypeCreationException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

UDPCom::UDPCom(POSLVComUDP& device, double pollingTime) :
    mDevice(device),
    mPollingTime(pollingTime) {
  connect(&mTimer, SIGNAL(timeout()), this, SLOT(timerTimeout()));
  mTimer.setInterval(pollingTime);
  mTimer.start();
}

UDPCom::~UDPCom() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

double UDPCom::getPollingTime() const {
  return mPollingTime;
}

void UDPCom::setPollingTime(double pollingTime) {
  mPollingTime = pollingTime;
  mTimer.setInterval(pollingTime);
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void UDPCom::timerTimeout() {
  try {
    if (!mDevice.getConnection().isOpen())
      mDevice.getConnection().open();
    boost::shared_ptr<Packet> packet = mDevice.readPacket();
    emit readPacket(packet);
    emit deviceConnected(true);
  }
  catch (IOException& e) {
    std::cerr << e.what() << std::endl;
    emit deviceConnected(false);
  }
  catch (SystemException& e) {
    std::cerr << e.what() << std::endl;
    emit deviceConnected(false);
  }
  catch (TypeCreationException<unsigned short>& e) {
    //std::cerr << e.what() << std::endl;
    emit deviceConnected(true);
  }
}
