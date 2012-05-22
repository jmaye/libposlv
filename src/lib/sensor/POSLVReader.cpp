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

#include <cstring>

#include "types/Group.h"
#include "types/Message.h"
#include "types/Packet.h"
#include "base/Factory.h"
#include "base/BufferReader.h"
#include "sensor/Checksum.h"
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

std::string POSLVReader::readEndString(BufferReader& bufferReader) {
  std::string outputString;
  uint8_t control;
  bufferReader >> control;
  outputString.push_back(control);
  bufferReader >> control;
  outputString.push_back(control);
  return outputString;
}

boost::shared_ptr<Packet> POSLVReader::readPacket() {
  std::string start = readStartString();
  uint16_t id;
  *this >> id;
  uint16_t byteCount;
  *this >> byteCount;
  char buffer[byteCount + 2 * sizeof(uint16_t) + start.size()];
  memcpy(&buffer[0], start.c_str(), start.size());
  memcpy(&buffer[start.size()], reinterpret_cast<char*>(&id), sizeof(uint16_t));
  memcpy(&buffer[start.size() + sizeof(uint16_t)],
    reinterpret_cast<char*>(&byteCount), sizeof(uint16_t));
  readBuffer(&buffer[2 * sizeof(uint16_t) + start.size()], byteCount);
  BufferReader bufferReader(&buffer[sizeof(uint16_t) + start.size()],
    byteCount + sizeof(uint16_t));
  const uint16_t sum = Checksum::getSum(buffer, sizeof(buffer));
  if (sum)
    throw IOException("POSLVReader::readPacket(): wrong checksum");
  if (start == "$GRP") {
    boost::shared_ptr<Packet>
      packet(Factory<uint16_t, Group>::getInstance().create(id));
    bufferReader >> *packet;
    const size_t padSize = bufferReader.getReadLeft() - 2 * sizeof(uint16_t);
    for (size_t i = 0; i < padSize; ++i) {
      uint8_t pad;
      bufferReader >> pad;
      if (pad != 0)
        throw IOException("POSLVReader::readPacket(): wrong pad");
    }
    uint16_t checksum;
    bufferReader >> checksum;
    std::string end = readEndString(bufferReader);
    if (end != "$#")
      throw IOException("POSLVReader::readPacket(): end of packet read failed");
    return packet;
  }
  else if (start == "$MSG") {
    boost::shared_ptr<Packet>
      packet(Factory<uint16_t, Message>::getInstance().create(id));
    bufferReader >> *packet;
    const size_t padSize = bufferReader.getReadLeft() - 2 * sizeof(uint16_t);
    for (size_t i = 0; i < padSize; ++i) {
      uint8_t pad;
      bufferReader >> pad;
      if (pad != 0)
        throw IOException("POSLVReader::readPacket(): wrong pad");
    }
    uint16_t checksum;
    bufferReader >> checksum;
    std::string end = readEndString(bufferReader);
    if (end != "$#")
      throw IOException("POSLVReader::readPacket(): end of packet read failed");
    return packet;
  }
  else
    throw IOException("POSLVReader::readPacket(): wrong start");

}
