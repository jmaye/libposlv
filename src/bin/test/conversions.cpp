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

#include <cmath>

#include <iostream>

#include <Eigen/Array>

#include "geo-tools/Geo.h"

int main(int argc, char** argv) {
  double east, north, height;
  Geo::wgs84ToLv03Approx(46.044131, 8.730497, 650.60, east, north, height);
  std::cout  << "East: " << east << " North: " << north
    << " Height: " << height << std::endl;
  if (std::fabs(east - 700000) > 5e-1 || std::fabs(north - 100000) > 5e-1 ||
      std::fabs(height - 600) > 5e-1)
    return 1;
  double latitude, longitude, altitude;
  Geo::lv03ToWgs84Approx(latitude, longitude, altitude, 700000, 100000, 600);
  std::cout << "Latitude: " << latitude << " Longitude: " << longitude
    << " Altitude: " << altitude << std::endl;
  if (std::fabs(latitude - 46.044131) > 5e-1 ||
      std::fabs(longitude - 8.730497) > 5e-1 ||
      std::fabs(altitude - 650.60) > 5e-1)
    return 1;
  Geo::R_ENU_NED& R_ENU = Geo::R_ENU_NED::getInstance();
  Eigen::Matrix3d R = Eigen::Matrix3d::Random();
  if (R * R_ENU * R_ENU != R)
    return 1;
  if (R_ENU * R_ENU * R != R)
    return 1;
  std::cout << R_ENU * R << std::endl;
  double xe, ye, ze;
  Geo::wgs84ToEcef(46.044131, 8.730497, 650.60, xe, ye, ze);
  std::cout << std::fixed << "xe: " << xe << " ye: " << ye << " ze: "
    << ze << std::endl;
  Geo::ecefToWgs84(latitude, longitude, altitude, xe, ye, ze);
  std::cout << "Latitude: " << latitude << " Longitude: " << longitude
    << " Altitude: " << altitude << std::endl;
  if (std::fabs(latitude - 46.044131) > 5e-1 ||
      std::fabs(longitude - 8.730497) > 5e-1 ||
      std::fabs(altitude - 650.60) > 5e-1)
    return 1;
  double xned, yned, zned;
  Geo::ecefToNed(xe, ye, ze, 47.37807435, 8.54664177, 500, xned, yned, zned);
  std::cout << "xned: " << xned << " yned: " << yned << " zned: " << zned
    << std::endl;
  double xecef, yecef, zecef;
  Geo::nedToEcef(xecef, yecef, zecef, 47.37807435, 8.54664177, 500, xned, yned,
    zned);
  if (std::fabs(xecef - xe) > 5e-1 ||
      std::fabs(yecef - ye) > 5e-1 ||
      std::fabs(zecef - ze) > 5e-1)
    return 1;
  std::cout << "xecef: " << xecef << " yecef: " << yecef << " zecef: "
    << zecef << std::endl;
  double xenu, yenu, zenu;
  Geo::ecefToEnu(xe, ye, ze, 47.37807435, 8.54664177, 500, xenu, yenu, zenu);
  std::cout << "xenu: " << xenu << " yenu: " << yenu << " zenu: " << zenu
    << std::endl;
  Geo::enuToEcef(xecef, yecef, zecef, 47.37807435, 8.54664177, 500, xenu, yenu,
    zenu);
  if (std::fabs(xecef - xe) > 5e-1 ||
      std::fabs(yecef - ye) > 5e-1 ||
      std::fabs(zecef - ze) > 5e-1)
    return 1;
  std::cout << "xecef: " << xecef << " yecef: " << yecef << " zecef: "
    << zecef << std::endl;
  Geo::wgs84ToLv03Rigorous(46.044131, 8.730497, 650.60, east, north);
  std::cout  << "East: " << east << " North: " << north
    << " Height: " << height << std::endl;
  return 0;
}
