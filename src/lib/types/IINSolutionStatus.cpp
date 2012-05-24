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

#include "types/IINSolutionStatus.h"

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const IINSolutionStatus IINSolutionStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

IINSolutionStatus::IINSolutionStatus() :
    Group(20) {
}

IINSolutionStatus::IINSolutionStatus(const IINSolutionStatus& other) :
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mNumberOfSatellites(other.mNumberOfSatellites),
    mAPrioriPDOP(other.mAPrioriPDOP),
    mBaselineLength(other.mBaselineLength),
    mIINProcessingStatus(other.mIINProcessingStatus),
    mL1CycleSlipFlag(other.mL1CycleSlipFlag),
    mL2CycleSlipFlag(other.mL2CycleSlipFlag) {
  memcpy(mPRNAssignment, other.mPRNAssignment, sizeof(mPRNAssignment));
}

IINSolutionStatus& IINSolutionStatus::operator =
    (const IINSolutionStatus& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    mNumberOfSatellites = other.mNumberOfSatellites;
    mAPrioriPDOP = other.mAPrioriPDOP;
    mBaselineLength = other.mBaselineLength;
    mIINProcessingStatus = other.mIINProcessingStatus;
    memcpy(mPRNAssignment, other.mPRNAssignment, sizeof(mPRNAssignment));
    mL1CycleSlipFlag = other.mL1CycleSlipFlag;
    mL2CycleSlipFlag = other.mL2CycleSlipFlag;
  }
  return *this;
}

IINSolutionStatus::~IINSolutionStatus() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void IINSolutionStatus::read(BinaryReader& stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("IINSolutionStatus::read(): wrong byte count");
  stream >> mTimeDistance;
  stream >> mNumberOfSatellites;
  stream >> mAPrioriPDOP;
  stream >> mBaselineLength;
  stream >> mIINProcessingStatus;
  for (size_t i = 0; i < sizeof(mPRNAssignment) /  sizeof(mPRNAssignment[0]);
      i++)
    stream >> mPRNAssignment[i];
  stream >> mL1CycleSlipFlag;
  stream >> mL2CycleSlipFlag;
}

void IINSolutionStatus::write(BinaryWriter& stream) const {
}

void IINSolutionStatus::read(std::istream& stream) {
}

void IINSolutionStatus::write(std::ostream& stream) const {
}

void IINSolutionStatus::read(std::ifstream& stream) {
}

void IINSolutionStatus::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mNumberOfSatellites;
  stream << " ";
  stream << mAPrioriPDOP;
  stream << " ";
  stream << mBaselineLength;
  stream << " ";
  stream << mIINProcessingStatus;
  stream << " ";
  for (size_t i = 0; i < 12; i++) {
    stream << (uint16_t)mPRNAssignment[i];
    stream << " ";
  }
  stream << mL1CycleSlipFlag;
  stream << " ";
  stream << mL2CycleSlipFlag;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

IINSolutionStatus* IINSolutionStatus::clone() const {
  return new IINSolutionStatus(*this);
}
