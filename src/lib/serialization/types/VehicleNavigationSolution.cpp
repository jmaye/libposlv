#include "VehicleNavigationSolution.h"

#include "Connection.h"
#include "TypesFactory.h"

#include <fstream>

using namespace std;

const VehicleNavigationSolution VehicleNavigationSolution::mProto;

VehicleNavigationSolution::VehicleNavigationSolution() : Group(1) {
}

VehicleNavigationSolution::
  VehicleNavigationSolution(const VehicleNavigationSolution &other)
  : Group(other) {
}

VehicleNavigationSolution::~VehicleNavigationSolution() {
}

void VehicleNavigationSolution::read(Connection &stream) throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;
  if (u16ByteCount != mcu16ByteCount)
    throw IOException("VehicleNavigationSolution::read: Wrong byte count");

  stream >> mTimeDistance;
  stream >> mf64Latitude;
  stream >> mf64Longitude;
  stream >> mf64Altitude;
  stream >> mf32NorthVelocity;
  stream >> mf32EastVelocity;
  stream >> mf32DownVelocity;
  stream >> mf64Roll;
  stream >> mf64Pitch;
  stream >> mf64Heading;
  stream >> mf64WanderAngle;
  stream >> mf32TrackAngle;
  stream >> mf32Speed;
  stream >> mf32AngularRateLong;
  stream >> mf32AngularRateTrans;
  stream >> mf32AngularRateDown;
  stream >> mf32AccLong;
  stream >> mf32AccTrans;
  stream >> mf32AccDown;
  stream >> mu8AlignementStatus;

  uint8_t u8Pad;
  stream >> u8Pad;
  if (u8Pad != 0)
    throw IOException("VehicleNavigationSolution::read: Wrong pad");
}

void VehicleNavigationSolution::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  stream << mf64Latitude;
  stream << " ";
  stream << mf64Longitude;
  stream << " ";
  stream << mf64Altitude;
  stream << " ";
  stream << mf32NorthVelocity;
  stream << " ";
  stream << mf32EastVelocity;
  stream << " ";
  stream << mf32DownVelocity;
  stream << " ";
  stream << mf64Roll;
  stream << " ";
  stream << mf64Pitch;
  stream << " ";
  stream << mf64Heading;
  stream << " ";
  stream << mf64WanderAngle;
  stream << " ";
  stream << mf32TrackAngle;
  stream << " ";
  stream << mf32Speed;
  stream << " ";
  stream << mf32AngularRateLong;
  stream << " ";
  stream << mf32AngularRateTrans;
  stream << " ";
  stream << mf32AngularRateDown;
  stream << " ";
  stream << mf32AccLong;
  stream << " ";
  stream << mf32AccTrans;
  stream << " ";
  stream << mf32AccDown;
  stream << " ";
  stream << mu8AlignementStatus;
}

VehicleNavigationSolution* VehicleNavigationSolution::clone() const {
  return new VehicleNavigationSolution(*this);
}
