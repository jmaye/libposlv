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

#include "visualization/PathBuilder.h"

#include <iomanip>

#include "types/VehicleNavigationPerformance.h"
#include "types/VehicleNavigationSolution.h"
#include "types/Group.h"
#include "types/Packet.h"
#include "sensor/Utils.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PathBuilder::PathBuilder(bool dump, const std::string& filename) :
    mDump(dump),
    mFilename(filename) {
}

PathBuilder::~PathBuilder() {
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void PathBuilder::readPacket(std::shared_ptr<Packet> packet) {
  if (packet->instanceOfGroup()) {
    const Group& group = packet->groupCast();
    if (group.instanceOf<VehicleNavigationSolution>()) {
      const VehicleNavigationSolution& msg =
        group.typeCast<VehicleNavigationSolution>();
      double east, north, height;
      Utils::WGS84ToLV03(msg.mLatitude, msg.mLongitude, msg.mAltitude, east,
        north, height);
      mPath.push_back(Eigen::Matrix<double, 3, 1>(east, north, height));
    }
    else if (group.instanceOf<VehicleNavigationPerformance>()) {
      const VehicleNavigationPerformance& msg =
        group.typeCast<VehicleNavigationPerformance>();
    }
  }
}

void PathBuilder::start() {
  mPath.clear();
}

void PathBuilder::eof() {
  if (mDump) {
    std::ofstream pathFile(mFilename);
    for (size_t i = 0; i < mPath.size(); ++i)
      pathFile << std::fixed << std::setprecision(16) << mPath[i].transpose()
        << std::endl;
    pathFile.close();
  }
  emit path(mPath);
}
