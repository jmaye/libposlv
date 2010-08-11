#include "TimeDistance.h"

#include "Connection.h"

#include <fstream>

using namespace std;

TimeDistance::TimeDistance() : mf64Time1(0),
                               mf64Time2(0),
                               mf64DistanceTag(0),
                               mu8TimeType(0),
                               mu8DistanceType(0) {
}

TimeDistance::~TimeDistance() {
}

void TimeDistance::read(Connection &stream) throw(IOException) {
  stream >> mf64Time1;
  stream >> mf64Time2;
  stream >> mf64DistanceTag;
  stream >> mu8TimeType;
  stream >> mu8DistanceType;
}

void TimeDistance::write(ofstream &stream) const {
}

Connection& operator >> (Connection &stream, TimeDistance &obj)
  throw(IOException) {
  obj.read(stream);
  return stream;
}

ofstream& operator << (ofstream &stream,
  const TimeDistance &obj) {
  obj.write(stream);
  return stream;
}
