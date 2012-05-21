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
  mChecksum += mTypeID;
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("VersionStatistics::read(): wrong byte count");
  mChecksum += mByteCount;
  stream >> mTimeDistance;
  mChecksum += mTimeDistance.mChecksum;
  for (size_t i = 0; i < 120; i++)
    stream >> mSystemVersion[i];
  for (size_t i = 1; i < 120; i += 2)
    mChecksum += mSystemVersion[i] << 8 | mSystemVersion[i - 1];
  for (size_t i = 0; i < 80; i++)
    stream >> mPrimaryGPSVersion[i];
  for (size_t i = 1; i < 80; i += 2)
    mChecksum += mPrimaryGPSVersion[i] << 8 | mPrimaryGPSVersion[i - 1];
  for (size_t i = 0; i < 80; i++)
    stream >> mSecondaryGPSversion[i];
  for (size_t i = 1; i < 80; i += 2)
    mChecksum += mSecondaryGPSversion[i] << 8 | mSecondaryGPSversion[i - 1];
  stream >> mTotalHours;
  mChecksum += ((uint16_t*)&mTotalHours)[0];
  mChecksum += ((uint16_t*)&mTotalHours)[1];
  stream >> mNumberOfRuns;
  mChecksum += ((uint16_t*)&mNumberOfRuns)[0];
  mChecksum += ((uint16_t*)&mNumberOfRuns)[1];
  stream >> mAverageLengthOfRun;
  mChecksum += ((uint16_t*)&mAverageLengthOfRun)[0];
  mChecksum += ((uint16_t*)&mAverageLengthOfRun)[1];
  stream >> mLongestRun;
  mChecksum += ((uint16_t*)&mLongestRun)[0];
  mChecksum += ((uint16_t*)&mLongestRun)[1];
  stream >> mCurrentRun;
  mChecksum += ((uint16_t*)&mCurrentRun)[0];
  mChecksum += ((uint16_t*)&mCurrentRun)[1];
  uint16_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("VersionStatistics::read(): wrong pad");
  mChecksum += pad;
  mChecksum = 65536 - mChecksum;
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
