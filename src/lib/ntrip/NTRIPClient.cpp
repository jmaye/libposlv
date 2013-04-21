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

#include "ntrip/NTRIPClient.h"

#include <sstream>

#include "com/NetUtils.h"
#include "com/HTTPProtocol.h"
#include "exceptions/IOException.h"
#include "exceptions/BadArgumentException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

NTRIPClient::NTRIPClient(const std::string &serverHost, short port, const
    std::string& mountPoint, const std::string& userName, const std::string&
    password, const std::string& ntripVersion, const std::string& agentName) :
    mServerHost(serverHost),
    mServerIP(NetUtils::getHostIP(serverHost)),
    mPort(port),
    mMountPoint(mountPoint),
    mUserName(userName),
    mPassword(password),
    mNTRIPVersion(ntripVersion),
    mNTRIPAgentName("NTRIP " + agentName),
    mConnection(mServerIP, mPort),
    mStreamReader(mConnection),
    mStreamWriter(mConnection) {
  if (mNTRIPVersion != "1.0" && mNTRIPVersion != "2.0")
    throw BadArgumentException<std::string>(mNTRIPVersion,
      "NTRIPClient::NTRIPClient(): only NTRIP version 1.0 or 2.0 supported");
}

NTRIPClient::~NTRIPClient() {
  close();
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

const BinaryStreamReader<TCPConnectionClient>& NTRIPClient::getStreamReader()
    const {
  return mStreamReader;
}

BinaryStreamReader<TCPConnectionClient>& NTRIPClient::getStreamReader() {
  return mStreamReader;
}

const BinaryStreamWriter<TCPConnectionClient>& NTRIPClient::getStreamWriter()
    const {
  return mStreamWriter;
}

BinaryStreamWriter<TCPConnectionClient>& NTRIPClient::getStreamWriter() {
  return mStreamWriter;
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
}

std::string NTRIPClient::requestSourceTable() {
  std::string httpRequest;
  httpRequest += HTTPProtocol::writeRequestLine(HTTPProtocol::Method::GET);
  httpRequest += HTTPProtocol::writeGeneralHeaderLine(
    HTTPProtocol::GeneralHeader::Connection, "close");
  httpRequest += HTTPProtocol::writeRequestHeaderLine(
    HTTPProtocol::RequestHeader::Host, mServerHost);
  httpRequest += HTTPProtocol::writeRequestHeaderLine(
    HTTPProtocol::RequestHeader::UserAgent, mNTRIPAgentName);
  httpRequest += HTTPProtocol::writeUserHeaderLine("Ntrip-Version",
    "Ntrip/" + mNTRIPVersion);
  httpRequest += "\r\n";
  mStreamWriter << httpRequest;
  std::string responseStatusLine = HTTPProtocol::readLine(mStreamReader);
  std::string protocol;
  std::string statusCode;
  std::string reasonPhrase;
  HTTPProtocol::readResponseStatusLine(responseStatusLine, protocol, statusCode,
    reasonPhrase);
  if (statusCode != "200")
    throw IOException("NTRIPClient::requestSourceTable(): \nstatus code: " +
      statusCode + "\nreason: " + reasonPhrase);
  if ((mNTRIPVersion == "1.0" && protocol != "SOURCETABLE") ||
      (mNTRIPVersion == "2.0" && protocol != "HTTP/1.1"))
    throw IOException(
      "NTRIPClient::requestSourceTable(): wrong protocol response");
  std::string responseHeaderLine;
  size_t bytesToRead = 0;
  while (1) {
    responseHeaderLine = HTTPProtocol::readLine(mStreamReader);
    if (responseHeaderLine == "\r\n")
      break;
    std::string header;
    std::string value;
    HTTPProtocol::readHeaderLine(responseHeaderLine, header, value);
    if (header ==
        HTTPProtocol::entityHeaders[HTTPProtocol::EntityHeader::ContentLength])
      bytesToRead = atoi(value.c_str());
    if (header ==
        HTTPProtocol::entityHeaders[HTTPProtocol::EntityHeader::ContentType] &&
        mNTRIPVersion == "2.0" &&
        value.compare(0, 15, "gnss/sourcetable", 0, 15))
      throw IOException(
        "NTRIPClient::requestSourceTable(): wrong server response");
    if (header ==
        HTTPProtocol::entityHeaders[HTTPProtocol::EntityHeader::ContentType] &&
        mNTRIPVersion == "1.0" &&
        value.compare(0, 9, "text/plain", 0, 9))
      throw IOException(
        "NTRIPClient::requestSourceTable(): wrong server response");
  }
  if (bytesToRead) {
    char buffer[bytesToRead];
    mStreamReader.read(buffer, bytesToRead);
    return std::string(buffer, bytesToRead);
  }
  else
    throw IOException(
      "NTRIPClient::requestSourceTable(): wrong server response");
}

void NTRIPClient::requestLiveStream(const std::string& nmeaMessage) {
  std::string httpRequest;
  httpRequest += HTTPProtocol::writeRequestLine(HTTPProtocol::Method::GET,
    mMountPoint);
  httpRequest += HTTPProtocol::writeGeneralHeaderLine(
    HTTPProtocol::GeneralHeader::Connection, "close");
  httpRequest += HTTPProtocol::writeRequestHeaderLine(
    HTTPProtocol::RequestHeader::Host, mServerHost);
  httpRequest += HTTPProtocol::writeRequestHeaderLine(
    HTTPProtocol::RequestHeader::UserAgent, mNTRIPAgentName);
  if (!mUserName.empty() && !mPassword.empty())
    httpRequest += HTTPProtocol::writeRequestHeaderLine(
      HTTPProtocol::RequestHeader::Authorization, "Basic " +
      NetUtils::base64Encode(mUserName + ":" + mPassword));
  httpRequest += HTTPProtocol::writeUserHeaderLine("Ntrip-Version",
    "Ntrip/" + mNTRIPVersion);
  if (!nmeaMessage.empty())
    httpRequest += HTTPProtocol::writeUserHeaderLine("Ntrip-GGA",
      nmeaMessage);
  httpRequest += "\r\n";
  mStreamWriter << httpRequest;
  std::string responseStatusLine = HTTPProtocol::readLine(mStreamReader);
  std::string protocol;
  std::string statusCode;
  std::string reasonPhrase;
  HTTPProtocol::readResponseStatusLine(responseStatusLine, protocol, statusCode,
    reasonPhrase);
  if (statusCode != "200")
    throw IOException("NTRIPClient::requestLiveStream(): \nstatus code: " +
      statusCode + "\nreason: " + reasonPhrase);
  if ((mNTRIPVersion == "1.0" && protocol != "ICY") ||
      (mNTRIPVersion == "2.0" && protocol != "HTTP/1.1"))
    throw IOException(
      "NTRIPClient::requestLiveStream(): wrong protocol response");
  std::string responseHeaderLine;
  while (1) {
    responseHeaderLine = HTTPProtocol::readLine(mStreamReader);
    if (responseHeaderLine == "\r\n")
      break;
    std::string header;
    std::string value;
    HTTPProtocol::readHeaderLine(responseHeaderLine, header, value);
    if (header ==
        HTTPProtocol::entityHeaders[HTTPProtocol::EntityHeader::ContentType] &&
        mNTRIPVersion == "2.0" &&
        value.compare(0, 8, "gnss/data", 0, 8))
      throw IOException(
        "NTRIPClient::requestLiveStream(): wrong server response");
    if (header ==
        HTTPProtocol::generalHeaders[
        HTTPProtocol::GeneralHeader::TransferEncoding] &&
        mNTRIPVersion == "2.0" &&
        value.compare(0, 6, "chunked", 0, 6))
      throw IOException(
        "NTRIPClient::requestLiveStream(): wrong server response");
  }
}

void NTRIPClient::close() {
  mConnection.close();
}
