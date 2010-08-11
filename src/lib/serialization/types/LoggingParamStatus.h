#ifndef LOGGINGPARAMSTATUS_H
#define LOGGINGPARAMSTATUS_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class LoggingParamStatus : public Group {
  LoggingParamStatus();
  LoggingParamStatus(const LoggingParamStatus &other);
  LoggingParamStatus& operator = (const LoggingParamStatus &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 4848;

  TimeDistance mTimeDistance;
  uint32_t mu32DiskKbytesRemaining;
  uint32_t mu32DiskKbytesLogged;
  float mf32DiskLoggingTimeRemaining;
  uint32_t mu32DiskKbytesTotal;
  uint8_t mu8LoggingState;

public:
  ~LoggingParamStatus();

  virtual LoggingParamStatus* clone() const;

  static const LoggingParamStatus mProto;

protected:
};

#endif // LOGGINGPARAMSTATUS_H
