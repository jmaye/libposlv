#ifndef SECONDARYGPSSTATUS_H
#define SECONDARYGPSSTATUS_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"
#include "ChannelStatusData.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class SecondaryGPSStatus : public Group {
  SecondaryGPSStatus();
  SecondaryGPSStatus(const SecondaryGPSStatus &other);
  SecondaryGPSStatus& operator = (const SecondaryGPSStatus &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 76;

  TimeDistance mTimeDistance;
  int8_t mi8NavigationSolutionStatus;
  uint8_t mu8NumberOfSVTracked;
  uint16_t mu16ChannelStatusByteCount;
  ChannelStatusData maChannelStatusData[12];
  float mf32HDOP;
  float mf32VDOP;
  float mf32DGPSCorrectionLatency;
  uint16_t mu16DGPSReferenceID;
  uint32_t mu32GPSUTCWeekNumber;
  double mf64GPSUTCTimeOffset;
  float mf32GPSNavigationMessageLatency;
  float mf32GeoidalSeparation;
  uint16_t mu16GPSReceiverType;
  uint32_t mu32GPSStatus;
  uint32_t mu32ChannelNumber;

public:
  ~SecondaryGPSStatus();

  virtual SecondaryGPSStatus* clone() const;

  static const SecondaryGPSStatus mProto;

protected:
};

#endif // SECONDARYGPSSTATUS_H
