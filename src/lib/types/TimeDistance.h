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

/** \file TimeDistance.h
    \brief This file defines the TimeDistance class, which is a Time/Distance
           record of the Applanix
  */

#ifndef TIMEDISTANCE_H
#define TIMEDISTANCE_H

#include "types/Group.h"

/** The class TimeDistance represents a Time/Distance record of the Applanix.
    \brief Time/Distance field
  */
class TimeDistance :
  public Serializable {
  /// Reads from UDP
  friend POSLVGroupRead& operator >> (POSLVGroupRead& stream,
    TimeDistance& obj);
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  TimeDistance();
  /// Copy constructor
  TimeDistance(const TimeDistance& other);
  /// Assignement operator
  TimeDistance& operator = (const TimeDistance& other);
  /// Destructor
  virtual ~TimeDistance();
  /** @}
    */

  /** \name Members
    @{
    */
  /// Time 1
  double mTime1;
  /// Time 2 
  double mTime2;
  /// Distance tag
  double mDistanceTag;
  /// Time type
  uint8_t mTimeType;
  /// Distance type
  uint8_t mDistanceType;
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
  virtual void read(POSLVGroupRead& stream);
  /** @}
    */

};

#endif // TIMEDISTANCE_H
