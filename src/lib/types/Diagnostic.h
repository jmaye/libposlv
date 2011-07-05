#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class Diagnostic : public Group {
  Diagnostic();
  Diagnostic(const Diagnostic &other);
  Diagnostic& operator = (const Diagnostic &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 276;

  TimeDistance mTimeDistance;

public:
  ~Diagnostic();

  virtual Diagnostic* clone() const;

  static const Diagnostic mProto;

protected:
};

#endif // DIAGNOSTIC_H
