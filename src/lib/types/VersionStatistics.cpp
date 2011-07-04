#include "types/VersionStatistics.h"

#include "com/Connection.h"
#include "utils/TypesFactory.h"

#include <fstream>
#include <string>

using namespace std;

const VersionStatistics VersionStatistics::mProto;

VersionStatistics::VersionStatistics() : Group(99) {
}

VersionStatistics::
  VersionStatistics(const VersionStatistics &other) : Group(other) {
}

VersionStatistics::~VersionStatistics() {
}

void VersionStatistics::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("VersionStatistics::read: Wrong byte count");

  stream >> mTimeDistance;
  for (uint32_t i = 0; i < 120; i++)
    stream >> mau8SystemVersion[i];
  for (uint32_t i = 0; i < 80; i++)
    stream >> mau8PrimaryGPSVersion[i];
  for (uint32_t i = 0; i < 80; i++)
    stream >> mau8SecondaryGPSversion[i];
  stream >> mf32TotalHours;
  stream >> mu32NumberOfRuns;
  stream >> mf32AverageLengthOfRun;
  stream >> mf32LongestRun;
  stream >> mf32CurrentRun;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("VersionStatistics::read: Wrong pad");
}

void VersionStatistics::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  string outputStr1((const char*)mau8SystemVersion);
  stream << outputStr1;
  stream << " ";
  string outputStr2((const char*)mau8PrimaryGPSVersion);
  stream << outputStr2;
  stream << " ";
  string outputStr3((const char*)mau8SecondaryGPSversion);
  stream << outputStr3;
  stream << " ";
  stream << mf32TotalHours;
  stream << " ";
  stream << mu32NumberOfRuns;
  stream << " ";
  stream << mf32AverageLengthOfRun;
  stream << " ";
  stream << mf32LongestRun;
  stream << " ";
  stream << mf32CurrentRun;
}

VersionStatistics* VersionStatistics::clone() const {
  return new VersionStatistics(*this);
}
