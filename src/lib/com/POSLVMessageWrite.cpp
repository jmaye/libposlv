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

#include "com/POSLVMessageWrite.h"

#include "base/Factory.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

POSLVMessageWrite::POSLVMessageWrite() {
}

POSLVMessageWrite::POSLVMessageWrite(const POSLVMessageWrite& other) {
}

POSLVMessageWrite& POSLVMessageWrite::operator =
  (const POSLVMessageWrite& other) {
  return *this;
}

POSLVMessageWrite::~POSLVMessageWrite() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void POSLVMessageWrite::sendMessage(const Message& message)
  throw (IOException) {
  std::string msgHeader = "$MSG";
  writeBuffer((const uint8_t*)msgHeader.c_str(), msgHeader.size());
  *this << message;
  std::string msgEnd = "$#";
  writeBuffer((const uint8_t*)msgEnd.c_str(), msgEnd.size());
}
