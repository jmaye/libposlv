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

/** \file GAMSSolutionStatus.h
    \brief This file defines the GAMSSolutionStatus class, which represents the
           GAMS Solution Status message from the Applanix
  */

#ifndef GAMSSOLUTIONSTATUS_H
#define GAMSSOLUTIONSTATUS_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class GAMSSolutionStatus represents the GAMS Solution Status message
    from the Applanix.
    \brief IIN Solution Status message
  */
class GAMSSolutionStatus :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  GAMSSolutionStatus();
  /// Copy constructor
  GAMSSolutionStatus(const GAMSSolutionStatus& other);
  /// Assignement operator
  GAMSSolutionStatus& operator = (const GAMSSolutionStatus& other);
  /// Destructor
  virtual ~GAMSSolutionStatus();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual GAMSSolutionStatus* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 72;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Number of satellites
  uint8_t mNumberOfSatellites;
  /// A priori PDOP
  float mAPrioriPDOP;
  /// Computed antenna separation
  float mComputedAntennaSeparation;
  /// Solution status
  uint8_t mSolutionStatus;
  /// PRN assignment
  uint8_t mau8PRNAssignment[12];
  /// Cycle slip flag
  uint16_t mCycleSlipFlag;
  /// GAMS heading
  double mGAMSHeading;
  /// GAMS heading RMS error
  double mGAMSHeadingRMSError;
  /// Prototype for this group
  static const GAMSSolutionStatus mProto;
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

#endif // GAMSSOLUTIONSTATUS_H
