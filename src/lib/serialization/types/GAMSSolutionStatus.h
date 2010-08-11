#ifndef GAMSSOLUTIONSTATUS_H
#define GAMSSOLUTIONSTATUS_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class GAMSSolutionStatus : public Group {
  GAMSSolutionStatus();
  GAMSSolutionStatus(const GAMSSolutionStatus &other);
  GAMSSolutionStatus& operator = (const GAMSSolutionStatus &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 72;

  TimeDistance mTimeDistance;
  uint8_t mu8NumberOfSatellites;
  float mf32APrioriPDOP;
  float mf32ComputedAntennaSeparation;
  uint8_t mu8SolutionStatus;
  uint8_t mau8PRNAssignment[12];
  uint16_t mu16CycleSlipFlag;
  double mf64GAMSHeading;
  double mf64GAMSHeadingRMSError;

public:
  ~GAMSSolutionStatus();

  virtual GAMSSolutionStatus* clone() const;

  static const GAMSSolutionStatus mProto;

protected:
};

#endif // GAMSSOLUTIONSTATUS_H
