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

/** \file logDataPort.cpp
    \brief This file is a testing binary for logging data from the TCP Ethernet
           Real-Time and Logging ports.
  */

#include "com/POSLVData.h"
#include "base/Timestamp.h"

#include <cstdlib>

int main(int argc, char** argv) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0] << " <IP> <Port> <LogFilename>" << std::endl;
    return -1;
  }

  POSLVData device(argv[1], atoi(argv[2]));
  device.open();

  while (true) {
    const Group* read = device.readGroup();
    if (read == NULL) {
      std::cout << "Dropping message..." << std::endl;
      continue;
    }
    std::ofstream logFile(argv[3], std::ios_base::app);
    logFile << std::fixed << Timestamp::now() << " ";
    logFile << *read;
    logFile << std::endl;
    logFile.close();
    delete read;
  }

  device.close();

  return 0;
}