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

/** \file GeneralStatusFDIR.h
    \brief This file defines the GeneralStatusFDIR class, which
           represents the General and FDIR Status message from the Applanix
  */

#ifndef GENERALSTATUSFDIR_H
#define GENERALSTATUSFDIR_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class GeneralStatusFDIR represents the General and FDIR Status message
    from the Applanix.
    \brief General and FDIR Status message
  */
class GeneralStatusFDIR :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  GeneralStatusFDIR();
  /// Copy constructor
  GeneralStatusFDIR(const GeneralStatusFDIR& other);
  /// Assignement operator
  GeneralStatusFDIR& operator = (const GeneralStatusFDIR& other);
  /// Destructor
  virtual ~GeneralStatusFDIR();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual GeneralStatusFDIR* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 60;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// General status A
  uint32_t mGeneralStatusA;
  /// General status B
  uint32_t mGeneralStatusB;
  /// General status C
  uint32_t mGeneralStatusC;
  /// FDIR level 1 status
  uint32_t mFDIRLevel1Status;
  /// FDIR level 1 failures
  uint16_t mFDIRLevel1Failures;
  /// FDIR level 2 status
  uint16_t mFDIRLevel2Status;
  /// FDIR level 3 status
  uint16_t mFDIRLevel3Status;
  /// FDIR level 4 status
  uint16_t mFDIRLevel4Status;
  /// FDIR level 5 status
  uint16_t mFDIRLevel5Status;
  /// Extended status
  uint32_t mExtendedStatus;
  /// Prototype for this group
  static const GeneralStatusFDIR mProto;
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

#endif // GENERALSTATUSFDIR_H
