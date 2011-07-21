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

#include "com/BinaryReader.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

BinaryReader::BinaryReader() {
}

BinaryReader::BinaryReader(const BinaryReader& other) {
}

BinaryReader& BinaryReader::operator = (const BinaryReader& other) {
  if (this != &other) {
  }
  return *this;
}

BinaryReader::~BinaryReader() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

BinaryReader& BinaryReader::operator >> (int8_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int8_t));
  return *this;
}

BinaryReader& BinaryReader::operator >> (uint8_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint8_t));
  return *this;
}

BinaryReader& BinaryReader::operator >> (int16_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int16_t));
  return *this;
}

BinaryReader& BinaryReader::operator >> (uint16_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint16_t));
  return *this;
}

BinaryReader& BinaryReader::operator >> (int32_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int32_t));
  return *this;
}

BinaryReader& BinaryReader::operator >> (uint32_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint32_t));
  return *this;
}

BinaryReader& BinaryReader::operator >> (int64_t& value) {
  readBuffer((uint8_t*)&value, sizeof(int64_t));
  return *this;
}

BinaryReader& BinaryReader::operator >> (uint64_t& value) {
  readBuffer((uint8_t*)&value, sizeof(uint64_t));
  return *this;
}

BinaryReader& BinaryReader::operator >> (float& value) {
  readBuffer((uint8_t*)&value, sizeof(float));
  return *this;
}

BinaryReader& BinaryReader::operator >> (double& value) {
  readBuffer((uint8_t*)&value, sizeof(double));
  return *this;
}
