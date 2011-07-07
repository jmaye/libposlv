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

/** \file RawDMIDataStream.h
    \brief This file defines the RawDMIDataStream class, which
           represents the Raw DMI Data Stream message from the Applanix
  */

#ifndef RAWDMIDATASTREAM_H
#define RAWDMIDATASTREAM_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"


/** The class RawDMIDataStream represents the Raw DMI Data Stream message from
    the Applanix.
    \brief Raw DMI Data Stream message
  */
class RawDMIDataStream :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  RawDMIDataStream();
  /// Copy constructor
  RawDMIDataStream(const RawDMIDataStream& other);
  /// Assignement operator
  RawDMIDataStream& operator = (const RawDMIDataStream& other);
  /// Destructor
  virtual ~RawDMIDataStream();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual RawDMIDataStream* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 48;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Up down pulse count
  int32_t mUpDownPulseCount;
  /// Rectified pulse count
  uint32_t mRectifiedPulseCount;
  /// Event count
  int32_t mEventCount;
  /// Reserved count
  uint32_t mReservedCount;
  /// Prototype for this group
  static const RawDMIDataStream mProto;
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
  virtual void read(POSLVGroupRead& stream) throw (IOException);
  /** @}
    */

};

#endif // RAWDMIDATASTREAM_H
