#include "BaseGPS1ModemStatus.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const BaseGPS1ModemStatus BaseGPS1ModemStatus::mProto;

BaseGPS1ModemStatus::BaseGPS1ModemStatus() : Group(21) {
}

BaseGPS1ModemStatus::
  BaseGPS1ModemStatus(const BaseGPS1ModemStatus &other) : Group(other) {
}

BaseGPS1ModemStatus::~BaseGPS1ModemStatus() {
}

void BaseGPS1ModemStatus::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("BaseGPS1ModemStatus::read: Wrong byte count");

  stream >> mTimeDistance;
  for (uint32_t i = 0; i < 16; i++)
    stream >> mau8ModemResponse[i];
  for (uint32_t i = 0; i < 48; i++)
    stream >> mau8ConnectionStatus[i];
  stream >> mu32NumberOfRedialsPerDisconnect;
  stream >> mu32MaximumNumberOfRedialsPerDisconnect;
  stream >> mu32NumberOfDisconnects;
  stream >> mu32DataGapLength;
  stream >> mu32MaximumDataGapLength;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("BaseGPS1ModemStatus::read: Wrong pad");
}

void BaseGPS1ModemStatus::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " " ;
  stream << mTimeDistance;
  for (uint32_t i = 0; i < 16; i++) {
    stream << mau8ModemResponse[i];
    stream << " " ;
  }
  for (uint32_t i = 0; i < 48; i++) {
    stream << mau8ConnectionStatus[i];
    stream << " " ;
  }
  stream << mu32NumberOfRedialsPerDisconnect;
  stream << " " ;
  stream << mu32MaximumNumberOfRedialsPerDisconnect;
  stream << " " ;
  stream << mu32NumberOfDisconnects;
  stream << " " ;
  stream << mu32DataGapLength;
  stream << " " ;
  stream << mu32MaximumDataGapLength;
}

BaseGPS1ModemStatus* BaseGPS1ModemStatus::clone() const {
  return new BaseGPS1ModemStatus(*this);
}
