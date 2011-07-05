#ifndef RAWIMUDATA_H
#define RAWIMUDATA_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class RawIMUData : public Group {
  RawIMUData();
  RawIMUData(const RawIMUData &other);
  RawIMUData& operator = (const RawIMUData &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  TimeDistance mTimeDistance;
  uint8_t mau8IMUHeader[6];
  uint16_t mu16VariableMsgByteCount;
  uint8_t *mau8IMURawData;
  uint16_t mu16DataChecksum;

public:
  ~RawIMUData();

  virtual RawIMUData* clone() const;

  static const RawIMUData mProto;

protected:
};

#endif // RAWIMUDATA_H
