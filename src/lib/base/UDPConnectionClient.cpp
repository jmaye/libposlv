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

#include "base/UDPConnectionClient.h"

#include <cstring>
#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

UDPConnectionClient::UDPConnectionClient(const std::string& serverIP, uint16_t
  port, double timeout) :
  mServerIP(serverIP),
  mPort(port),
  mTimeout(timeout),
  mSocket(0) {
  memset(&mServer, 0, sizeof(mServer));
  mServer.sin_family = AF_INET;
  mServer.sin_port = htons(mPort);
  if (inet_aton(mServerIP.c_str(), &mServer.sin_addr) == 0)
    throw IOException("UDPConnectionClient::UDPConnectionClient(): invalid IP address");
}

UDPConnectionClient::UDPConnectionClient(const UDPConnectionClient& other) {
}

UDPConnectionClient& UDPConnectionClient::operator =
  (const UDPConnectionClient& other) {
  return *this;
}

UDPConnectionClient::~UDPConnectionClient() {
  close();
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void UDPConnectionClient::read(std::istream& stream) {
}

void UDPConnectionClient::write(std::ostream& stream) const {
  stream << "server IP: " << mServerIP << std::endl
    << "port: " << mPort << std::endl
    << "timeout: " << mTimeout;
}

void UDPConnectionClient::read(std::ifstream& stream) {
}

void UDPConnectionClient::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

uint16_t UDPConnectionClient::getPort() const {
  return mPort;
}

const std::string& UDPConnectionClient::getServerIP() const {
  return mServerIP;
}

void UDPConnectionClient::setTimeout(double timeout) {
  mTimeout = timeout;
}

double UDPConnectionClient::getTimeout() const {
  return mTimeout;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void UDPConnectionClient::open() throw (IOException) {
  mSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (mSocket < 0)
    throw IOException("UDPConnectionClient::open(): socket creation failed");
}

void UDPConnectionClient::close() throw (IOException) {
  if (mSocket != 0) {
    ssize_t res = ::close(mSocket);
    if (res < 0)
      throw IOException("UDPConnectionClient::close(): socket closing failed");
  }
  mSocket = 0;
}

bool UDPConnectionClient::isOpen() const {
  return (mSocket != 0);
}

void UDPConnectionClient::readBuffer(uint8_t* au8Buffer, ssize_t nbBytes)
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
      throw IOException("UDPConnectionClient::readBuffer(): read select failed");
    if (FD_ISSET(mSocket, &readFlags)) {
      FD_CLR(mSocket, &readFlags);
      struct sockaddr_in server;
      socklen_t size;
      res = recvfrom(mSocket, &au8Buffer[bytesRead], nbBytes - bytesRead, 0,
        (struct sockaddr*)&server, &size);
      if (res < 0)
        throw IOException("UDPConnectionClient::readBuffer(): read failed");
      bytesRead += res;
    }
    else
      throw IOException("UDPConnectionClient::readBuffer(): read timeout");
  }
}

void UDPConnectionClient::writeBuffer(const uint8_t* au8Buffer, ssize_t nbBytes)
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
      throw IOException("UDPConnectionClient::writeBuffer(): write select failed");
    if (FD_ISSET(mSocket, &writeFlags)) {
      FD_CLR(mSocket, &writeFlags);
      res = sendto(mSocket, &au8Buffer[bytesWritten], nbBytes - bytesWritten, 0,
        (const struct sockaddr*)&mServer, sizeof(struct sockaddr_in));
      if (res < 0)
        throw IOException("UDPConnectionClient::writeBuffer(): write failed");
      bytesWritten += res;
    }
    else
      throw IOException("UDPConnectionClient::writeBuffer(): write timeout");
  }
}
