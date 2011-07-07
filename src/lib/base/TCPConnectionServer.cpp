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

#include "base/TCPConnectionServer.h"

#include <arpa/inet.h>
#include <cstring>
#include <cmath>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

TCPConnectionServer::TCPConnectionServer(uint16_t port, double timeout) :
  mPort(port),
  mTimeout(timeout),
  mSocket(0) {
}

TCPConnectionServer::TCPConnectionServer(const TCPConnectionServer& other) {
}

TCPConnectionServer& TCPConnectionServer::operator =
  (const TCPConnectionServer& other) {
  return *this;
}

TCPConnectionServer::~TCPConnectionServer() {
  close();
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void TCPConnectionServer::read(std::istream& stream) {
}

void TCPConnectionServer::write(std::ostream& stream) const {
  stream << "port: " << mPort << std::endl
    << "timeout: " << mTimeout;
}

void TCPConnectionServer::read(std::ifstream& stream) {
}

void TCPConnectionServer::write(std::ofstream& stream) const {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

uint16_t TCPConnectionServer::getPort() const {
  return mPort;
}

void TCPConnectionServer::setTimeout(double timeout) {
  mTimeout = timeout;
}

double TCPConnectionServer::getTimeout() const {
  return mTimeout;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void TCPConnectionServer::open() throw (IOException) {
  mSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (mSocket == -1)
    throw IOException("TCPConnectionServer::open(): socket creation failed");

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(mPort);
  if (bind(mSocket, (struct sockaddr*)&server, sizeof(struct sockaddr_in)) ==
    -1)
    throw IOException("TCPConnectionServer::open(): binding failed");
  if (listen(mSocket, 5) == -1)
    throw IOException("TCPConnectionServer::open(): listen failed");
}

void TCPConnectionServer::close() throw (IOException) {
  if (mSocket != 0) {
    ssize_t res = ::close(mSocket);
    if (res < 0)
      throw IOException("TCPConnectionServer::close(): socket closing failed");
  }
  mSocket = 0;
}

bool TCPConnectionServer::isOpen() const {
  return (mSocket != 0);
}

void TCPConnectionServer::readBuffer(uint8_t* au8Buffer, ssize_t nbBytes)
  throw (IOException) {
//newsockfd = accept(sockfd,
//                 (struct sockaddr *) &cli_addr,
//                 &clilen);
//  if (isOpen() == false)
//    open();
//  double intPart;
//  double fracPart = modf(mTimeout, &intPart);
//  struct timeval waitd;
//  waitd.tv_sec = intPart;
//  waitd.tv_usec = fracPart * 1e6;
//  fd_set readFlags;
//  FD_ZERO(&readFlags);
//  FD_SET(mSocket, &readFlags);
//  ssize_t res = select(mSocket + 1, &readFlags, (fd_set*)0, (fd_set*)0, &waitd);
//  if(res < 0)
//    throw IOException("TCPConnectionServer::readBuffer(): read select failed");
//  if (FD_ISSET(mSocket, &readFlags)) {
//    FD_CLR(mSocket, &readFlags);
//    struct sockaddr_in client;
//    socklen_t size;
//    if (recvfrom(mSocket, au8Buffer, nbBytes, 0, (struct sockaddr*)&client,
//      &size) != nbBytes)
//      throw IOException("TCPConnectionServer::readBuffer(): read failed");
//  }
//  else
//    throw IOException("TCPConnectionServer::readBuffer(): read timeout");
}

void TCPConnectionServer::writeBuffer(const uint8_t* au8Buffer, ssize_t nbBytes)
  throw (IOException) {
//  if (isOpen() == false)
//    open();
//  double intPart;
//  double fracPart = modf(mTimeout, &intPart);
//  struct timeval waitd;
//  waitd.tv_sec = intPart;
//  waitd.tv_usec = fracPart * 1e6;
//  fd_set writeFlags;
//  FD_ZERO(&writeFlags);
//  FD_SET(mSocket, &writeFlags);
//  ssize_t res = select(mSocket + 1, (fd_set*)0, &writeFlags, (fd_set*)0,
//    &waitd);
//  if(res < 0)
//    throw IOException("TCPConnectionServer::writeBuffer(): write select failed");
//  if (FD_ISSET(mSocket, &writeFlags)) {
//    FD_CLR(mSocket, &writeFlags);
//    //TODO: MODIFY THIS PART
//    struct sockaddr_in client;
//    if (sendto(mSocket, au8Buffer, nbBytes, 0, (const struct sockaddr*)&client,
//      sizeof(struct sockaddr_in)) != nbBytes)
//      throw IOException("TCPConnectionServer::writeBuffer(): write failed");
//  }
//  else
//    throw IOException("TCPConnectionServer::writeBuffer(): write timeout");
}
