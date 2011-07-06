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

/** \file Auxiliary1GPSDisplayData.h
    \brief This file defines the Auxiliary1GPSDisplayData class, which
           represents the Auxiliary 1 GPS Display Data message from the Applanix
  */

#ifndef AUXILIARY1GPSDISPLAYDATA_H
#define AUXILIARY1GPSDISPLAYDATA_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class Auxiliary1GPSDisplayData represents the Auxiliary 1 GPS Display
    Data message from the Applanix.
    \brief Auxiliary 1 GPS Display Data message
  */
class Auxiliary1GPSDisplayData :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  Auxiliary1GPSDisplayData();
  /// Copy constructor
  Auxiliary1GPSDisplayData(const Auxiliary1GPSDisplayData& other);
  /// Assignement operator
  Auxiliary1GPSDisplayData& operator = (const Auxiliary1GPSDisplayData& other);
  /// Destructor
  virtual ~Auxiliary1GPSDisplayData();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual Auxiliary1GPSDisplayData* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Time/Distance field of the message
  TimeDistance mTimeDistance;
  /// Reserved bytes
  uint8_t mau8Reserved[6];
  /// Variable message byte count
  uint16_t mVariableMsgByteCount;
  /// GPS raw data
  uint8_t* mau8GPSRawData;
  /** @}
    */

protected:
  /** \name Stream methods
    @{
    */
  /// Reads from standard input
  virtual void read(std::istream& stream);
  /// Writes to standard output
  virtual void write(std::ostream& stream) const ;
  /// Reads from a file
  virtual void read(std::ifstream& stream);
  /// Writes to a file
  virtual void write(std::ofstream& stream) const;
  /// Reads from the network
  virtual void read(Connection& stream) throw (IOException);
  /** @}
    */

  /** \name Protected members
    @{
    */
  /// Prototype for this group
  static const Auxiliary1GPSDisplayData mProto;
  /** @}
    */

};

#endif // AUXILIARY1GPSDISPLAYDATA_H
