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

/** \file logDisplayPort.cpp
    \brief This file is a testing binary for logging data from the UDP display
           port.
  */

#include <cstdlib>

#include "com/UDPConnectionServer.h"
#include "sensor/POSLVComUDP.h"
#include "types/Packet.h"
#include "base/Timestamp.h"

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <Port> <LogFilename>"
      << std::endl;
    return -1;
  }
  UDPConnectionServer connection(atoi(argv[1]));
  POSLVComUDP device(connection);
  while (true) {
    boost::shared_ptr<Packet> packet = device.readPacket();
    std::ofstream logFile(argv[2], std::ios_base::app);
    logFile << std::fixed << Timestamp::now() << " ";
    logFile << *packet;
    logFile << std::endl;
    logFile.close();
  }
  return 0;
}
