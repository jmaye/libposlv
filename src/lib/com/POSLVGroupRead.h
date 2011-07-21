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

/** \file POSLVGroupRead.h
    \brief This file defines the POSLVGroupRead class which is an interface for
           all groups reading from the Applanix device.
  */

#ifndef POSLVGROUPREAD_H
#define POSLVGROUPREAD_H

#include "com/BinaryReader.h"
#include "types/Group.h"
#include "exceptions/IOException.h"

/** The POSLVGroupRead class is an interface for all groups reading from the
    Applanix device.
    \brief Applanix POS LV reading interface for groups
  */
class POSLVGroupRead :
  public BinaryReader {
public:
  /** \name Constructors/destructor
    @{
    */
  /// Default constructor
  POSLVGroupRead();
  /// Copy constructor
  POSLVGroupRead(const POSLVGroupRead& other);
  /// Assignment operator
  POSLVGroupRead& operator = (const POSLVGroupRead& other);
  /// Destructor
  virtual ~POSLVGroupRead();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Reads a group from the network
  const Group* readGroup() throw (IOException);
  /** @}
    */

protected:
  /** \name Protected methods
    @{
    */
  /// Reads the start of a group
  void readStartGroup();
  /// Reads the end of a group
  std::string readEndGroup();
  /** @}
    */

};

#endif // POSLVGROUPREAD
