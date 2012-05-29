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

#include "visualization/TCPCom.h"

#include "sensor/POSLVComTCP.h"
#include "com/TCPConnectionClient.h"
#include "types/Packet.h"
#include "exceptions/IOException.h"
#include "exceptions/SystemException.h"
#include "exceptions/TypeCreationException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

TCPCom::TCPCom(POSLVComTCP& device) :
    mDevice(device) {
}

TCPCom::~TCPCom() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

//void TCPCom::timerTimeout() {
//  try {
//    if (!mDevice.getConnection().isOpen())
//      mDevice.getConnection().open();
//    boost::shared_ptr<Packet> packet = mDevice.readPacket();
//    emit readPacket(packet);
//    emit deviceConnected(true);
//  }
//  catch (IOException& e) {
//    std::cerr << e.what() << std::endl;
//    emit deviceConnected(false);
//  }
//  catch (SystemException& e) {
//    std::cerr << e.what() << std::endl;
//    emit deviceConnected(false);
//  }
//  catch (TypeCreationException<unsigned short>& e) {
//    //std::cerr << e.what() << std::endl;
//    emit deviceConnected(true);
//  }
//}

void TCPCom::connect(bool connect) {
  try {
    if (connect) {
      mDevice.getConnection().open();
      emit deviceConnected(true);
    }
    else {
      mDevice.getConnection().close();
      emit deviceConnected(false);
    }
  }
  catch (SystemException& e) {
    std::cerr << e.what() << std::endl;
    emit deviceConnected(false);
  }
}

void TCPCom::writePacket(boost::shared_ptr<Packet> packet) {
  try {
    if (!mDevice.getConnection().isOpen())
      mDevice.getConnection().open();
    mDevice.writePacket(packet);
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
}
