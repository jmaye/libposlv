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

#include "types/ChannelStatusData.h"

#include "com/Connection.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

ChannelStatusData::ChannelStatusData() {
}

ChannelStatusData::ChannelStatusData(const ChannelStatusData& other) {
}

ChannelStatusData& ChannelStatusData::operator =
  (const ChannelStatusData& other) {
  return *this;
}

ChannelStatusData::~ChannelStatusData() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void ChannelStatusData::read(Connection& stream) {
  stream >> mSVPRN;
  stream >> mChannelTrackingStatus;
  stream >> mSVAzimuth;
  stream >> mSVElevation;
  stream >> mSVL1SNR;
  stream >> mSVL2SNR;
}

void ChannelStatusData::read(std::istream& stream) {
}

void ChannelStatusData::write(std::ostream& stream) const {
}

void ChannelStatusData::read(std::ifstream& stream) {
}

void ChannelStatusData::write(std::ofstream& stream) const {
//  stream << mu16SVPRN;
//  stream << " ";
//  stream << mu16ChannelTrackingStatus;
//  stream << " ";
//  stream << mf32SVAzimuth;
//  stream << " ";
//  stream << mf32SVElevation;
//  stream << " ";
//  stream << mf32SVL1SNR;
//  stream << " ";
//  stream << mf32SVL2SNR;
}

Connection& operator >> (Connection& stream, ChannelStatusData& obj) {
  obj.read(stream);
  return stream;
}
