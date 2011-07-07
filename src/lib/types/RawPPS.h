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

/** \file RawPPS.h
    \brief This file defines the RawPPS class, which
           represents the Raw PPS message from the Applanix
  */

#ifndef RAWPPS_H
#define RAWPPS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class RawPPS represents the Raw PPS message from the Applanix.
    \brief Raw PPS message
  */
class RawPPS :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  RawPPS();
  /// Copy constructor
  RawPPS(const RawPPS& other);
  /// Assignement operator
  RawPPS& operator = (const RawPPS& other);
  /// Destructor
  virtual ~RawPPS();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual RawPPS* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 36;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Pulse count
  uint32_t mPPSPulseCount;
  /// Prototype for this group
  static const RawPPS mProto;
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

#endif // RAWPPS_H
