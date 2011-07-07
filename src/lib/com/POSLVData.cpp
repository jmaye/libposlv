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

#include "com/POSLVData.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

POSLVData::POSLVData(const std::string& serverIP, uint16_t port,
  double timeout) :
  TCPConnectionClient(serverIP, port, timeout) {
}

POSLVData::POSLVData(const POSLVData& other) :
  TCPConnectionClient(other) {
}

POSLVData& POSLVData::operator = (const POSLVData& other) {
  this->TCPConnectionClient::operator=(other);
  return *this;
}

POSLVData::~POSLVData() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void POSLVData::readBuffer(uint8_t* au8Buffer, ssize_t nbBytes) {
  TCPConnectionClient::readBuffer(au8Buffer, nbBytes);
}
