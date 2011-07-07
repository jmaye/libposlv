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

/** \file Diagnostic.h
    \brief This file defines the Diagnostic class, which
           represents the Diagnostic message from the Applanix
  */

#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include "types/Group.h"
#include "types/TimeDistance.h"
#include "exceptions/IOException.h"

/** The class Diagnostic represents the Diagnostic message from the Applanix.
    \brief Diagnostic message
  */
class Diagnostic :
  public Group {
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  Diagnostic();
  /// Copy constructor
  Diagnostic(const Diagnostic& other);
  /// Assignement operator
  Diagnostic& operator = (const Diagnostic& other);
  /// Destructor
  virtual ~Diagnostic();
  /** @}
    */

  /** \name Methods
    @{
    */
  /// Returns a new prototype of this group
  virtual Diagnostic* clone() const;
  /** @}
    */

  /** \name Members
    @{
    */
  /// Nominal number of bytes in the message
  static const uint16_t mByteCount = 276;
  /// Time/Distance field
  TimeDistance mTimeDistance;
  /// Prototype for this group
  static const Diagnostic mProto;
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

#endif // DIAGNOSTIC_H
