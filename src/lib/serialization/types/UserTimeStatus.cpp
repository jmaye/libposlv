#include "UserTimeStatus.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const UserTimeStatus UserTimeStatus::mProto;

UserTimeStatus::UserTimeStatus() : Group(17) {
}

UserTimeStatus::UserTimeStatus(const UserTimeStatus &other)
  : Group(other) {
}

UserTimeStatus::~UserTimeStatus() {
}

void UserTimeStatus::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("UserTimeStatus::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mu32NumberOfTimeSynchMessageRejections;
  stream >> mu32NumberOfUserTimeResynchronizations;
  stream >> mu8UserTimeValid;
  stream >> mu8TimeSynchMessageReceived;
}

void UserTimeStatus::write(ofstream &stream) const {
}

UserTimeStatus* UserTimeStatus::clone() const {
  return new UserTimeStatus(*this);
}
