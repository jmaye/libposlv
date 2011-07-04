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

#include "com/TCPConnection.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

TCPConnection::TCPConnection(uint16_t port, double timeout) :
  mPort(port),
  mTimeout(timeout),
  mSocket(0) {
}

TCPConnection::~TCPConnection() {
  close();
}

TCPConnection::TCPConnection(const TCPConnection& other) {
}

TCPConnection& TCPConnection::operator = (const TCPConnection& other) {
  return *this;
}

uint16_t TCPConnection::getPort() const {
  return mPort;
}

void TCPConnection::setTimeout(double time) {
  mTimeout = time;
}

double TCPConnection::getTimeout() const {
  return mTimeout;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void TCPConnection::open() throw (IOException) {
  mSocket = socket(AF_INET, SOCK_DGRAM, 0);
  if (mSocket == -1)
    throw IOException("TCPConnection::open(): Socket creation failed");

  struct sockaddr_in server;
  memset(&server, 0, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_port = htons(mPort);
  server.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(mSocket, (const sockaddr*)&server, sizeof(struct sockaddr)) == -1)
    throw IOException("TCPConnection::open: Socket binding failed");
}

void TCPConnection::close() throw(IOException) {
  if (mSocket != 0) {
    ssize_t res = ::close(mSocket);
    if (res == -1)
      throw IOException("TCPConnection::close(): Socket closing failed");
  }
  mSocket = 0;
}

bool TCPConnection::isOpen() const {
  return (mSocket != 0);
}

void TCPConnection::readBuffer(uint8_t* au8Buffer, ssize_t nbBytes)
  throw (IOException) {
  if (isOpen() == false)
    open();
  double intPart;
  double fractPart = modf(mTimeout , &intPart);
  struct timeval waitd;
  waitd.tv_sec = intPart;
  waitd.tv_usec = fractPart * 1000000;
  fd_set readFlags;
  FD_ZERO(&readFlags);
  FD_SET(mSocket, &readFlags);
  ssize_t res = select(mSocket + 1, &readFlags, (fd_set*)0,
    (fd_set*)0, &waitd);
  if(res < 0)
    throw IOException("TCPConnection::readBuffer(): Read select failed");
  if (FD_ISSET(mSocket, &readFlags)) {
    FD_CLR(mSocket, &readFlags);
    struct sockaddr_in client;
    socklen_t size;
    if (recvfrom(mSocket, au8Buffer, nbBytes, 0,
      (sockaddr*)&client, &size) != nbBytes)
      throw IOException("TCPConnection::readBuffer(): Read failed");
  }
  else
    throw IOException("TCPConnection::readBuffer(): Read timeout");
}
