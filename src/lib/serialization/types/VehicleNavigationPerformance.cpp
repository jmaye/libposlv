#include "VehicleNavigationPerformance.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const VehicleNavigationPerformance VehicleNavigationPerformance::mProto;

VehicleNavigationPerformance::VehicleNavigationPerformance() : Group(2) {
}

VehicleNavigationPerformance::
  VehicleNavigationPerformance(const VehicleNavigationPerformance &other)
  : Group(other) {
}

VehicleNavigationPerformance::~VehicleNavigationPerformance() {
}

void VehicleNavigationPerformance::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("VehicleNavigationPerformance::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mf32NorthPositionRMSError;
  stream >> mf32EastPositionRMSError;
  stream >> mf32DownPositionRMSError;
  stream >> mf32NorthVelocityRMSError;
  stream >> mf32EastVelocityRMSError;
  stream >> mf32DownVelocityRMSError;
  stream >> mf32RollRMSError;
  stream >> mf32PitchRMSError;
  stream >> mf32HeadingRMSError;
  stream >> mf32ErrorEllipsoidSemiMajor;
  stream >> mf32ErrorEllipsoidSemiMinor;
  stream >> mf32ErrorEllipsoidOrientation;

  uint16_t u16Pad;
  stream >> u16Pad;
  if (u16Pad != 0)
    throw IOException("VehicleNavigationPerformance::read: Wrong pad");
}

void VehicleNavigationPerformance::write(ofstream &stream) const {
}

VehicleNavigationPerformance* VehicleNavigationPerformance::clone() const {
  return new VehicleNavigationPerformance(*this);
}
