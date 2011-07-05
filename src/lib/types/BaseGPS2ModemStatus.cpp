#include "types/BaseGPS2ModemStatus.h"

#include "com/Connection.h"

#include <fstream>

using namespace std;

const BaseGPS2ModemStatus BaseGPS2ModemStatus::mProto;

BaseGPS2ModemStatus::BaseGPS2ModemStatus() : Group(22) {
}

BaseGPS2ModemStatus::
  BaseGPS2ModemStatus(const BaseGPS2ModemStatus &other) : Group(other) {
}

BaseGPS2ModemStatus::~BaseGPS2ModemStatus() {
}

void BaseGPS2ModemStatus::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("BaseGPS2ModemStatus::read: Wrong byte count");

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
    throw IOException("BaseGPS2ModemStatus::read: Wrong pad");
}

void BaseGPS2ModemStatus::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  for (uint32_t i = 0; i < 16; i++) {
    stream << hex << (uint16_t)mau8ModemResponse[i] << dec;
    stream << " ";
  }
  for (uint32_t i = 0; i < 48; i++) {
    stream << hex << (uint16_t)mau8ConnectionStatus[i] << dec;
    stream << " ";
  }
  stream << mu32NumberOfRedialsPerDisconnect;
  stream << " ";
  stream << mu32MaximumNumberOfRedialsPerDisconnect;
  stream << " ";
  stream << mu32NumberOfDisconnects;
  stream << " ";
  stream << mu32DataGapLength;
  stream << " ";
  stream << mu32MaximumDataGapLength;
}

BaseGPS2ModemStatus* BaseGPS2ModemStatus::clone() const {
  return new BaseGPS2ModemStatus(*this);
}
