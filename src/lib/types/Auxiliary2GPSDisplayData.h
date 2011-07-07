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

/** \file Auxiliary2GPSDisplayData.h
    \brief This file defines the Auxiliary2GPSDisplayData class, which
           represents the Auxiliary 2 GPS Display Data message from the Applanix
  */

#ifndef AUXILIARY2GPSDISPLAYDATA_H
#define AUXILIARY2GPSDISPLAYDATA_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class Auxiliary2GPSDisplayData represents the Auxiliary 2 GPS Display
    Data message from the Applanix.
    \brief Auxiliary 2 GPS Display Data message
  */
class Auxiliary2GPSDisplayData :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  Auxiliary2GPSDisplayData();
  /// Copy constructor
  Auxiliary2GPSDisplayData(const Auxiliary2GPSDisplayData& other);
  /// Assignement operator
  Auxiliary2GPSDisplayData& operator = (const Auxiliary2GPSDisplayData& other);
  /// Destructor
  virtual ~Auxiliary2GPSDisplayData();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual Auxiliary2GPSDisplayData* clone() const;
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
  /// Prototype for this group
  static const Auxiliary2GPSDisplayData mProto;
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
  /// Reads from the network
  virtual void read(POSLVGroupRead& stream) throw (IOException);
  /** @}
    */

};

#endif // AUXILIARY2GPSDISPLAYDATA_H
