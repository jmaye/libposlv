#include "ChannelStatusData.h"

#include "Connection.h"

#include <fstream>

using namespace std;

ChannelStatusData::ChannelStatusData() : mu16SVPRN(0),
                                         mu16ChannelTrackingStatus(0),
                                         mf32SVAzimuth(0),
                                         mf32SVElevation(0),
                                         mf32SVL1SNR(0),
                                         mf32SVL2SNR(0) {
}

ChannelStatusData::~ChannelStatusData() {
}

void ChannelStatusData::read(Connection &stream) throw(IOException) {
  stream >> mu16SVPRN;
  stream >> mu16ChannelTrackingStatus;
  stream >> mf32SVAzimuth;
  stream >> mf32SVElevation;
  stream >> mf32SVL1SNR;
  stream >> mf32SVL2SNR;
}

void ChannelStatusData::write(ofstream &stream) const {
  stream << mu16SVPRN;
  stream << " ";
  stream << mu16ChannelTrackingStatus;
  stream << " ";
  stream << mf32SVAzimuth;
  stream << " ";
  stream << mf32SVElevation;
  stream << " ";
  stream << mf32SVL1SNR;
  stream << " ";
  stream << mf32SVL2SNR;
}

Connection& operator >> (Connection &stream, ChannelStatusData &obj)
  throw(IOException) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream &stream,
  const ChannelStatusData &obj) {
  obj.write(stream);
  return stream;
}
