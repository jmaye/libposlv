#ifndef TIMETAGGEDIMUDATA_H
#define TIMETAGGEDIMUDATA_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class TimeTaggedIMUData : public Group {
  TimeTaggedIMUData();
  TimeTaggedIMUData(const TimeTaggedIMUData &other);
  TimeTaggedIMUData& operator = (const TimeTaggedIMUData &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 60;

  TimeDistance mTimeDistance;
  int32_t mi32XIncrementalVelocity;
  int32_t mi32YIncrementalVelocity;
  int32_t mi32ZIncrementalVelocity;
  int32_t mi32XIncrementalAngle;
  int32_t mi32YIncrementalAngle;
  int32_t mi32ZIncrementalAngle;
  uint8_t mu8DataStatus;
  uint8_t mu8IMUType;
  uint8_t mu8POSIMUDataRate;
  uint16_t mu16IMUStatus;

public:
  ~TimeTaggedIMUData();

  virtual TimeTaggedIMUData* clone() const;

  static const TimeTaggedIMUData mProto;

protected:
};

#endif // TIMETAGGEDIMUDATA_H
