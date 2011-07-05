#ifndef EVENT1_H
#define EVENT1_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class Event1 : public Group {
  Event1();
  Event1(const Event1 &other);
  Event1& operator = (const Event1 &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 36;

  TimeDistance mTimeDistance;
  uint32_t mu32EventPulseNumber;

public:
  ~Event1();

  virtual Event1* clone() const;

  static const Event1 mProto;

protected:
};

#endif // Event1_H
