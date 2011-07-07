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

#include "base/UDPConnectionServer.h"

#include <arpa/inet.h>
#include <cstring>
#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

UDPConnectionServer::UDPConnectionServer(uint16_t port, double timeout) :
  mPort(port),
  mTimeout(timeout),
  mSocket(0) {
}

UDPConnectionServer::UDPConnectionServer(const UDPConnectionServer& other) {
}

UDPConnectionServer& UDPConnectionServer::operator =
  (const UDPConnectionServer& other) {
  return *this;
}


UDPConnectionServer::~UDPConnectionServer() {
  close();
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void UDPConnectionServer::read(std::istream& stream) {
}

void UDPConnectionServer::write(std::ostream& stream) const {
  stream << "port: " << mPort << std::endl
    << "timeout: " << mTimeout;
}

void UDPConnectionServer::read(std::ifstream& stream) {
}

void UDPConnectionServer::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

uint16_t UDPConnectionServer::getPort() const {
  return mPort;
}

void UDPConnectionServer::setTimeout(double timeout) {
  mTimeout = timeout;
}

double UDPConnectionServer::getTimeout() const {
  return mTimeout;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void UDPConnectionServer::open() throw (IOException) {
  mSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (mSocket < 0)
    throw IOException("UDPConnectionServer::open(): socket creation failed");

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(mPort);
  if (bind(mSocket, (struct sockaddr*)&server, sizeof(struct sockaddr_in)) ==
    -1)
    throw IOException("UDPConnectionServer::open(): binding failed");
}

void UDPConnectionServer::close() throw (IOException) {
  if (mSocket != 0) {
    ssize_t res = ::close(mSocket);
    if (res < 0)
      throw IOException("UDPConnectionServer::close(): socket closing failed");
  }
  mSocket = 0;
}

bool UDPConnectionServer::isOpen() const {
  return (mSocket != 0);
}

void UDPConnectionServer::readBuffer(uint8_t* au8Buffer, ssize_t nbBytes)
  throw (IOException) {
  if (isOpen() == false)
    open();
  ssize_t bytesRead = 0;
  while (bytesRead != nbBytes) {
    double intPart;
    double fracPart = modf(mTimeout, &intPart);
    struct timeval waitd;
    waitd.tv_sec = intPart;
    waitd.tv_usec = fracPart * 1e6;
    fd_set readFlags;
    FD_ZERO(&readFlags);
    FD_SET(mSocket, &readFlags);
    ssize_t res = select(mSocket + 1, &readFlags, (fd_set*)0, (fd_set*)0,
      &waitd);
    if(res < 0)
      throw IOException("UDPConnectionServer::readBuffer(): read select failed");
    if (FD_ISSET(mSocket, &readFlags)) {
      FD_CLR(mSocket, &readFlags);
      struct sockaddr_in client;
      socklen_t size;
      res = recvfrom(mSocket, &au8Buffer[bytesRead], nbBytes - bytesRead, 0,
        (struct sockaddr*)&client, &size);
      if (res < 0)
        throw IOException("UDPConnectionServer::readBuffer(): read failed");
      bytesRead += res;
    }
    else
      throw IOException("UDPConnectionServer::readBuffer(): read timeout");
  }
}

void UDPConnectionServer::writeBuffer(const uint8_t* au8Buffer, ssize_t nbBytes)
  throw (IOException) {
  if (isOpen() == false)
    open();
  ssize_t bytesWritten = 0;
  while (bytesWritten != nbBytes) {
    double intPart;
    double fracPart = modf(mTimeout, &intPart);
    struct timeval waitd;
    waitd.tv_sec = intPart;
    waitd.tv_usec = fracPart * 1e6;
    fd_set writeFlags;
    FD_ZERO(&writeFlags);
    FD_SET(mSocket, &writeFlags);
    ssize_t res = select(mSocket + 1, (fd_set*)0, &writeFlags, (fd_set*)0,
      &waitd);
    if(res < 0)
      throw IOException("UDPConnectionServer::writeBuffer(): write select failed");
    if (FD_ISSET(mSocket, &writeFlags)) {
      FD_CLR(mSocket, &writeFlags);
      //TODO: MODIFY THIS PART
      struct sockaddr_in client;
      res = sendto(mSocket, &au8Buffer[bytesWritten], nbBytes - bytesWritten, 0,
        (const struct sockaddr*)&client, sizeof(struct sockaddr_in));
      if (res < 0)
        throw IOException("UDPConnectionServer::writeBuffer(): write failed");
      bytesWritten += res;
    }
    else
      throw IOException("UDPConnectionServer::writeBuffer(): write timeout");
  }
}
