#ifndef AUXILIARY1GPSDISPLAYDATA_H
#define AUXILIARY1GPSDISPLAYDATA_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class Auxiliary1GPSDisplayData : public Group {
  Auxiliary1GPSDisplayData();
  Auxiliary1GPSDisplayData(const Auxiliary1GPSDisplayData &other);
  Auxiliary1GPSDisplayData& operator = (const Auxiliary1GPSDisplayData &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  TimeDistance mTimeDistance;
  uint8_t mau8Reserved[6];
  uint16_t mu16VariableMsgByteCount;
  uint8_t *mau8GPSRawData;

public:
  ~Auxiliary1GPSDisplayData();

  virtual Auxiliary1GPSDisplayData* clone() const;

  static const Auxiliary1GPSDisplayData mProto;

protected:
};

#endif // AUXILIARY1GPSDISPLAYDATA_H
