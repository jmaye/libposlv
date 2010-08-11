#ifndef IINSOLUTIONSTATUS_H
#define IINSOLUTIONSTATUS_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class IINSolutionStatus : public Group {
  IINSolutionStatus();
  IINSolutionStatus(const IINSolutionStatus &other);
  IINSolutionStatus& operator = (const IINSolutionStatus &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 60;

  TimeDistance mTimeDistance;
  uint16_t mu16NumberOfSatellites;
  float mf32APrioriPDOP;
  float mf32BaselineLength;
  uint16_t mu16IINProcessingStatus;
  uint8_t mau8PRNAssignment[12];
  uint16_t mu16L1CycleSlipFlag;
  uint16_t mu16L2CycleSlipFlag;

public:
  ~IINSolutionStatus();

  virtual IINSolutionStatus* clone() const;

  static const IINSolutionStatus mProto;

protected:
};

#endif // IINSOLUTIONSTATUS_H
