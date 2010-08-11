#include "GeneralStatusFDIR.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const GeneralStatusFDIR GeneralStatusFDIR::mProto;

GeneralStatusFDIR::GeneralStatusFDIR() : Group(10) {
}

GeneralStatusFDIR::
  GeneralStatusFDIR(const GeneralStatusFDIR &other) : Group(other) {
}

GeneralStatusFDIR::~GeneralStatusFDIR() {
}

void GeneralStatusFDIR::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("GeneralStatusFDIR::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mu32GeneralStatusA;
  stream >> mu32GeneralStatusB;
  stream >> mu32GeneralStatusC;
  stream >> mu32FDIRLevel1Status;
  stream >> mu16FDIRLevel1Failures;
  stream >> mu16FDIRLevel2Status;
  stream >> mu16FDIRLevel3Status;
  stream >> mu16FDIRLevel4Status;
  stream >> mu16FDIRLevel5Status;
  stream >> mu32ExtendedStatus;
}

void GeneralStatusFDIR::write(ofstream &stream) const {
}

GeneralStatusFDIR* GeneralStatusFDIR::clone() const {
  return new GeneralStatusFDIR(*this);
}
