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

#include "sensor/POSLVWriter.h"

#include <string>
#include <limits>

#include "types/Message.h"
#include "base/BinaryBufferWriter.h"
#include "sensor/Checksum.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

POSLVWriter::POSLVWriter() {
}

POSLVWriter::~POSLVWriter() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void POSLVWriter::sendMessage(const Message& message) {
  BinaryBufferWriter bufferWriter;
  bufferWriter << std::string("$MSG");
  bufferWriter << message;
  const size_t padSize = (bufferWriter.getBufferSize() + 2 * sizeof(uint16_t))
    % 4;
  for (size_t i = 0; i < padSize; ++i) {
    const uint8_t pad = 0;
    bufferWriter << pad;
  }
  std::string end = "$#";
  const uint16_t sum = Checksum::getSum(bufferWriter.getBuffer(),
    bufferWriter.getBufferSize()) +
    Checksum::getSum(reinterpret_cast<const char*>(end.c_str()), end.size());
  const uint16_t checksum = std::numeric_limits<unsigned short>::max() + 1 -
    sum;
  bufferWriter << checksum;
  bufferWriter << end;
  write(bufferWriter.getBuffer(), bufferWriter.getBufferSize());
}
