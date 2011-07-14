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

#include "com/POSLVMessageRead.h"

#include "base/Factory.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

POSLVMessageRead::POSLVMessageRead() {
}

POSLVMessageRead::POSLVMessageRead(const POSLVMessageRead& other) {
}

POSLVMessageRead& POSLVMessageRead::operator = (const POSLVMessageRead& other) {
  return *this;
}

POSLVMessageRead::~POSLVMessageRead() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

POSLVMessageRead& POSLVMessageRead::operator >> (int8_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int8_t));
  return *this;
}

POSLVMessageRead& POSLVMessageRead::operator >> (uint8_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint8_t));
  return *this;
}

POSLVMessageRead& POSLVMessageRead::operator >> (int16_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int16_t));
  return *this;
}

POSLVMessageRead& POSLVMessageRead::operator >> (uint16_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint16_t));
  return *this;
}

POSLVMessageRead& POSLVMessageRead::operator >> (int32_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int32_t));
  return *this;
}

POSLVMessageRead& POSLVMessageRead::operator >> (uint32_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint32_t));
  return *this;
}

POSLVMessageRead& POSLVMessageRead::operator >> (int64_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int64_t));
  return *this;
}

POSLVMessageRead& POSLVMessageRead::operator >> (uint64_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint64_t));
  return *this;
}

POSLVMessageRead& POSLVMessageRead::operator >> (float& value) {
  readBuffer((uint8_t*)&value, sizeof(float));
  return *this;
}

POSLVMessageRead& POSLVMessageRead::operator >> (double& value) {
  readBuffer((uint8_t*)&value, sizeof(double));
  return *this;
}

void POSLVMessageRead::readStartMessage() {
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

std::string POSLVMessageRead::readEndMessage() {
  std::string outputString;
  uint8_t control;
  readBuffer(&control, sizeof(uint8_t));
  outputString.push_back(control);
  readBuffer(&control, sizeof(uint8_t));
  outputString.push_back(control);
  return outputString;
}

const Message* POSLVMessageRead::readMessage() throw (IOException) {
  readStartMessage();

  uint16_t messageID;
  *this >> messageID;

  if (Factory<uint16_t, Message>::getInstance().isRegistered(messageID) ==
    false)
    return NULL;

  Message* messageRead =
    Factory<uint16_t, Message>::getInstance().create(messageID);
  *this >> *messageRead;

  uint16_t checksum;
  *this >> checksum;

  if (checksum != messageRead->getChecksum())
    throw IOException("POSLVMessageRead::readGroup(): wrong checksum");

  std::string endString = readEndMessage();
  if (endString != "$#")
    throw IOException("POSLVMessageRead::readGroup(): end of message read failed");

  return messageRead;
}
