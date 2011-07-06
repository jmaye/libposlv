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

#include "com/Connection.h"

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
  Group(other) {
}

IINSolutionStatus& IINSolutionStatus::operator =
  (const IINSolutionStatus& other) {
  this->Group::operator=(other);
  return *this;
}

IINSolutionStatus::~IINSolutionStatus() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void IINSolutionStatus::read(Connection& stream) throw(IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("IINSolutionStatus::read(): wrong byte count");

  stream >> mTimeDistance;
  stream >> mNumberOfSatellites;
  stream >> mAPrioriPDOP;
  stream >> mBaselineLength;
  stream >> mIINProcessingStatus;
  for (size_t i = 0; i < 12; i++)
    stream >> mau8PRNAssignment[i];
  stream >> mL1CycleSlipFlag;
  stream >> mL2CycleSlipFlag;

  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("IINSolutionStatus::read(): wrong pad");
}

void IINSolutionStatus::read(std::istream& stream) {
}

void IINSolutionStatus::write(std::ostream& stream) const {
}

void IINSolutionStatus::read(std::ifstream& stream) {
}

void IINSolutionStatus::write(std::ofstream& stream) const {
  stream << mTypeID;
//  stream << " ";
//  stream << mTimeDistance;
//  stream << mu16NumberOfSatellites;
//  stream << " ";
//  stream << mf32APrioriPDOP;
//  stream << " ";
//  stream << mf32BaselineLength;
//  stream << " ";
//  stream << mu16IINProcessingStatus;
//  stream << " ";
//  for (uint8_t i = 0; i < 12; i++) {
//    stream << hex << (uint16_t)mau8PRNAssignment[i] << dec;
//    stream << " ";
//  }
//  stream << mu16L1CycleSlipFlag;
//  stream << " ";
//  stream << mu16L2CycleSlipFlag;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

IINSolutionStatus* IINSolutionStatus::clone() const {
  return new IINSolutionStatus(*this);
}
