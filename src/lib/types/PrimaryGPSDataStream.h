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

/** \file PrimaryGPSDataStream.h
    \brief This file defines the PrimaryGPSDataStream class, which
           represents the Primary GPS Data Stream message from the Applanix
  */

#ifndef PRIMARYGPSDATASTREAM_H
#define PRIMARYGPSDATASTREAM_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class PrimaryGPSDataStream represents the Primary GPS Data Stream
    message from the Applanix.
    \brief Primary GPS Data Stream message
  */
class PrimaryGPSDataStream :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  PrimaryGPSDataStream();
  /// Copy constructor
  PrimaryGPSDataStream(const PrimaryGPSDataStream& other);
  /// Assignement operator
  PrimaryGPSDataStream& operator = (const PrimaryGPSDataStream& other);
  /// Destructor
  virtual ~PrimaryGPSDataStream();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual PrimaryGPSDataStream* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Time/Distance field of the message
  TimeDistance mTimeDistance;
  /// Receiver type
  uint16_t mGPSReceiverType;
  /// Reserved stuff
  uint32_t mReserved;
  /// Variable message length
  uint16_t mVariableMsgByteCount;
  /// Data
  uint8_t* mau8GPSReceiverRawData;
  /// Prototype of this group
  static const PrimaryGPSDataStream mProto;
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

};

#endif // PRIMARYGPSDATASTREAM_H
