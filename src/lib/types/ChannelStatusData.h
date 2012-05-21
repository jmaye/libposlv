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

/** \file ChannelStatusData.h
    \brief This file defines the ChannelStatusData class, which is the Channel
           Status for the Applanix
  */

#ifndef CHANNELSTATUSDATA_H
#define CHANNELSTATUSDATA_H

#include "base/Serializable.h"

class BinaryReader;

/** The class ChannelStatusData represents the Channel Status for the Applanix.
    \brief Channel Status
  */
class ChannelStatusData :
  public virtual Serializable {
  /// Reads from UDP connection
  friend BinaryReader& operator >> (BinaryReader& stream,
    ChannelStatusData& obj);
public:
  /** \name Constructors/Destructor
    @{
    */
  /// Default constructor
  ChannelStatusData();
  /// Copy constructor
  ChannelStatusData(const ChannelStatusData& other);
  /// Assignement operator
  ChannelStatusData& operator = (const ChannelStatusData& other);
  /// Destructor
  virtual ~ChannelStatusData();
  /** @}
    */

  /** \name Members
    @{
    */
  /// SVPRN
  uint16_t mSVPRN;
  /// Channel tracking status
  uint16_t mChannelTrackingStatus;
  /// SV azimzuth
  float mSVAzimuth;
  /// SV elevation
  float mSVElevation;
  /// SVL1SNR
  float mSVL1SNR;
  /// SVL2SNR
  float mSVL2SNR;
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
  virtual void read(BinaryReader& stream);
  /** @}
    */

};

#endif // CHANNELSTATUSDATA_H
