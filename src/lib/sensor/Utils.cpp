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

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

void WGS84ToLV03(double latitude, double longitude, double altitude,
    double& east, double& north, double& height) {
  latitude = decToSexAngle(latitude);
  longitude = decToSexAngle(longitude);
  latitude = sexAngleToSeconds(latitude);
  longitude = sexAngleToSeconds(longitude);
  double latitudeAux = (latitude - 169028.66) / 10000;
  double longitudeAux = (longitude - 26782.5) / 10000;
  east = 600072.37 + 211455.93 * longitudeAux - 10938.51 * longitudeAux *
    latitudeAux - 0.36 * longitudeAux * latitudeAux * latitudeAux
    - 44.54 * longitudeAux * longitudeAux * longitudeAux;
  north = 200147.07 + 308807.95 * latitudeAux + 3745.25 * longitudeAux *
    longitudeAux + 76.63 * latitudeAux * latitudeAux - 194.56 * longitudeAux *
    longitudeAux * latitudeAux + 119.79 * latitudeAux * latitudeAux *
    latitudeAux;
  height = altitude - 49.55 + 2.73 * longitudeAux + 6.94 * latitudeAux;
}

void LV03ToWGS84(double& latitude, double& longitude, double& altitude,
    double east, double north, double height) {
  double eastAux = (east - 600000) / 1000000;
  double northAux = (north - 200000) / 1000000;
  longitude = 2.6779094 + 4.728982 * eastAux + 0.791484 * eastAux * northAux +
    0.1306 * eastAux * northAux * northAux - 0.0436 * eastAux * eastAux *
    eastAux;
  longitude = longitude * 100 / 36;
  latitude = 16.9023892 + 3.238272 * northAux - 0.270978 * eastAux * eastAux
    - 0.002528 * northAux * northAux - 0.0447 * eastAux * eastAux * northAux
    - 0.0140 * northAux * northAux * northAux;
  latitude = latitude * 100 / 36;
  altitude = height + 49.55 - 12.60 * eastAux - 22.64 * northAux;
}

double sexToDecAngle(double dms) {
  double deg = 0, min = 0, sec = 0;
  deg = floor(dms);
  min = floor((dms - deg) * 100);
  sec = (((dms - deg) * 100) - min) * 100;
  return deg + min / 60 + sec / 3600;
}

double decToSexAngle(double dec) {
  int deg = floor(dec);
  int min = floor((dec - deg) * 60);
  double sec = (((dec - deg) * 60) - min) * 60;
  return deg + (double)min/100 + (double)sec/10000;
}

double sexAngleToSeconds(double dms) {
  double deg = 0, min = 0, sec = 0;
  deg = floor(dms);
  min = floor((dms - deg) * 100);
  sec = (((dms - deg) * 100) - min) * 100;
  return sec + (double)min * 60 + (double)deg * 3600;
}

}
