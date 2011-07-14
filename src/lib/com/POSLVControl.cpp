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

#include "com/POSLVControl.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

POSLVControl::POSLVControl(const std::string& serverIP, uint16_t port,
  double timeout) :
  TCPConnectionClient(serverIP, port, timeout) {
}

POSLVControl::POSLVControl(const POSLVControl& other) :
  TCPConnectionClient(other) {
}

POSLVControl& POSLVControl::operator = (const POSLVControl& other) {
  this->TCPConnectionClient::operator=(other);
  return *this;
}

POSLVControl::~POSLVControl() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void POSLVControl::readBuffer(uint8_t* au8Buffer, ssize_t nbBytes) {
  TCPConnectionClient::readBuffer(au8Buffer, nbBytes);
}

void POSLVControl::writeBuffer(const uint8_t* au8Buffer, ssize_t nbBytes) {
  TCPConnectionClient::writeBuffer(au8Buffer, nbBytes);
}

const Acknowledge& POSLVControl::sendControl(const Message& message)
  throw (IOException) {
  sendMessage(message);
  const Message* ret = readMessage();
  if (ret->instanceOf<Acknowledge>() == false)
   throw IOException("POSLVControl:sendControl(): wrong acknowledge");
  return ret->typeCast<Acknowledge>();
}
