#ifndef VERSIONSTATISTICS_H
#define VERSIONSTATISTICS_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class VersionStatistics : public Group {
  VersionStatistics();
  VersionStatistics(const VersionStatistics &other);
  VersionStatistics& operator = (const VersionStatistics &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 332;

  TimeDistance mTimeDistance;
  uint8_t mau8SystemVersion[120];
  uint8_t mau8PrimaryGPSVersion[80];
  uint8_t mau8SecondaryGPSversion[80];
  float mf32TotalHours;
  uint32_t mu32NumberOfRuns;
  float mf32AverageLengthOfRun;
  float mf32LongestRun;
  float mf32CurrentRun;

public:
  ~VersionStatistics();

  virtual VersionStatistics* clone() const;

  static const VersionStatistics mProto;

protected:
};

#endif // VERSIONSTATISTICS_H
