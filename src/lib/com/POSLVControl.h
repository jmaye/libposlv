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

/** \file POSLVControl.h
    \brief This file defines the POSLVControl class which is an interface for
           controlling the Applanix POS LV device
  */

#ifndef POSLVCONTROL_H
#define POSLVCONTROL_H

/** The POSLVControl class is an interface for controlling the Applanix POS LV
    device.
    \brief Applanix POS LV control
  */
class POSLVControl {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  POSLVControl(const POSLVControl& other);
  /// Assignment operator
  POSLVControl& operator = (const POSLVControl& other);
  /** @}
    */

  /** \name Private methods
    @{
    */

  /** @}
    */

  /** \name Private members
    @{
    */

  /** @}
    */

public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  POSLVControl();
  /// Destructor
  ~POSLVControl();
  /** @}
    */

  /** \name Accessors
    @{
    */

  /** @}
    */

  /** \name Methods
    @{
    */

  /** @}
    */

protected:

};

#endif // POSLVCONTROL_H
