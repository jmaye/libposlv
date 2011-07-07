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

#include "base/TCPConnectionClient.h"

#include <cstring>
#include <cmath>
#include <arpa/inet.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

TCPConnectionClient::TCPConnectionClient(const std::string& serverIP, uint16_t
  port, double timeout) :
  mServerIP(serverIP),
  mPort(port),
  mTimeout(timeout),
  mSocket(0) {
}

TCPConnectionClient::TCPConnectionClient(const TCPConnectionClient& other) {
}

TCPConnectionClient& TCPConnectionClient::operator =
  (const TCPConnectionClient& other) {
  return *this;
}

TCPConnectionClient::~TCPConnectionClient() {
  close();
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void TCPConnectionClient::read(std::istream& stream) {
}

void TCPConnectionClient::write(std::ostream& stream) const {
  stream << "server IP: " << mServerIP << std::endl
    << "port: " << mPort << std::endl
    << "timeout: " << mTimeout;
}

void TCPConnectionClient::read(std::ifstream& stream) {
}

void TCPConnectionClient::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

uint16_t TCPConnectionClient::getPort() const {
  return mPort;
}

const std::string& TCPConnectionClient::getServerIP() const {
  return mServerIP;
}

void TCPConnectionClient::setTimeout(double timeout) {
  mTimeout = timeout;
}

double TCPConnectionClient::getTimeout() const {
  return mTimeout;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void TCPConnectionClient::open() throw (IOException) {
  mSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (mSocket < 0)
    throw IOException("TCPConnectionClient::open(): socket creation failed");

  struct sockaddr_in server;
  memset(&server, 0, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(mServerIP.c_str());
  server.sin_port = htons(mPort);
  if (connect(mSocket, (const struct sockaddr*)&server, sizeof(server)) == -1)
    throw IOException("TCPConnectionClient::open(): socket connection failed");
}

void TCPConnectionClient::close() throw (IOException) {
  if (mSocket != 0) {
    ssize_t res = ::close(mSocket);
    if (res < 0)
      throw IOException("TCPConnectionClient::close(): socket closing failed");
  }
  mSocket = 0;
}

bool TCPConnectionClient::isOpen() const {
  return (mSocket != 0);
}

void TCPConnectionClient::readBuffer(uint8_t* au8Buffer, ssize_t nbBytes)
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
      throw IOException("TCPConnectionClient::readBuffer(): read select failed");
    if (FD_ISSET(mSocket, &readFlags)) {
      FD_CLR(mSocket, &readFlags);
      res = ::read(mSocket, &au8Buffer[bytesRead], nbBytes - bytesRead);
      if (res < 0)
        throw IOException("TCPConnectionClient::readBuffer(): read failed");
      bytesRead += res;
    }
    else
      throw IOException("TCPConnectionClient::readBuffer(): read timeout");
  }
}

void TCPConnectionClient::writeBuffer(const uint8_t* au8Buffer, ssize_t nbBytes)
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
      throw IOException("TCPConnectionClient::writeBuffer(): write select failed");
    if (FD_ISSET(mSocket, &writeFlags)) {
      FD_CLR(mSocket, &writeFlags);
      res = ::write(mSocket, &au8Buffer[bytesWritten], nbBytes - bytesWritten);
      if (res < 0)
        throw IOException("TCPConnectionClient::writeBuffer(): write failed");
      bytesWritten += res;
    }
    else
      throw IOException("TCPConnectionClient::writeBuffer(): write timeout");
  }
}
