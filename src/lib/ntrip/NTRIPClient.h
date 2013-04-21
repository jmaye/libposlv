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
#include "base/BinaryStreamWriter.h"
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
  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Constructs the object
  NTRIPClient(const std::string& serverHost, short port, const std::string&
    mountPoint = "", const std::string& userName = "", const std::string&
    password = "", const std::string& ntripVersion = "2.0", const std::string&
    agentName = "NTRIPClient");
  /// Destructor
  virtual ~NTRIPClient();
  /** @}
    */

  /** \name Accessors
    @{
    */
  /// Returns the stream for reading
  const BinaryStreamReader<TCPConnectionClient>& getStreamReader() const;
  /// Returns the stream for reading
  BinaryStreamReader<TCPConnectionClient>& getStreamReader();
  /// Returns the stream for writing
  const BinaryStreamWriter<TCPConnectionClient>& getStreamWriter() const;
  /// Returns the stream for writing
  BinaryStreamWriter<TCPConnectionClient>& getStreamWriter();
  /// Returns the connection
  const TCPConnectionClient& getConnection() const;
  /// Returns the connection
  TCPConnectionClient& getConnection();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Open the connection
  void open();
  /// Request source table
  std::string requestSourceTable();
  /// Request live stream
  void requestLiveStream(const std::string& nmeaMessage = "");
  /// Close the connection
  void close();
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Server host
  std::string mServerHost;
  /// Server IP
  std::string mServerIP;
  /// Server port
  short mPort;
  /// Mountpoint (optional)
  std::string mMountPoint;
  /// Username (optional)
  std::string mUserName;
  /// Password (optional)
  std::string mPassword;
  /// NTRIP version (optional)
  std::string mNTRIPVersion;
  /// NTRIP agent name
  std::string mNTRIPAgentName;
  /// TCP connection
  TCPConnectionClient mConnection;
  /// Binary sream reader
  BinaryStreamReader<TCPConnectionClient> mStreamReader;
  /// Binary sream writer
  BinaryStreamWriter<TCPConnectionClient> mStreamWriter;
  /** @}
    */

};

#endif // NTRIPCLIENT_H
