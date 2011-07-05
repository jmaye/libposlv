#ifndef BASEGPS2DATASTREAM_H
#define BASEGPS2DATASTREAM_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class BaseGPS2DataStream : public Group {
  BaseGPS2DataStream();
  BaseGPS2DataStream(const BaseGPS2DataStream &other);
  BaseGPS2DataStream& operator = (const BaseGPS2DataStream &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  TimeDistance mTimeDistance;
  uint8_t mau8Reserved[6];
  uint16_t mu16VariableMsgByteCount;
  uint8_t *mau8GPSReceiverRawData;

public:
  ~BaseGPS2DataStream();

  virtual BaseGPS2DataStream* clone() const;

  static const BaseGPS2DataStream mProto;

protected:
};

#endif // BASEGPS2DATASTREAM_H
