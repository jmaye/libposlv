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

#include "com/POSLVDisplay.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

POSLVDisplay::POSLVDisplay(uint16_t port, double timeout) :
  UDPConnectionServer(port, timeout) {
}

POSLVDisplay::POSLVDisplay(const POSLVDisplay& other) :
  UDPConnectionServer(other) {
}

POSLVDisplay& POSLVDisplay::operator = (const POSLVDisplay& other) {
  this->UDPConnectionServer::operator=(other);
  return *this;
}

POSLVDisplay::~POSLVDisplay() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void POSLVDisplay::readBuffer(uint8_t* au8Buffer, ssize_t nbBytes) {
  if (mBytesBuffer.size() < (size_t)nbBytes) {
    ssize_t numBytes = UDPConnectionServer::readBuffer(mPacketsBuffer,
      mMaxPacketSize);
    for (size_t i = 0; i < (size_t)numBytes; i++)
      mBytesBuffer.push(mPacketsBuffer[i]);
  }
  for (size_t i = 0; i < (size_t)nbBytes; i++) {
    au8Buffer[i] = mBytesBuffer.front();
    mBytesBuffer.pop();
  }
}
