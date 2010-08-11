#ifndef RAWPPS_H
#define RAWPPS_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class RawPPS : public Group {
  RawPPS();
  RawPPS(const RawPPS &other);
  RawPPS& operator = (const RawPPS &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 36;

  TimeDistance mTimeDistance;
  uint32_t mu16PPSPulseCount;

public:
  ~RawPPS();

  virtual RawPPS* clone() const;

  static const RawPPS mProto;

protected:
};

#endif // RAWPPS_H
