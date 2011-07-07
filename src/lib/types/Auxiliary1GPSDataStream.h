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

/** \file Auxiliary1GPSDataStream.h
    \brief This file defines the Auxiliary1GPSDataStream class, which
           represents the Auxiliary 1 GPS Data Stream message from the Applanix
  */

#ifndef AUXILIARY1GPSDATASTREAM_H
#define AUXILIARY1GPSDATASTREAM_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class Auxiliary1GPSDataStream represents the Auxiliary 1 GPS Data
    Stream message from the Applanix.
    \brief Auxiliary 1 GPS Data Stream message
  */
class Auxiliary1GPSDataStream :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  Auxiliary1GPSDataStream();
  /// Copy constructor
  Auxiliary1GPSDataStream(const Auxiliary1GPSDataStream& other);
  /// Assignement operator
  Auxiliary1GPSDataStream& operator = (const Auxiliary1GPSDataStream& other);
  /// Destructor
  virtual ~Auxiliary1GPSDataStream();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual Auxiliary1GPSDataStream* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Time/Distance field of the message
  TimeDistance mTimeDistance;
  //// Reserved stuff
  uint8_t mau8Reserved[6];
  /// Variable message length
  uint16_t mVariableMsgByteCount;
  /// Data
  uint8_t* mau8GPSReceiverRawData;
  /// Prototype for this group
  static const Auxiliary1GPSDataStream mProto;
 /** @}
    */

public:
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

protected:
};

#endif // AUXILIARY1GPSDATASTREAM_H
