#include "LoggingParamStatus.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const LoggingParamStatus LoggingParamStatus::mProto;

LoggingParamStatus::LoggingParamStatus() : Group(8) {
}

LoggingParamStatus::
  LoggingParamStatus(const LoggingParamStatus &other) : Group(other) {
}

LoggingParamStatus::~LoggingParamStatus() {
}

void LoggingParamStatus::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("LoggingParamStatus::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mu32DiskKbytesRemaining;
  stream >> mu32DiskKbytesLogged;
  stream >> mf32DiskLoggingTimeRemaining;
  stream >> mu32DiskKbytesTotal;
  stream >> mu8LoggingState;

  uint8_t u8Pad;
  stream >> u8Pad;
  if (u8Pad != 0)
    throw IOException("LoggingParamStatus::read: Wrong pad");
}

void LoggingParamStatus::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mu32DiskKbytesRemaining;
  stream << " ";
  stream << mu32DiskKbytesLogged;
  stream << " ";
  stream << mf32DiskLoggingTimeRemaining;
  stream << " ";
  stream << mu32DiskKbytesTotal;
  stream << " ";
  stream << hex << (uint16_t)mu8LoggingState << dec;
}

LoggingParamStatus* LoggingParamStatus::clone() const {
  return new LoggingParamStatus(*this);
}
