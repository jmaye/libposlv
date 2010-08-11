#ifndef RAWDMIDATASTREAM_H
#define RAWDMIDATASTREAM_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class RawDMIDataStream : public Group {
  RawDMIDataStream();
  RawDMIDataStream(const RawDMIDataStream &other);
  RawDMIDataStream& operator = (const RawDMIDataStream &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 48;

  TimeDistance mTimeDistance;
  int32_t mi32UpDownPulseCount;
  uint32_t mu32RectifiedPulseCount;
  int32_t mi32EventCount;
  uint32_t mu32ReservedCount;

public:
  ~RawDMIDataStream();

  virtual RawDMIDataStream* clone() const;

  static const RawDMIDataStream mProto;

protected:
};

#endif // RAWDMIDATASTREAM_H
