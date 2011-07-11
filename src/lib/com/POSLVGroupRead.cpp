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

#include "com/POSLVGroupRead.h"

#include "base/Factory.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

POSLVGroupRead::POSLVGroupRead() {
}

POSLVGroupRead::POSLVGroupRead(const POSLVGroupRead& other) {
}

POSLVGroupRead& POSLVGroupRead::operator = (const POSLVGroupRead& other) {
  return *this;
}

POSLVGroupRead::~POSLVGroupRead() {

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/}

POSLVGroupRead& POSLVGroupRead::operator >> (int8_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int8_t));
  return *this;
}

POSLVGroupRead& POSLVGroupRead::operator >> (uint8_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint8_t));
  return *this;
}

POSLVGroupRead& POSLVGroupRead::operator >> (int16_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int16_t));
  return *this;
}

POSLVGroupRead& POSLVGroupRead::operator >> (uint16_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint16_t));
  return *this;
}

POSLVGroupRead& POSLVGroupRead::operator >> (int32_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int32_t));
  return *this;
}

POSLVGroupRead& POSLVGroupRead::operator >> (uint32_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint32_t));
  return *this;
}

POSLVGroupRead& POSLVGroupRead::operator >> (int64_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int64_t));
  return *this;
}

POSLVGroupRead& POSLVGroupRead::operator >> (uint64_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint64_t));
  return *this;
}

POSLVGroupRead& POSLVGroupRead::operator >> (float& value) {
  readBuffer((uint8_t*)&value, sizeof(float));
  return *this;
}

POSLVGroupRead& POSLVGroupRead::operator >> (double& value) {
  readBuffer((uint8_t*)&value, sizeof(double));
  return *this;
}

void POSLVGroupRead::readStartGroup() {
  uint8_t control;
  readBuffer(&control, sizeof(uint8_t));
  while (true) {
    while (control != '$')
      readBuffer(&control, sizeof(uint8_t));
    readBuffer(&control, sizeof(uint8_t));
    if (control != 'G')
      continue;
    readBuffer(&control, sizeof(uint8_t));
    if (control != 'R')
      continue;
    readBuffer(&control, sizeof(uint8_t));
    if (control != 'P')
      continue;
    break;
  }
}

std::string POSLVGroupRead::readEndGroup() {
  std::string outputString;
  uint8_t control;
  readBuffer(&control, sizeof(uint8_t));
  outputString.push_back(control);
  readBuffer(&control, sizeof(uint8_t));
  outputString.push_back(control);
  return outputString;
}

const Group* POSLVGroupRead::readGroup() throw (IOException) {
  readStartGroup();

  uint16_t groupID;
  *this >> groupID;

  if (Factory<uint16_t, Group>::getInstance().isRegistered(groupID) == false)
    return NULL;

  Group* groupRead = Factory<uint16_t, Group>::getInstance().create(groupID);
  *this >> *groupRead;

  uint16_t checksum;
  *this >> checksum;

  // TODO: Checksum control

  std::string endString = readEndGroup();
  if (endString != "$#")
    throw IOException("POSLVGroupRead::readGroup(): end of group read failed");

  return groupRead;
}
