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

#include "types/LoggingParamStatus.h"

#include "com/POSLVGroupRead.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const LoggingParamStatus LoggingParamStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

LoggingParamStatus::LoggingParamStatus() :
  Group(8) {
}

LoggingParamStatus::LoggingParamStatus(const LoggingParamStatus& other) :
  Group(other) {
}

LoggingParamStatus& LoggingParamStatus::operator =
  (const LoggingParamStatus& other) {
  this->Group::operator=(other);
  return *this;
}

LoggingParamStatus::~LoggingParamStatus() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void LoggingParamStatus::read(POSLVGroupRead& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("LoggingParamStatus::read(): wrong byte count");

  stream >> mTimeDistance;
  stream >> mDiskKbytesRemaining;
  stream >> mDiskKbytesLogged;
  stream >> mDiskLoggingTimeRemaining;
  stream >> mDiskKbytesTotal;
  stream >> mLoggingState;

  uint8_t pad;
  stream >> pad;
  if (pad != 0)
    throw IOException("LoggingParamStatus::read(): wrong pad");
}


void LoggingParamStatus::read(std::istream& stream) {
}

void LoggingParamStatus::write(std::ostream& stream) const {
}

void LoggingParamStatus::read(std::ifstream& stream) {
}

void LoggingParamStatus::write(std::ofstream& stream) const {
  stream << mTypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mDiskKbytesRemaining;
  stream << " ";
  stream << mDiskKbytesLogged;
  stream << " ";
  stream << mDiskLoggingTimeRemaining;
  stream << " ";
  stream << mDiskKbytesTotal;
  stream << " ";
  stream << (uint16_t)mLoggingState;
}


/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

LoggingParamStatus* LoggingParamStatus::clone() const {
  return new LoggingParamStatus(*this);
}
