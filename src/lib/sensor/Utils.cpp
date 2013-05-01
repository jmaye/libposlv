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

#include "sensor/Utils.h"

#include <cmath>

namespace Utils {

double sexToDecAngle(double dms) {
  double deg = 0, min = 0, sec = 0;
  deg = std::floor(dms);
  min = std::floor((dms - deg) * 100);
  sec = (((dms - deg) * 100) - min) * 100;
  return deg + min / 60 + sec / 3600;
}

double decToSexAngle(double dec) {
  int deg = std::floor(dec);
  int min = std::floor((dec - deg) * 60);
  double sec = (((dec - deg) * 60) - min) * 60;
  return deg + (double)min/100 + (double)sec/10000;
}

double sexAngleToSeconds(double dms) {
  double deg = 0, min = 0, sec = 0;
  deg = std::floor(dms);
  min = std::floor((dms - deg) * 100);
  sec = (((dms - deg) * 100) - min) * 100;
  return sec + (double)min * 60 + (double)deg * 3600;
}

double deg2rad(double deg) {
  return deg * M_PI / 180.0;
}

double rad2deg(double rad) {
  return rad * 180.0 / M_PI;
}

}
