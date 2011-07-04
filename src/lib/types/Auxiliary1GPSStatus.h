#ifndef AUXILIARY1GPSSTATUS_H
#define AUXILIARY1GPSSTATUS_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"
#include "types/ChannelStatusData.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class Auxiliary1GPSStatus : public Group {
  Auxiliary1GPSStatus();
  Auxiliary1GPSStatus(const Auxiliary1GPSStatus &other);
  Auxiliary1GPSStatus& operator = (const Auxiliary1GPSStatus &other);

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
  ~Auxiliary1GPSStatus();

  virtual Auxiliary1GPSStatus* clone() const;

  static const Auxiliary1GPSStatus mProto;

protected:
};

#endif // AUXILIARY1GPSSTATUS_H
