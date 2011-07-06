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

#include "types/UserTimeStatus.h"

#include "com/Connection.h"

/******************************************************************************/
/* Statics                                                                    */
/******************************************************************************/

const UserTimeStatus UserTimeStatus::mProto;

/******************************************************************************/
/* Constructors and Destructor                                                */
/******************************************************************************/

UserTimeStatus::UserTimeStatus() :
  Group(17) {
}

UserTimeStatus::UserTimeStatus(const UserTimeStatus& other) :
  Group(other) {
}

UserTimeStatus& UserTimeStatus::operator =
  (const UserTimeStatus& other) {
  this->Group::operator=(other);
  return *this;
}

UserTimeStatus::~UserTimeStatus() {
}

/******************************************************************************/
/* Stream operations                                                          */
/******************************************************************************/

void UserTimeStatus::read(Connection& stream) throw (IOException) {
  uint16_t byteCount;
  stream >> byteCount;
  if (byteCount != mByteCount)
    throw IOException("UserTimeStatus::read(): wrong byte count");

  stream >> mTimeDistance;
  stream >> mNumberOfTimeSynchMessageRejections;
  stream >> mNumberOfUserTimeResynchronizations;
  stream >> mUserTimeValid;
  stream >> mTimeSynchMessageReceived;
}

void UserTimeStatus::read(std::istream& stream) {
}

void UserTimeStatus::write(std::ostream& stream) const {
}

void UserTimeStatus::read(std::ifstream& stream) {
}

void UserTimeStatus::write(std::ofstream& stream) const {
//  stream << mu16TypeID;
//  stream << " ";
//  stream << mTimeDistance;
//  stream << mu32NumberOfTimeSynchMessageRejections;
//  stream << " ";
//  stream << mu32NumberOfUserTimeResynchronizations;
//  stream << " ";
//  stream << hex << (uint16_t)mu8UserTimeValid << dec;
//  stream << " ";
//  stream << hex << (uint16_t)mu8TimeSynchMessageReceived << dec;
}

/******************************************************************************/
/* Methods                                                                    */
/******************************************************************************/

UserTimeStatus* UserTimeStatus::clone() const {
  return new UserTimeStatus(*this);
}
