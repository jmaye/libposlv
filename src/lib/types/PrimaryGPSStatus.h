#ifndef PRIMARYGPSSTATUS_H
#define PRIMARYGPSSTATUS_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"
#include "types/ChannelStatusData.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class PrimaryGPSStatus : public Group {
  PrimaryGPSStatus();
  PrimaryGPSStatus(const PrimaryGPSStatus &other);
  PrimaryGPSStatus& operator = (const PrimaryGPSStatus &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 676;

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

public:
  ~PrimaryGPSStatus();

  virtual PrimaryGPSStatus* clone() const;

  static const PrimaryGPSStatus mProto;

protected:
};

#endif // PRIMARYGPSSTATUS_H
