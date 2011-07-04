#ifndef USERTIMESTATUS_H
#define USERTIMESTATUS_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class UserTimeStatus : public Group {
  UserTimeStatus();
  UserTimeStatus(const UserTimeStatus &other);
  UserTimeStatus& operator = (const UserTimeStatus &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 40;

  TimeDistance mTimeDistance;
  uint32_t mu32NumberOfTimeSynchMessageRejections;
  uint32_t mu32NumberOfUserTimeResynchronizations;
  uint8_t mu8UserTimeValid;
  uint8_t mu8TimeSynchMessageReceived;

public:
  ~UserTimeStatus();

  virtual UserTimeStatus* clone() const;

  static const UserTimeStatus mProto;

protected:
};

#endif // USERTIMESTATUS_H
