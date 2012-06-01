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

#include <cstring>

#include "base/BinaryReader.h"
#include "base/BinaryWriter.h"
#include "exceptions/IOException.h"

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
    Group(other),
    mTimeDistance(other.mTimeDistance),
    mTotalHours(other.mTotalHours),
    mNumberOfRuns(other.mNumberOfRuns),
    mAverageLengthOfRun(other.mAverageLengthOfRun),
    mLongestRun(other.mLongestRun),
    mCurrentRun(other.mCurrentRun) {
  memcpy(mSystemVersion, other.mSystemVersion, sizeof(mSystemVersion));
  memcpy(mPrimaryGPSVersion, other.mPrimaryGPSVersion,
    sizeof(mPrimaryGPSVersion));
  memcpy(mSecondaryGPSversion, other.mSecondaryGPSversion,
    sizeof(mSecondaryGPSversion));
}

VersionStatistics& VersionStatistics::operator =
    (const VersionStatistics& other) {
  if (this != &other) {
    Group::operator=(other);
    mTimeDistance = other.mTimeDistance;
    memcpy(mSystemVersion, other.mSystemVersion, sizeof(mSystemVersion));
    memcpy(mPrimaryGPSVersion, other.mPrimaryGPSVersion,
      sizeof(mPrimaryGPSVersion));
    memcpy(mSecondaryGPSversion, other.mSecondaryGPSversion,
      sizeof(mSecondaryGPSversion));
    mTotalHours = other.mTotalHours;
    mNumberOfRuns = other.mNumberOfRuns;
    mAverageLengthOfRun = other.mAverageLengthOfRun;
    mLongestRun = other.mLongestRun;
    mCurrentRun = other.mCurrentRun;
  }
  return *this;
}

VersionStatistics::~VersionStatistics() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void VersionStatistics::read(BinaryReader &stream) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("VersionStatistics::read(): wrong byte count");
  stream >> mTimeDistance;
  for (size_t i = 0; i < sizeof(mSystemVersion) / sizeof(mSystemVersion[0]);
      i++)
    stream >> mSystemVersion[i];
  for (size_t i = 0; i < sizeof(mPrimaryGPSVersion) /
      sizeof(mPrimaryGPSVersion[0]); i++)
    stream >> mPrimaryGPSVersion[i];
  for (size_t i = 0; i < sizeof(mSecondaryGPSversion) /
      sizeof(mSecondaryGPSversion[0]); i++)
    stream >> mSecondaryGPSversion[i];
  stream >> mTotalHours;
  stream >> mNumberOfRuns;
  stream >> mAverageLengthOfRun;
  stream >> mLongestRun;
  stream >> mCurrentRun;
}

void VersionStatistics::write(BinaryWriter &stream) const {
  stream << mTypeID;
  stream << mByteCount;
  stream << mTimeDistance;
  for (size_t i = 0; i < sizeof(mSystemVersion) / sizeof(mSystemVersion[0]);
      i++)
    stream << mSystemVersion[i];
  for (size_t i = 0; i < sizeof(mPrimaryGPSVersion) /
      sizeof(mPrimaryGPSVersion[0]); i++)
    stream << mPrimaryGPSVersion[i];
  for (size_t i = 0; i < sizeof(mSecondaryGPSversion) /
      sizeof(mSecondaryGPSversion[0]); i++)
    stream << mSecondaryGPSversion[i];
  stream << mTotalHours;
  stream << mNumberOfRuns;
  stream << mAverageLengthOfRun;
  stream << mLongestRun;
  stream << mCurrentRun;
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
  std::string outputStr1((const char*)mSystemVersion);
  stream << outputStr1;
  stream << " ";
  std::string outputStr2((const char*)mPrimaryGPSVersion);
  stream << outputStr2;
  stream << " ";
  std::string outputStr3((const char*)mSecondaryGPSversion);
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
