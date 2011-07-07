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

/** \file POSLVEthernet.h
    \brief This file defines the POSLVEthernet class which implements the
           Ethernet Real-Time and Logging Data communication with the POS LV
  */

#ifndef POSLVETHERNET_H
#define POSLVETHERNET_H

#include <iosfwd>

/** The POSLVEthernet class implements the Ethernet Real-Time and Logging Data
    communication with the Applanix POS LV device.
    \brief Applanix POS LV Ethernet Real-Time and Logging
  */
class POSLVEthernet {
  /** \name Private constructors
    @{
    */
  /// Copy constructor
  POSLVEthernet(const POSLVEthernet& other);
  /// Assignment operator
  POSLVEthernet& operator = (const POSLVEthernet& other);
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
  POSLVEthernet();
  /// Destructor
  ~POSLVEthernet();
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

#endif // POSLVETHERNET_H
