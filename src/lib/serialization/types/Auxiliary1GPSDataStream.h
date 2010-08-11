#ifndef AUXILIARY1GPSDATASTREAM_H
#define AUXILIARY1GPSDATASTREAM_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class Auxiliary1GPSDataStream : public Group {
  Auxiliary1GPSDataStream();
  Auxiliary1GPSDataStream(const Auxiliary1GPSDataStream &other);
  Auxiliary1GPSDataStream& operator = (const Auxiliary1GPSDataStream &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  TimeDistance mTimeDistance;
  uint8_t mau8Reserved[6];
  uint16_t mu16VariableMsgByteCount;
  uint8_t *mau8GPSReceiverRawData;

public:
  ~Auxiliary1GPSDataStream();

  virtual Auxiliary1GPSDataStream* clone() const;

  static const Auxiliary1GPSDataStream mProto;

protected:
};

#endif // AUXILIARY1GPSDATASTREAM_H
