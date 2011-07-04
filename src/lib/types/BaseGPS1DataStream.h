#ifndef BASEGPS1DATASTREAM_H
#define BASEGPS1DATASTREAM_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class BaseGPS1DataStream : public Group {
  BaseGPS1DataStream();
  BaseGPS1DataStream(const BaseGPS1DataStream &other);
  BaseGPS1DataStream& operator = (const BaseGPS1DataStream &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  TimeDistance mTimeDistance;
  uint8_t mau8Reserved[6];
  uint16_t mu16VariableMsgByteCount;
  uint8_t *mau8GPSReceiverRawData;

public:
  ~BaseGPS1DataStream();

  virtual BaseGPS1DataStream* clone() const;

  static const BaseGPS1DataStream mProto;

protected:
};

#endif // BASEGPS1DATASTREAM_H
