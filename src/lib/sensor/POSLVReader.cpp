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

#include "sensor/POSLVReader.h"

#include "types/Group.h"
#include "types/Message.h"
#include "types/Packet.h"
#include "base/Factory.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

POSLVReader::POSLVReader() {
}

POSLVReader::~POSLVReader() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

std::string POSLVReader::readStartString() {
  uint8_t control;
  std::string outputString;
  *this >> control;
  while (true) {
    while (control != '$')
      *this >> control;
    outputString.clear();
    outputString.push_back(control);
    *this >> control;
    if (control != 'G' || control != 'M')
      continue;
    outputString.push_back(control);
    *this >> control;
    if ((control != 'R' && outputString == "$G") ||
        (control != 'S' && outputString == "$M"))
      continue;
    outputString.push_back(control);
    *this >> control;
    if ((control != 'P' && outputString == "$GR") ||
        (control != 'G' && outputString == "$MS"))
      continue;
    outputString.push_back(control);
    break;
  }
  return outputString;
}

std::string POSLVReader::readEndString() {
  std::string outputString;
  uint8_t control;
  *this >> control;
  outputString.push_back(control);
  *this >> control;
  outputString.push_back(control);
  return outputString;
}

boost::shared_ptr<Packet> POSLVReader::readPacket() {
  std::string start = readStartString();
  uint16_t id;
  *this >> id;
  if (start == "$GRP") {
    boost::shared_ptr<Packet>
      packet(Factory<uint16_t, Group>::getInstance().create(id));
    *this >> *packet;
    uint16_t checksum;
    *this >> checksum;
//    if (checksum != packet->groupCast().getChecksum())
//      throw IOException("POSLVReader::readPacket(): wrong checksum");
    std::string end = readEndString();
    if (end != "$#")
      throw IOException("POSLVReader::readPacket(): end of packet read failed");
    return packet;
  }
  else if (start == "$MSG") {
    boost::shared_ptr<Packet>
      packet(Factory<uint16_t, Message>::getInstance().create(id));
    *this >> *packet;
    uint16_t checksum;
    *this >> checksum;
    if (checksum != packet->messageCast().getChecksum())
      throw IOException("POSLVReader::readPacket(): wrong checksum");
    std::string end = readEndString();
    if (end != "$#")
      throw IOException("POSLVReader::readPacket(): end of packet read failed");
    return packet;
  }
  else
    throw IOException("POSLVReader::readPacket(): wrong start");

}
