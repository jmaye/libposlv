#ifndef PRIMARYGPSDATASTREAM_H
#define PRIMARYGPSDATASTREAM_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class PrimaryGPSDataStream : public Group {
  PrimaryGPSDataStream();
  PrimaryGPSDataStream(const PrimaryGPSDataStream &other);
  PrimaryGPSDataStream& operator = (const PrimaryGPSDataStream &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  TimeDistance mTimeDistance;
  uint16_t mu16GPSReceiverType;
  uint32_t mu32Reserved;
  uint16_t mu16VariableMsgByteCount;
  uint8_t *mau8GPSReceiverRawData;

public:
  ~PrimaryGPSDataStream();

  virtual PrimaryGPSDataStream* clone() const;

  static const PrimaryGPSDataStream mProto;

protected:
};

#endif // PRIMARYGPSDATASTREAM_H
