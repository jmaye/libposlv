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

/** \file POSLVDisplay.h
    \brief This file defines the POSLVDisplay class intended for displaying
           Applanix POS LV data
  */

#ifndef POSLVDISPLAY_H
#define POSLVDISPLAY_H


/** The POSLVDisplay class implements the UDP communication with the Applanix
    POS LV device, mainly intended for displaying data in a GUI.
    \brief Applanix POS LV display
  */
class POSLVDisplay {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  POSLVDisplay(const POSLVDisplay& other);

  /// Assignment operator
  POSLVDisplay& operator = (const POSLVDisplay& other);
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
  POSLVDisplay();
  /// Destructor
  ~POSLVDisplay();
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

#endif // POSLVDISPLAY_H
