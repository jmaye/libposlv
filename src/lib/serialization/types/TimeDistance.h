#ifndef TIMEDISTANCE_H
#define TIMEDISTANCE_H

#include "IOException.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class TimeDistance {
  friend Connection& operator >> (Connection &stream, TimeDistance &obj)
    throw(IOException);
  friend std::ofstream& operator << (std::ofstream &stream,
    const TimeDistance &obj);

  TimeDistance(const TimeDistance &other);
  TimeDistance& operator = (const TimeDistance &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  double mf64Time1;
  double mf64Time2;
  double mf64DistanceTag;
  uint8_t mu8TimeType;
  uint8_t mu8DistanceType;

public:
  TimeDistance();
  ~TimeDistance();

protected:

};

#endif // TIMEDISTANCE_H
