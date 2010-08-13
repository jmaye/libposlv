#ifndef AUXILIARY2GPSSTATUS_H
#define AUXILIARY2GPSSTATUS_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"
#include "ChannelStatusData.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class Auxiliary2GPSStatus : public Group {
  Auxiliary2GPSStatus();
  Auxiliary2GPSStatus(const Auxiliary2GPSStatus &other);
  Auxiliary2GPSStatus& operator = (const Auxiliary2GPSStatus &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 72;

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
  uint16_t mu16NMEAMessageReceived;
  uint8_t mu8Aux12InUse;
  uint32_t mu32ChannelNumber;

public:
  ~Auxiliary2GPSStatus();

  virtual Auxiliary2GPSStatus* clone() const;

  static const Auxiliary2GPSStatus mProto;

protected:
};

#endif // AUXILIARY2GPSSTATUS_H
