#ifndef RAWEVENT2_H
#define RAWEVENT2_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class RawEvent2 : public Group {
  RawEvent2();
  RawEvent2(const RawEvent2 &other);
  RawEvent2& operator = (const RawEvent2 &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 36;

  TimeDistance mTimeDistance;
  uint32_t mu32Event2PulseCount;

public:
  ~RawEvent2();

  virtual RawEvent2* clone() const;

  static const RawEvent2 mProto;

protected:
};

#endif // RAWEVENT2_H
