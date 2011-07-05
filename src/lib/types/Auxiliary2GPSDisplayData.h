#ifndef AUXILIARY2GPSDISPLAYDATA_H
#define AUXILIARY2GPSDISPLAYDATA_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class Auxiliary2GPSDisplayData : public Group {
  Auxiliary2GPSDisplayData();
  Auxiliary2GPSDisplayData(const Auxiliary2GPSDisplayData &other);
  Auxiliary2GPSDisplayData& operator = (const Auxiliary2GPSDisplayData &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  TimeDistance mTimeDistance;
  uint8_t mau8Reserved[6];
  uint16_t mu16VariableMsgByteCount;
  uint8_t *mau8GPSRawData;

public:
  ~Auxiliary2GPSDisplayData();

  virtual Auxiliary2GPSDisplayData* clone() const;

  static const Auxiliary2GPSDisplayData mProto;

protected:
};

#endif // AUXILIARY2GPSDISPLAYDATA_H
