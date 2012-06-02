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

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

NTRIPClient::NTRIPClient(const std::string &serverHost, short port, const
    std::string& serverStream, const std::string& userName, const std::string&
    password) :
    mServerHost(serverHost),
    mPort(port),
    mServerStream(serverStream),
    mUserName(userName),
    mPassword(password) {
}

NTRIPClient::~NTRIPClient() {
}

/******************************************************************************/
/* Accessors                                                                  */
/******************************************************************************/

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

//  std::string httpRequest = "GET /ZIM20 HTTP/1.1\r\n"
//    "Host: http://www.euref-ip.net/\r\n"
//    "Authorization: BASIC YXNsdGVhbTphc2xldGh6\r\n"
//    "Ntrip-Version: Ntrip/2.0\r\n"
//    "User-Agent: NTRIP poslv-dgps\r\n"
//    "Connection: close\r\n\r\n";
