#include "StationRecord.h"

#include "Connection.h"

#include <fstream>

using namespace std;

StationRecord::StationRecord() {
}

StationRecord::~StationRecord() {
}

void StationRecord::read(Connection &stream) throw(IOException) {
  stream >> mu8RecordIndexAndFlags;
  stream >> mu16StationID;
  stream >> mu16StationHealth;
  stream >> mf32Distance;
  stream >> mf32Range;
  stream >> mu8USCGIndex;
  stream >> mu64Seconds;
  stream >> mu8ModulationRate;
}

void StationRecord::write(ofstream &stream) const {
}

Connection& operator >> (Connection &stream, StationRecord &obj)
  throw(IOException) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream &stream,
  const StationRecord &obj) {
  obj.write(stream);
  return stream;
}
