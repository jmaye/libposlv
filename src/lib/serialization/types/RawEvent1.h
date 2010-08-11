#ifndef RAWEVENT1_H
#define RAWEVENT1_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class RawEvent1 : public Group {
  RawEvent1();
  RawEvent1(const RawEvent1 &other);
  RawEvent1& operator = (const RawEvent1 &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 36;

  TimeDistance mTimeDistance;
  uint32_t mu32Event1PulseCount;

public:
  ~RawEvent1();

  virtual RawEvent1* clone() const;

  static const RawEvent1 mProto;

protected:
};

#endif // RAWEVENT1_H
