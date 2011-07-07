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

#include "types/GAMSSolutionStatus.h"

#include "com/POSLVGroupRead.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const GAMSSolutionStatus GAMSSolutionStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

GAMSSolutionStatus::GAMSSolutionStatus() :
  Group(9) {
}

GAMSSolutionStatus::GAMSSolutionStatus(const GAMSSolutionStatus& other) :
  Group(other) {
}

GAMSSolutionStatus& GAMSSolutionStatus::operator =
  (const GAMSSolutionStatus& other) {
  this->Group::operator=(other);
  return *this;
}

GAMSSolutionStatus::~GAMSSolutionStatus() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void GAMSSolutionStatus::read(POSLVGroupRead& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("GAMSSolutionStatus::read(): wrong byte count");

  stream >> mTimeDistance;
  stream >> mNumberOfSatellites;
  stream >> mAPrioriPDOP;
  stream >> mComputedAntennaSeparation;
  stream >> mSolutionStatus;
  for (size_t i = 0; i < 12; i++)
    stream >> mau8PRNAssignment[i];
  stream >> mCycleSlipFlag;
  stream >> mGAMSHeading;
  stream >> mGAMSHeadingRMSError;

  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("GAMSSolutionStatus::read(): wrong pad");
}

void GAMSSolutionStatus::read(std::istream& stream) {
}

void GAMSSolutionStatus::write(std::ostream& stream) const {
}

void GAMSSolutionStatus::read(std::ifstream& stream) {
}

void GAMSSolutionStatus::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << (uint16_t)mNumberOfSatellites;
  stream << " ";
  stream << mAPrioriPDOP;
  stream << " ";
  stream << mComputedAntennaSeparation;
  stream << " ";
  stream << (uint16_t)mSolutionStatus;
  stream << " ";
  for (uint32_t i = 0; i < 12; i++) {
    stream << (uint16_t)mau8PRNAssignment[i];
    stream << " ";
  }
  stream << std::hex << mCycleSlipFlag << std::dec;
  stream << " ";
  stream << mGAMSHeading;
  stream << " ";
  stream << mGAMSHeadingRMSError;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

GAMSSolutionStatus* GAMSSolutionStatus::clone() const {
  return new GAMSSolutionStatus(*this);
}
