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

/** \file binaryLogToKML.cpp
    \brief This file is a testing binary for converting a binary log file
           into a KML file.
  */

#include <sstream>
#include <iomanip>

#include "types/Packet.h"
#include "sensor/BinaryLogReader.h"
#include "exceptions/IOException.h"
#include "types/VehicleNavigationSolution.h"
#include "types/Group.h"
#include "types/Packet.h"
#include "base/Timestamp.h"

//int main(int argc, char** argv) {
//  if (argc != 3) {
//    std::cerr << "Usage: " << argv[0] << " <LogFilename>" << " <OutFilename>"
//      << std::endl;
//    return -1;
//  }
//  std::ifstream logFile(argv[1]);
//  BinaryLogReader logReader(logFile);
//  logFile.seekg (0, std::ios::end);
//  const int length = logFile.tellg();
//  logFile.seekg (0, std::ios::beg);
//  std::ofstream outFile(argv[2]);
//  outFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl
//    << "<kml xmlns=\"http://www.opengis.net/kml/2.2\"" << std::endl
//    << " xmlns:gx=\"http://www.google.com/kml/ext/2.2\">" << std::endl
//    << "<Folder>" << std::endl
//    << "  <Placemark>" << std::endl
//    << "    <gx:Track>" << std::endl;
//  std::stringstream when;
//  std::stringstream coord;
//  size_t packetCounter = 0;
//  while (logFile.tellg() != length) {
//    std::cout << std::fixed
//      << logFile.tellg() / (double)length * 100 << " %" << '\r';
//    double timestamp;
//    logReader >> timestamp;
//    try {
//      std::shared_ptr<Packet> packet = logReader.readPacket();
//      if (packet->instanceOfGroup()) {
//        const Group& group = packet->groupCast();
//        if (group.instanceOf<VehicleNavigationSolution>()) {
//          const VehicleNavigationSolution& msg =
//            group.typeCast<VehicleNavigationSolution>();
//          std::string date = Timestamp(timestamp).getDate();
//          date[10] = 'T';
//          packetCounter++;
//          std::stringstream packetCounterString;
//          packetCounterString << "." << packetCounter % 100;
//          date.append(packetCounterString.str());
//          date.push_back('Z');
//          when << "      <when>" << date << "</when>" << std::endl;
//          coord << "      <gx:coord>" << std::setprecision(16)
//            << msg.mLongitude << " " << msg.mLatitude << " "
//            << msg.mAltitude << "</gx:coord>" << std::endl;
//        }
//      }
//    }
//    catch (IOException& e) {
//    }
//  }
//  outFile << when.str() << coord.str();
//  outFile << "    </gx:Track>" << std::endl
//    << "  </Placemark>" << std::endl
//    << "</Folder>" << std::endl
//    << "</kml>";
//  return 0;
//}

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
  outFile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl
    << "<kml xmlns=\"http://www.opengis.net/kml/2.2\">" << std::endl
    << "  <Document>" << std::endl
    << "    <name>" << "Applanix Run" << "</name>" << std::endl
    << "    <description>" << "Applanix run" << "</description>" << std::endl
    << "    <Style>" << std::endl
    << "      <PolyStyle>" << std::endl
    << "        <fill>0</fill>" << std::endl
    << "        <outline>1</outline>" << std::endl
    << "      </PolyStyle>" << std::endl
    << "    </Style>" << std::endl
    << "    <Placemark>" << std::endl
    << "      <name>Applanix Run</name>" << std::endl
    << "      <description>Applanix run</description>" << std::endl
    << "      <MultiGeometry>" << std::endl
    << "        <LineString>" << std::endl
    << "          <coordinates>";
  while (logFile.tellg() != length) {
    std::cout << std::fixed
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
          outFile << std::setprecision(16) << msg.mLongitude
            << "," << msg.mLatitude << " ";
        }
      }
    }
    catch (IOException& e) {
    }
  }
  outFile << "</coordinates>" << std::endl
    << "        </LineString>" << std::endl
    << "      </MultiGeometry>" << std::endl
    << "    </Placemark>" << std::endl
    << "  </Document>" << std::endl
    << "</kml>";
  return 0;
}
