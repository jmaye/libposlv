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

/** \file binaryToTime.cpp
    \brief This file is a testing binary for converting a binary log file
           into a text file with timestamps
  */

#include <iomanip>

#include "types/Packet.h"
#include "sensor/BinaryLogReader.h"
#include "exceptions/IOException.h"
#include "types/VehicleNavigationSolution.h"
#include "types/Group.h"
#include "types/Packet.h"
#include "sensor/Utils.h"

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <LogFilename>" << " <OutFilename>"
      << std::endl;
    return -1;
  }
  std::ifstream logFile(argv[1]);
  BinaryLogReader logReader(logFile);
  logFile.seekg (0, std::ios::end);
  const int length = logFile.tellg();
  logFile.seekg (0, std::ios::beg);
  std::ofstream outFile(argv[2]);
  while (logFile.tellg() != length) {
    std::cout << std::fixed << std::setw(3)
      << logFile.tellg() / (double)length * 100 << " %" << '\r';
    double timestamp;
    logReader >> timestamp;
    try {
      std::shared_ptr<Packet> packet = logReader.readPacket();
      if (packet->instanceOfGroup()) {
        const Group& group = packet->groupCast();
        if (group.instanceOf<VehicleNavigationSolution>()) {
          const VehicleNavigationSolution& msg =
            group.typeCast<VehicleNavigationSolution>();
          outFile << std::fixed << std::setprecision(16) << timestamp << " "
            << msg.mTimeDistance.mTime1 << " "
            << msg.mTimeDistance.mTime2 << std::endl;
        }
      }
    }
    catch (IOException& e) {
    }
  }
  return 0;
}
