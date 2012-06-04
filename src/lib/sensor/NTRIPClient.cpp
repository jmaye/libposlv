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

#include "sensor/NTRIPClient.h"

#include <sstream>

#include "com/NetUtils.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

NTRIPClient::NTRIPClient(const std::string &serverHost, short port, const
    std::string& serverStream, const std::string& userName, const std::string&
    password) :
    mServerHost(serverHost),
    mServerIP(NetUtils::getHostIP(serverHost)),
    mPort(port),
    mServerStream(serverStream),
    mUserName(userName),
    mPassword(password),
    mConnection(mServerIP, mPort),
    mStream(mConnection) {
}

NTRIPClient::~NTRIPClient() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const BinaryStreamReader<TCPConnectionClient>& NTRIPClient::getStream() const {
  return mStream;
}

const TCPConnectionClient& NTRIPClient::getConnection() const {
  return mConnection;
}

TCPConnectionClient& NTRIPClient::getConnection() {
  return mConnection;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void NTRIPClient::open() {
  mConnection.open();
  std::string httpRequest;
  httpRequest.append(getHTTPRequestLine("GET", mServerStream.empty() ? "/" :
    mServerStream));
  httpRequest.append(getHTTPGeneralHeaders(mServerHost, "NTRIP NTRIPClient/1.0",
    "BASIC YXNsdGVhbTphc2xldGh6"));
  httpRequest.append(getHTTPNTRIPVersionHeader("2.0"));
  httpRequest.append("\r\n");
  mConnection.write(httpRequest.c_str(), httpRequest.size());
  while (1) {
    uint8_t byte;
    mStream >> byte;
    std::cout << (char)byte;
  }
}

void NTRIPClient::close() {
  mConnection.close();
}

std::string NTRIPClient::getHTTPRequestLine(const std::string& method,
    const std::string& uri, const std::string& httpVersion) const {
  std::stringstream httpRequestLine;
  httpRequestLine << method << " " << uri << " " << "HTTP/" << httpVersion
    << "\r\n";
  return httpRequestLine.str();
}

std::string NTRIPClient::getHTTPGeneralHeaders(const std::string& host, const
    std::string& userAgent, const std::string& authorization, const
    std::string& connection) const {
  std::stringstream httpHeader;
  httpHeader << "Host: " << host << "\r\n"
    << "User-Agent: " << userAgent << "\r\n"
    << "Authorization: " << authorization << "\r\n"
    << "Connection: " << connection << "\r\n";
  return httpHeader.str();
}

std::string NTRIPClient::getHTTPNTRIPVersionHeader(const std::string&
    ntripVersion) const {
  std::stringstream httpNTRIPHeader;
  httpNTRIPHeader << "Ntrip-Version: Ntrip/" << ntripVersion << "\r\n";
  return httpNTRIPHeader.str();
}
