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

/** \file BaseGPS2DataStream.h
    \brief This file defines the BaseGPS2DataStream class, which
           represents the Base GPS 2 Data Stream message from the Applanix
  */

#ifndef BASEGPS2DATASTREAM_H
#define BASEGPS2DATASTREAM_H

#include "types/Group.h"
#include "types/TimeDistance.h"

/** The class BaseGPS2DataStream represents the Base GPS 2 Data Stream message
    from the Applanix.
    \brief Base GPS 2 Data Stream message
  */
class BaseGPS2DataStream :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  BaseGPS2DataStream();
  /// Copy constructor
  BaseGPS2DataStream(const BaseGPS2DataStream& other);
  /// Assignement operator
  BaseGPS2DataStream& operator = (const BaseGPS2DataStream& other);
  /// Destructor
  virtual ~BaseGPS2DataStream();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual BaseGPS2DataStream* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Time/Distance field of the message
  TimeDistance mTimeDistance;
  /// Reserved stuff
  uint8_t mReserved[6];
  /// Variable message length
  uint16_t mVariableMsgByteCount;
  /// Data
  uint8_t* mGPSReceiverRawData;
  /// Prototype for this group
  static const BaseGPS2DataStream mProto;
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
  virtual void read(BinaryReader& stream);
  /// Writes to the network
  virtual void write(BinaryWriter& stream) const;
  /** @}
    */

protected:
};

#endif // BASEGPS2DATASTREAM_H
