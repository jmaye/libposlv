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

/** \file conversions.cpp
    \brief This file is a testing binary for the conversions.
  */

#include <iostream>

#include <cmath>

#include "sensor/Utils.h"

int main(int argc, char** argv) {
  double east, north, height;
  Utils::WGS84ToLV03(46.044131, 8.730497, 650.60, east, north, height);
  std::cout  << "East: " << east << " North: " << north
    << " Height: " << height << std::endl;
  if (fabs(east - 700000) > 5e-1 || fabs(north - 100000) > 5e-1 ||
      fabs(height - 600) > 5e-1)
    return 1;
  double latitude, longitude, altitude;
  Utils::LV03ToWGS84(latitude, longitude, altitude, 700000, 100000, 600);
  std::cout << "Latitude: " << latitude << " Longitude: " << longitude
    << " Altitude: " << altitude << std::endl;
  if (fabs(latitude - 46.044131) > 5e-1 || fabs(longitude - 8.730497) > 5e-1 ||
      fabs(altitude - 650.60) > 5e-1)
    return 1;
  return 0;
}
