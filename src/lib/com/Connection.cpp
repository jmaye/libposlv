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

#include "com/Connection.h"

#include "base/Factory.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string.h>
#include <math.h>

using namespace std;

Connection::Connection(const string& strHost, uint32_t u32Port,
  double f64Timeout)
 : mstrHost(strHost),
   mPort(u32Port),
   mTimeout(f64Timeout),
   mSocket(0) {
}

Connection::~Connection() {
  close();
}

const string& Connection::getHost() const {
  return mstrHost;
}

uint32_t Connection::getPort() const {
  return mPort;
}

double Connection::getTimeout() const {
  return mTimeout;
}

void Connection::setTimeout(double f64Time) {
  mTimeout = f64Time;
}

void Connection::open() throw (IOException) {
  mSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (mSocket == -1)
    throw IOException("Connection::open: Socket creation failed");

  int32_t i32Flag = 1;
  if (setsockopt(mSocket, IPPROTO_TCP, TCP_NODELAY, (char*)&i32Flag,
    sizeof(int32_t)) == -1)
    throw IOException("doOpen: Set TCP_NODELAY failed");

  struct sockaddr_in server;
  memset(&server, 0, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(mstrHost.c_str());
  server.sin_port = htons(mPort);
  if (connect(mSocket, (struct sockaddr*)&server, sizeof(server)) == -1)
    throw IOException("Connection::open: Socket connection failed");
}

void Connection::close() throw (IOException) {
  if (mSocket != 0) {
    int32_t i32Res = ::close(mSocket);
    if (i32Res == -1)
      throw IOException("Connection::close: Socket closing failed");
  }
  mSocket = 0;
}

bool Connection::isOpen() const {
  return (mSocket != 0);
}

uint8_t Connection::readByte() const throw (IOException) {
  double f64IntPart;
  double f64FractPart = modf(mTimeout , &f64IntPart);
  struct timeval waitd;
  waitd.tv_sec = f64IntPart;
  waitd.tv_usec = f64FractPart * 1000000;
  fd_set readFlags;
  FD_ZERO(&readFlags);
  FD_SET(mSocket, &readFlags);
  int32_t i32Res = select(mSocket + 1, &readFlags, (fd_set*)0,
    (fd_set*)0, &waitd);
  if(i32Res < 0)
    throw IOException("Connection::readByte: Read select failed");
  uint8_t u8Byte;
  if (FD_ISSET(mSocket, &readFlags)) {
    FD_CLR(mSocket, &readFlags);
    if (::read(mSocket, &u8Byte, 1) == -1)
      throw IOException("Connection::readByte: Read failed");
  }
  else
    throw IOException("Connection::readByte: Read timeout");
  return u8Byte;
}

const Group* Connection::readGroup()
  throw(IOException) {
  if(mSocket == 0)
    open();
  readStartGroup();

  uint16_t u16GroupID;
  *this >> u16GroupID;

  if (Factory<uint16_t, Group>::getInstance().isRegistered(u16GroupID) == false)
    return NULL;

  Group *groupRead = Factory<uint16_t, Group>::getInstance().create(u16GroupID);
  *this >> *groupRead;

  uint16_t u16Checksum;
  *this >> u16Checksum;

  // TODO: Checksum control

  string endString = readEndGroup();
  if (endString != "$#")
    throw IOException("Connection::readGroup: End of group read failed");
  return groupRead;
}

void Connection::readStartGroup() const throw (IOException) {
  uint8_t control;
  while (true) {
    do {
      control = readByte();
    }
    while (control != '$');
    control = readByte();
    if (control != 'G')
      continue;
    control = readByte();
    if (control != 'R')
      continue;
    control = readByte();
    if (control != 'P')
      continue;
    break;
  }
}

string Connection::readEndGroup() const throw (IOException) {
  string outputString;
  outputString.push_back(readByte());
  outputString.push_back(readByte());
  return outputString;
}

void Connection::sendControl() throw (IOException) {
  if(mSocket == 0)
    open();
  
}

Connection& Connection::operator >> (int8_t &i8Value) throw (IOException) {
  i8Value = (int8_t)readByte();
  return *this;
}

Connection& Connection::operator >> (uint8_t &u8Value) throw (IOException) {
  u8Value = readByte();
  return *this;
}

Connection& Connection::operator >> (int16_t &i16Value) throw (IOException) {
  ((uint8_t*)&i16Value)[0] = readByte();
  ((uint8_t*)&i16Value)[1] = readByte();
  return *this;
}

Connection& Connection::operator >> (uint16_t &u16Value) throw (IOException) {
  ((uint8_t*)&u16Value)[0] = readByte();
  ((uint8_t*)&u16Value)[1] = readByte();
  return *this;
}

Connection& Connection::operator >> (int32_t &i32Value) throw (IOException) {
  ((uint8_t*)&i32Value)[0] = readByte();
  ((uint8_t*)&i32Value)[1] = readByte();
  ((uint8_t*)&i32Value)[2] = readByte();
  ((uint8_t*)&i32Value)[3] = readByte();
  return *this;
}

Connection& Connection::operator >> (uint32_t &u32Value) throw (IOException) {
  ((uint8_t*)&u32Value)[0] = readByte();
  ((uint8_t*)&u32Value)[1] = readByte();
  ((uint8_t*)&u32Value)[2] = readByte();
  ((uint8_t*)&u32Value)[3] = readByte();
  return *this;
}

Connection& Connection::operator >> (int64_t &i64Value) throw (IOException) {
  ((uint8_t*)&i64Value)[0] = readByte();
  ((uint8_t*)&i64Value)[1] = readByte();
  ((uint8_t*)&i64Value)[2] = readByte();
  ((uint8_t*)&i64Value)[3] = readByte();
  ((uint8_t*)&i64Value)[4] = readByte();
  ((uint8_t*)&i64Value)[5] = readByte();
  ((uint8_t*)&i64Value)[6] = readByte();
  ((uint8_t*)&i64Value)[7] = readByte();
  return *this;
}

Connection& Connection::operator >> (uint64_t &u64Value) throw (IOException) {
  ((uint8_t*)&u64Value)[0] = readByte();
  ((uint8_t*)&u64Value)[1] = readByte();
  ((uint8_t*)&u64Value)[2] = readByte();
  ((uint8_t*)&u64Value)[3] = readByte();
  ((uint8_t*)&u64Value)[4] = readByte();
  ((uint8_t*)&u64Value)[5] = readByte();
  ((uint8_t*)&u64Value)[6] = readByte();
  ((uint8_t*)&u64Value)[7] = readByte();
  return *this;
}


Connection& Connection::operator >> (std::string &strValue) throw (IOException) {
  uint32_t u32Length;
  ((uint8_t*)&u32Length)[0] = readByte();
  ((uint8_t*)&u32Length)[1] = readByte();
  ((uint8_t*)&u32Length)[2] = readByte();
  ((uint8_t*)&u32Length)[3] = readByte();
  for (uint32_t i = 0; i < u32Length; i++)
    strValue.push_back(readByte());
  return *this;
}

Connection& Connection::operator >> (float &f32Value) throw (IOException) {
  ((uint8_t*)&f32Value)[0] = readByte();
  ((uint8_t*)&f32Value)[1] = readByte();
  ((uint8_t*)&f32Value)[2] = readByte();
  ((uint8_t*)&f32Value)[3] = readByte();
  return *this;
}

Connection& Connection::operator >> (double &f64Value) throw (IOException) {
  ((uint8_t*)&f64Value)[0] = readByte();
  ((uint8_t*)&f64Value)[1] = readByte();
  ((uint8_t*)&f64Value)[2] = readByte();
  ((uint8_t*)&f64Value)[3] = readByte();
  ((uint8_t*)&f64Value)[4] = readByte();
  ((uint8_t*)&f64Value)[5] = readByte();
  ((uint8_t*)&f64Value)[6] = readByte();
  ((uint8_t*)&f64Value)[7] = readByte();
  return *this;
}
