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

/** \file IINSolutionStatus.h
    \brief This file defines the IINSolutionStatus class, which
           represents the IIN Solution Status message from the Applanix
  */

#ifndef IINSOLUTIONSTATUS_H
#define IINSOLUTIONSTATUS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class IINSolutionStatus represents the IIN Solution Status message from
    the Applanix.
    \brief IIN Solution Status message
  */
class IINSolutionStatus :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  IINSolutionStatus();
  /// Copy constructor
  IINSolutionStatus(const IINSolutionStatus& other);
  /// Assignement operator
  IINSolutionStatus& operator = (const IINSolutionStatus& other);
  /// Destructor
  virtual ~IINSolutionStatus();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual IINSolutionStatus* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 60;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Number of satellites
  uint16_t mNumberOfSatellites;
  /// A priori PDOP
  float mAPrioriPDOP;
  /// Baseline length
  float mBaselineLength;
  /// Processing status
  uint16_t mIINProcessingStatus;
  /// PRN assignment
  uint8_t mau8PRNAssignment[12];
  /// L1 cycle slip flag
  uint16_t mL1CycleSlipFlag;
  /// L2 cycle slip flag
  uint16_t mL2CycleSlipFlag;
  /// Prototype for this group
  static const IINSolutionStatus mProto;
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

#endif // IINSOLUTIONSTATUS_H
