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

#include "sensor/POSLVComUDP.h"

#include "com/UDPConnectionServer.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

POSLVComUDP::POSLVComUDP(UDPConnectionServer& connection) :
    mConnection(connection) {
}

POSLVComUDP::~POSLVComUDP() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

UDPConnectionServer& POSLVComUDP::getConnection() {
  return mConnection;
}

const UDPConnectionServer& POSLVComUDP::getConnection() const {
  return mConnection;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void POSLVComUDP::read(char* buffer, size_t numBytes) {
  if (mBytesBuffer.size() < (size_t)numBytes) {
    ssize_t numBytesRead = mConnection.read(mPacketsBuffer,
      mMaxPacketSize);
    for (size_t i = 0; i < (size_t)numBytesRead; ++i)
      mBytesBuffer.push(mPacketsBuffer[i]);
  }
  for (size_t i = 0; i < (size_t)numBytes; ++i) {
    buffer[i] = mBytesBuffer.front();
    mBytesBuffer.pop();
  }
}
