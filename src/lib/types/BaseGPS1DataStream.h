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

/** \file BaseGPS1DataStream.h
    \brief This file defines the BaseGPS1DataStream class, which
           represents the Base GPS 1 Data Stream message from the Applanix
  */

#ifndef BASEGPS1DATASTREAM_H
#define BASEGPS1DATASTREAM_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class BaseGPS1DataStream represents the Base GPS 1 Data Stream message
    from the Applanix.
    \brief Base GPS 1 Data Stream message
  */
class BaseGPS1DataStream :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  BaseGPS1DataStream();
  /// Copy constructor
  BaseGPS1DataStream(const BaseGPS1DataStream& other);
  /// Assignement operator
  BaseGPS1DataStream& operator = (const BaseGPS1DataStream& other);
  /// Destructor
  virtual ~BaseGPS1DataStream();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual BaseGPS1DataStream* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Time/Distance field of the message
  TimeDistance mTimeDistance;
  /// Reserved stuff
  uint8_t mau8Reserved[6];
  /// Variable message length
  uint16_t mVariableMsgByteCount;
  /// Data
  uint8_t* mau8GPSReceiverRawData;
  /// Prototype for this group
  static const BaseGPS1DataStream mProto;
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

#endif // BASEGPS1DATASTREAM_H
