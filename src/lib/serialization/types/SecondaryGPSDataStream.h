#ifndef SECONDARYGPSDATASTREAM_H
#define SECONDARYGPSDATASTREAM_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class SecondaryGPSDataStream : public Group {
  SecondaryGPSDataStream();
  SecondaryGPSDataStream(const SecondaryGPSDataStream &other);
  SecondaryGPSDataStream& operator = (const SecondaryGPSDataStream &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  TimeDistance mTimeDistance;
  uint8_t mau8Reserved[6];
  uint16_t mu16VariableMsgByteCount;
  uint8_t *mau8GPSReceiverRawData;

public:
  ~SecondaryGPSDataStream();

  virtual SecondaryGPSDataStream* clone() const;

  static const SecondaryGPSDataStream mProto;

protected:
};

#endif // SECONDARYGPSDATASTREAM_H
