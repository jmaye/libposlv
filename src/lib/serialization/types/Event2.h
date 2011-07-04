#ifndef Event2_H
#define Event2_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class Event2 : public Group {
  Event2();
  Event2(const Event2 &other);
  Event2& operator = (const Event2 &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 36;

  TimeDistance mTimeDistance;
  uint32_t mu32EventPulseNumber;

public:
  ~Event2();

  virtual Event2* clone() const;

  static const Event2 mProto;

protected:
};

#endif // Event2_H
