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

#include "types/VersionStatistics.h"

#include "com/Connection.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const VersionStatistics VersionStatistics::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

VersionStatistics::VersionStatistics() :
  Group(99) {
}

VersionStatistics::VersionStatistics(const VersionStatistics& other) :
  Group(other) {
}

VersionStatistics& VersionStatistics::operator =
  (const VersionStatistics& other) {
  this->Group::operator=(other);
  return *this;
}

VersionStatistics::~VersionStatistics() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void VersionStatistics::read(Connection &stream) throw(IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("VersionStatistics::read(): wrong byte count");

  stream >> mTimeDistance;
  for (size_t i = 0; i < 120; i++)
    stream >> mau8SystemVersion[i];
  for (size_t i = 0; i < 80; i++)
    stream >> mau8PrimaryGPSVersion[i];
  for (size_t i = 0; i < 80; i++)
    stream >> mau8SecondaryGPSversion[i];
  stream >> mTotalHours;
  stream >> mNumberOfRuns;
  stream >> mAverageLengthOfRun;
  stream >> mLongestRun;
  stream >> mCurrentRun;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("VersionStatistics::read(): wrong pad");
}

void VersionStatistics::read(std::istream& stream) {
}

void VersionStatistics::write(std::ostream& stream) const {
}

void VersionStatistics::read(std::ifstream& stream) {
}

void VersionStatistics::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  std::string outputStr1((const char*)mau8SystemVersion);
  stream << outputStr1;
  stream << " ";
  std::string outputStr2((const char*)mau8PrimaryGPSVersion);
  stream << outputStr2;
  stream << " ";
  std::string outputStr3((const char*)mau8SecondaryGPSversion);
  stream << outputStr3;
  stream << " ";
  stream << mTotalHours;
  stream << " ";
  stream << mNumberOfRuns;
  stream << " ";
  stream << mAverageLengthOfRun;
  stream << " ";
  stream << mLongestRun;
  stream << " ";
  stream << mCurrentRun;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

VersionStatistics* VersionStatistics::clone() const {
  return new VersionStatistics(*this);
}
