#include "types/IINSolutionStatus.h"

#include "com/Connection.h"
#include "utils/TypesFactory.h"

#include <fstream>

using namespace std;

const IINSolutionStatus IINSolutionStatus::mProto;

IINSolutionStatus::IINSolutionStatus() : Group(20) {
}

IINSolutionStatus::
  IINSolutionStatus(const IINSolutionStatus &other) : Group(other) {
}

IINSolutionStatus::~IINSolutionStatus() {
}

void IINSolutionStatus::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("IINSolutionStatus::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mu16NumberOfSatellites;
  stream >> mf32APrioriPDOP;
  stream >> mf32BaselineLength;
  stream >> mu16IINProcessingStatus;
  for (uint8_t i = 0; i < 12; i++)
    stream >> mau8PRNAssignment[i];
  stream >> mu16L1CycleSlipFlag;
  stream >> mu16L2CycleSlipFlag;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("IINSolutionStatus::read: Wrong pad");
}

void IINSolutionStatus::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mu16NumberOfSatellites;
  stream << " ";
  stream << mf32APrioriPDOP;
  stream << " ";
  stream << mf32BaselineLength;
  stream << " ";
  stream << mu16IINProcessingStatus;
  stream << " ";
  for (uint8_t i = 0; i < 12; i++) {
    stream << hex << (uint16_t)mau8PRNAssignment[i] << dec;
    stream << " ";
  }
  stream << mu16L1CycleSlipFlag;
  stream << " ";
  stream << mu16L2CycleSlipFlag;
}

IINSolutionStatus* IINSolutionStatus::clone() const {
  return new IINSolutionStatus(*this);
}
