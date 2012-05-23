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

#include "types/PPSTimeRecoveryStatus.h"

#include "base/BinaryReader.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const PPSTimeRecoveryStatus PPSTimeRecoveryStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

PPSTimeRecoveryStatus::PPSTimeRecoveryStatus() :
    Group(7) {
}

PPSTimeRecoveryStatus::PPSTimeRecoveryStatus(const PPSTimeRecoveryStatus&
    other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mPPSCount(other.mPPSCount),
    mTimeSynchroStatus(other.mTimeSynchroStatus) {
}

PPSTimeRecoveryStatus& PPSTimeRecoveryStatus::operator =
    (const PPSTimeRecoveryStatus& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    mPPSCount = other.mPPSCount;
    mTimeSynchroStatus = other.mTimeSynchroStatus;
  }
  return *this;
}

PPSTimeRecoveryStatus::~PPSTimeRecoveryStatus() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void PPSTimeRecoveryStatus::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("PPSTimeRecoveryStatus::read(): wrong byte count");
  stream >> mTimeDistance;
  stream >> mPPSCount;
  stream >> mTimeSynchroStatus;
}

void PPSTimeRecoveryStatus::write(BinaryWriter& stream) const {
}

void PPSTimeRecoveryStatus::read(std::istream& stream) {
}

void PPSTimeRecoveryStatus::write(std::ostream& stream) const {
}

void PPSTimeRecoveryStatus::read(std::ifstream& stream) {
}

void PPSTimeRecoveryStatus::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mPPSCount;
  stream << (uint16_t)mTimeSynchroStatus;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

PPSTimeRecoveryStatus* PPSTimeRecoveryStatus::clone() const {
  return new PPSTimeRecoveryStatus(*this);
}
