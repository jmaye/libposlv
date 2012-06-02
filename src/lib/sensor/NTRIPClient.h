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
  NTRIPClient(const std::string &serverHost, short port, const std::string&
    serverStream = "", const std::string& userName = "", const std::string&
    password = "");
  /// Destructor
  virtual ~NTRIPClient();
  /** @}
    */

  /** \name Methods
    @{
    */
  /** @}
    */

protected:
  /** \name Protected members
    @{
    */
  /// Server host
  std::string mServerHost;
  /// Server port
  short mPort;
  /// Live stream (optional)
  std::string mServerStream;
  /// Username (optional)
  std::string mUserName;
  /// Password (optional)
  std::string mPassword;
  /** @}
    */

};

#endif // NTRIPCLIENT_H
