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

/** \file binaryToKML.cpp
    \brief This file is a testing binary for converting a binary log file
           into a KML file.
  */

#include <cmath>

#include <sstream>
#include <iomanip>
#include <vector>

#include "types/Packet.h"
#include "sensor/BinaryLogReader.h"
#include "exceptions/IOException.h"
#include "types/VehicleNavigationSolution.h"
#include "types/Group.h"
#include "types/Packet.h"
#include "base/Timestamp.h"

#define GOOGLE_EARTH_MAX_POINTS 64000

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
    << "<kml xmlns=\"http://www.opengis.net/kml/2.2\"" << std::endl
    << " xmlns:gx=\"http://www.google.com/kml/ext/2.2\">" << std::endl
    << "<Folder>" << std::endl
    << "  <Placemark>" << std::endl
    << "    <Style>" << std::endl
    << "      <LineStyle>" << std::endl
    << "        <color>FF0000E6</color>" << std::endl
    << "        <width>2</width>" << std::endl
    << "      </LineStyle>" << std::endl
    << "    </Style>" << std::endl
    << "    <name>Toyota PRIUS</name>" << std::endl
    << "    <description>Current pose of the PRIUS</description>" << std::endl
    << "    <gx:Track>" << std::endl;
  std::vector<std::string> when;
  std::vector<std::string> coord;
  std::vector<std::string> angles;
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
          std::string date = Timestamp(msg.mTimeDistance.mTime1).getDate();
          date[10] = 'T';
          date.push_back('Z');
          std::stringstream whenss;
          std::stringstream coordss;
          std::stringstream anglesss;
          whenss << "      <when>" << date << "</when>" << std::endl;
          coordss << "      <gx:coord>" << std::setprecision(16)
            << msg.mLongitude << " " << msg.mLatitude << " "
            << msg.mAltitude << "</gx:coord>" << std::endl;
          anglesss << "      <gx:angles>" << msg.mHeading << " "
            << msg.mPitch << " " << msg.mRoll << "</gx:angles>" << std::endl;
          when.push_back(whenss.str());
          coord.push_back(coordss.str());
          angles.push_back(anglesss.str());
        }
      }
    }
    catch (IOException& e) {
    }
  }
  const size_t subSample = ceil(when.size() / (double)GOOGLE_EARTH_MAX_POINTS);
  for (size_t i = 0; i < when.size(); i += subSample) {
    outFile << when[i] << coord[i] << angles[i];
  }
  outFile << "    </gx:Track>" << std::endl
    << "  </Placemark>" << std::endl
    << "</Folder>" << std::endl
    << "</kml>";
  return 0;
}
