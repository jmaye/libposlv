#ifndef PPSTimeRecoveryStatus_H
#define PPSTimeRecoveryStatus_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class PPSTimeRecoveryStatus : public Group {
  PPSTimeRecoveryStatus();
  PPSTimeRecoveryStatus(const PPSTimeRecoveryStatus &other);
  PPSTimeRecoveryStatus& operator = (const PPSTimeRecoveryStatus &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 36;

  TimeDistance mTimeDistance;
  uint32_t mu32PPSCount;
  uint8_t mu8TimeSynchroStatus;

public:
  ~PPSTimeRecoveryStatus();

  virtual PPSTimeRecoveryStatus* clone() const;

  static const PPSTimeRecoveryStatus mProto;

protected:
};

#endif // PPSTimeRecoveryStatus_H
