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

#include "base/Factory.h"
#include "types/Acknowledge.h"

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

void POSLVControl::sendMessage(const Message& message) throw (IOException) {
  std::string msgHeader = "$MSG";
  writeBuffer((const uint8_t*)msgHeader.c_str(), msgHeader.size());
  *this << message;
  std::string msgEnd = "$#";
  writeBuffer((const uint8_t*)msgEnd.c_str(), msgEnd.size());

  const Message* msgAck = readMessage();
  if (msgAck == NULL || msgAck->instanceOf<Acknowledge>() == false)
    throw IOException("POSLVControl::sendMessage(): wrong ack return");
  delete msgAck;
}

POSLVControl& POSLVControl::operator >> (int8_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int8_t));
  return *this;
}

POSLVControl& POSLVControl::operator >> (uint8_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint8_t));
  return *this;
}

POSLVControl& POSLVControl::operator >> (int16_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int16_t));
  return *this;
}

POSLVControl& POSLVControl::operator >> (uint16_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint16_t));
  return *this;
}

POSLVControl& POSLVControl::operator >> (int32_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int32_t));
  return *this;
}

POSLVControl& POSLVControl::operator >> (uint32_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint32_t));
  return *this;
}

POSLVControl& POSLVControl::operator >> (int64_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int64_t));
  return *this;
}

POSLVControl& POSLVControl::operator >> (uint64_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint64_t));
  return *this;
}

POSLVControl& POSLVControl::operator >> (float& value) {
  readBuffer((uint8_t*)&value, sizeof(float));
  return *this;
}

POSLVControl& POSLVControl::operator >> (double& value) {
  readBuffer((uint8_t*)&value, sizeof(double));
  return *this;
}

POSLVControl& POSLVControl::operator << (int8_t value) {
  writeBuffer((uint8_t*)&value, sizeof(int8_t));
  return *this;
}

POSLVControl& POSLVControl::operator << (uint8_t value) {
  writeBuffer((uint8_t*)&value, sizeof(uint8_t));
  return *this;
}

POSLVControl& POSLVControl::operator << (int16_t value) {
  writeBuffer((uint8_t*)&value, sizeof(int16_t));
  return *this;
}

POSLVControl& POSLVControl::operator << (uint16_t value) {
  writeBuffer((uint8_t*)&value, sizeof(uint16_t));
  return *this;
}

POSLVControl& POSLVControl::operator << (int32_t value) {
  writeBuffer((uint8_t*)&value, sizeof(int32_t));
  return *this;
}

POSLVControl& POSLVControl::operator << (uint32_t value) {
  writeBuffer((uint8_t*)&value, sizeof(uint32_t));
  return *this;
}

POSLVControl& POSLVControl::operator << (int64_t value) {
  writeBuffer((uint8_t*)&value, sizeof(int64_t));
  return *this;
}

POSLVControl& POSLVControl::operator << (uint64_t value) {
  writeBuffer((uint8_t*)&value, sizeof(uint64_t));
  return *this;
}

POSLVControl& POSLVControl::operator << (float value) {
  writeBuffer((uint8_t*)&value, sizeof(float));
  return *this;
}

POSLVControl& POSLVControl::operator << (double value) {
  writeBuffer((uint8_t*)&value, sizeof(double));
  return *this;
}

void POSLVControl::readStartMessage() {
  uint8_t control;
  readBuffer(&control, sizeof(uint8_t));
  while (true) {
    while (control != '$')
      readBuffer(&control, sizeof(uint8_t));
    readBuffer(&control, sizeof(uint8_t));
    if (control != 'M')
      continue;
    readBuffer(&control, sizeof(uint8_t));
    if (control != 'S')
      continue;
    readBuffer(&control, sizeof(uint8_t));
    if (control != 'G')
      continue;
    break;
  }
}

std::string POSLVControl::readEndMessage() {
  std::string outputString;
  uint8_t control;
  readBuffer(&control, sizeof(uint8_t));
  outputString.push_back(control);
  readBuffer(&control, sizeof(uint8_t));
  outputString.push_back(control);
  return outputString;
}

const Message* POSLVControl::readMessage() throw (IOException) {
  readStartMessage();

  uint16_t msgID;
  *this >> msgID;

  if (Factory<uint16_t, Message>::getInstance().isRegistered(msgID) == false)
    return NULL;

  Message* msgRead = Factory<uint16_t, Message>::getInstance().create(msgID);
  *this >> *msgRead;

  uint16_t checksum;
  *this >> checksum;

  // TODO: Checksum control

  std::string endString = readEndMessage();
  if (endString != "$#")
    throw IOException("POSLVControl::readMessage(): end of group read failed");

  return msgRead;
}
