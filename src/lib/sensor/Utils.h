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

/** The Utils namespace contains useful functions for the Applanix.
    \brief Utilities for the Applanix.
  */
namespace Utils {

  /** \name Methods
    @{
    */
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
  /** @}
    */

};

#endif // UTILS_H
