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

#include "types/StationRecord.h"

#include "com/POSLVGroupRead.h"

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

StationRecord::StationRecord() {
}

StationRecord::StationRecord(const StationRecord& other) {
}

StationRecord& StationRecord::operator = (const StationRecord& other) {
  return *this;
}

StationRecord::~StationRecord() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void StationRecord::read(POSLVGroupRead& stream) {
  stream >> mRecordIndexAndFlags;
  stream >> mStationID;
  stream >> mStationHealth;
  stream >> mDistance;
  stream >> mRange;
  stream >> mUSCGIndex;
  stream >> mSeconds;
  stream >> mModulationRate;
}

void StationRecord::read(std::istream& stream) {
}

void StationRecord::write(std::ostream& stream) const {
}

void StationRecord::read(std::ifstream& stream) {
}

void StationRecord::write(std::ofstream& stream) const {
  stream << (uint16_t)mRecordIndexAndFlags;
  stream << " ";
  stream << mStationID;
  stream << " ";
  stream << mStationHealth;
  stream << " ";
  stream << mDistance;
  stream << " ";
  stream << mRange;
  stream << " ";
  stream << (uint16_t)mUSCGIndex;
  stream << " ";
  stream << mSeconds;
  stream << " ";
  stream << (uint16_t)mModulationRate;
  stream << " ";
}

POSLVGroupRead& operator >> (POSLVGroupRead& stream, StationRecord& obj) {
  obj.read(stream);
  return stream;
}
