#ifndef TIMETAGGEDDMIDATA_H
#define TIMETAGGEDDMIDATA_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class TimeTaggedDMIData : public Group {
  TimeTaggedDMIData();
  TimeTaggedDMIData(const TimeTaggedDMIData &other);
  TimeTaggedDMIData& operator = (const TimeTaggedDMIData &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 52;

  TimeDistance mTimeDistance;
  double mf64SignedDistanceTraveled;
  double mf64UnsignedDistanceTraveled;
  uint16_t mu16DMIScaleFactor;
  uint8_t mu8DataStatus;
  uint8_t mu8DMIType;
  uint8_t mu8DMIDataRate;

public:
  ~TimeTaggedDMIData();

  virtual TimeTaggedDMIData* clone() const;

  static const TimeTaggedDMIData mProto;

protected:
};

#endif // TIMETAGGEDDMIDATA_H
