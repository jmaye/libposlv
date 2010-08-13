#include "PPSTimeRecoveryStatus.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const PPSTimeRecoveryStatus PPSTimeRecoveryStatus::mProto;

PPSTimeRecoveryStatus::PPSTimeRecoveryStatus() : Group(7) {
}

PPSTimeRecoveryStatus::
  PPSTimeRecoveryStatus(const PPSTimeRecoveryStatus &other) : Group(other) {
}

PPSTimeRecoveryStatus::~PPSTimeRecoveryStatus() {
}

void PPSTimeRecoveryStatus::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("PPSTimeRecoveryStatus::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mu32PPSCount;
  stream >> mu8TimeSynchroStatus;

  uint8_t u8Pad;
  stream >> u8Pad;
  if (u8Pad != 0)
    throw IOException("PPSTimeRecoveryStatus::read: Wrong pad");
}

void PPSTimeRecoveryStatus::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mu32PPSCount;
  stream << hex << (uint16_t)mu8TimeSynchroStatus << dec;
}

PPSTimeRecoveryStatus* PPSTimeRecoveryStatus::clone() const {
  return new PPSTimeRecoveryStatus(*this);
}
