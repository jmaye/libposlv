#include "GAMSSolutionStatus.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const GAMSSolutionStatus GAMSSolutionStatus::mProto;

GAMSSolutionStatus::GAMSSolutionStatus() : Group(9) {
}

GAMSSolutionStatus::
  GAMSSolutionStatus(const GAMSSolutionStatus &other) : Group(other) {
}

GAMSSolutionStatus::~GAMSSolutionStatus() {
}

void GAMSSolutionStatus::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("GAMSSolutionStatus::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mu8NumberOfSatellites;
  stream >> mf32APrioriPDOP;
  stream >> mf32ComputedAntennaSeparation;
  stream >> mu8SolutionStatus;
  for (uint32_t i = 0; i < 12; i++)
    stream >> mau8PRNAssignment[i];
  stream >> mu16CycleSlipFlag;
  stream >> mf64GAMSHeading;
  stream >> mf64GAMSHeadingRMSError;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("GAMSSolutionStatus::read: Wrong pad");
}

void GAMSSolutionStatus::write(ofstream &stream) const {
}

GAMSSolutionStatus* GAMSSolutionStatus::clone() const {
  return new GAMSSolutionStatus(*this);
}