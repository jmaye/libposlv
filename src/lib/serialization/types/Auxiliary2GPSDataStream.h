#ifndef AUXILIARY2GPSDATASTREAM_H
#define AUXILIARY2GPSDATASTREAM_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class Auxiliary2GPSDataStream : public Group {
  Auxiliary2GPSDataStream();
  Auxiliary2GPSDataStream(const Auxiliary2GPSDataStream &other);
  Auxiliary2GPSDataStream& operator = (const Auxiliary2GPSDataStream &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  TimeDistance mTimeDistance;
  uint8_t mau8Reserved[6];
  uint16_t mu16VariableMsgByteCount;
  uint8_t *mau8GPSReceiverRawData;

public:
  ~Auxiliary2GPSDataStream();

  virtual Auxiliary2GPSDataStream* clone() const;

  static const Auxiliary2GPSDataStream mProto;

protected:
};

#endif // AUXILIARY2GPSDATASTREAM_H
