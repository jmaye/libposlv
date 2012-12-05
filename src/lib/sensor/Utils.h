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

/** \file Utils.h
    \brief This file defines the Utils namespace which contains useful function
           for the POS LV.
  */

#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <array>
#include <string>

/** The Utils namespace contains useful functions for the Applanix.
    \brief Utilities for the Applanix.
  */
namespace Utils {
  /** \name Type definitions
    @{
    */
  /// Map type
  enum MapType {
    symbolic,
    aerial,
    info
  };
  /// Map format
  enum MapFormat {
    jpg,
    gif,
    png
  };
  /** @}
    */

  /** \name Constants
    @{
    */
  /// Host for fetching maps
  static const std::string serverHost = "map.search.ch";
  /// Port for fetching maps
  static const size_t serverPort = 80;
  /// Map type string
  static const std::vector<std::string> mapTypes = {
    "sym",
    "bg",
    "fg"
  };
  /// Map format string
  static const std::vector<std::string> mapFormats = {
    "jpg",
    "gif",
    "png"
  };
  /// Standard pixel width
  static const size_t pixelWidth = 256;
  /// Standard pixel height
  static const size_t pixelHeight = 256;
  /// Recognized zoom levels
  static const std::array<double, 9> zoomLevels =
  {{512, 128, 32, 8, 4, 2, 1, 0.5, 0.25}};
  /// Min Swiss east coordinate in LV03
  static const double minEast = 468604;
  /// Max Swiss east coordinate in LV03
  static const double maxEast = 853898;
  /// Min Swiss north coordinate in LV03
  static const double minNorth = 60945;
  /// Max Swiss north coordinate in LV03
  static const double maxNorth = 317923;
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Converts WGS84 to LV03
  void WGS84ToLV03(double latitude, double longitude, double altitude,
    double& east, double& north, double& height);
  /// Converts LV03 to WGS84
  void LV03ToWGS84(double& latitude, double& longitude, double& altitude,
    double east, double north, double height);
  /** \brief Converts sexagesimal angle (degrees, minutes and seconds "dd.mmss")
    to decimal angle (degrees) */
  double sexToDecAngle(double dms);
  /** \brief Converts decimal angle (degrees) to sexagesimal angle (degrees,
    minutes and seconds dd.mmss,ss) */
  double decToSexAngle(double dec);
  /**  \brief Converts sexagesimal angle (degrees, minutes and
    seconds dd.mmss,ss) to seconds */
  double sexAngleToSeconds(double dms);
  /// Degrees to radians
  double deg2rad(double deg);
  /// Radians to degrees
  double rad2deg(double rad);
  /// Download map tile centered in east/north to the specified directory
  std::string downloadMapTile(double east, double north, double zoomLevel,
    const std::string& dir = "", size_t width = pixelWidth,
    size_t height = pixelHeight, const MapType type = MapType::symbolic,
    const MapFormat format = MapFormat::png);
  /// Fetch map tile centered in east/north to a string buffer
  void fetchMapTile(double east, double north, double zoomLevel,
    std::string& image, size_t width = pixelWidth, size_t height = pixelHeight,
    const MapType type = MapType::symbolic,
    const MapFormat format = MapFormat::png);
  /** @}
    */

};

#endif // UTILS
