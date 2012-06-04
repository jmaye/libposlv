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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

/** \file NTRIPClient.h
    \brief This file defines the NTRIPClient class intended for receiving
           GPS corrections from a NTRIP server.
  */

#ifndef NTRIPCLIENT_H
#define NTRIPCLIENT_H

#include <string>

#include "base/BinaryStreamReader.h"
#include "com/TCPConnectionClient.h"

/** The NTRIPClient class communicates with an NTRIP server to receive GPS
    corrections.
    \brief NTRIP client
  */
class NTRIPClient {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  NTRIPClient(const NTRIPClient& other);
  /// Assignment operator
  NTRIPClient& operator = (const NTRIPClient& other);
  /** @}W
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the object
  NTRIPClient(const std::string& serverHost, short port, const std::string&
    serverStream = "", const std::string& userName = "", const std::string&
    password = "");
  /// Destructor
  virtual ~NTRIPClient();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the stream for reading
  const BinaryStreamReader<TCPConnectionClient>& getStream() const;
  /// Returns the connection
  const TCPConnectionClient& getConnection() const;
  /// Returns the connection
  TCPConnectionClient& getConnection();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Open and init the connection
  void open();
  /// Close the connection
  void close();
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Create http request line
  std::string getHTTPRequestLine(const std::string& method,
    const std::string& uri, const std::string& httpVersion = "1.1") const;
  /// Create http general headers
  std::string getHTTPGeneralHeaders(const std::string& host, const std::string&
    userAgent, const std::string& authentification = "", const std::string&
    connection = "close") const;
  /// Create http NTRIP version header
  std::string getHTTPNTRIPVersionHeader(const std::string& ntripVersion) const;
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Server host
  std::string mServerHost;
  /// Server IP
  std::string mServerIP;
  /// Server port
  short mPort;
  /// Live stream (optional)
  std::string mServerStream;
  /// Username (optional)
  std::string mUserName;
  /// Password (optional)
  std::string mPassword;
  /// TCP connection
  TCPConnectionClient mConnection;
  /// Binary sream reader
  BinaryStreamReader<TCPConnectionClient> mStream;
  /** @}
    */

};

#endif // NTRIPCLIENT_H
