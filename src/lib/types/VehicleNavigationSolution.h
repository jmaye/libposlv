#ifndef VEHICLENAVIGATIONSOLUTION_H
#define VEHICLENAVIGATIONSOLUTION_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class VehicleNavigationSolution : public Group {
  VehicleNavigationSolution();
  VehicleNavigationSolution(const VehicleNavigationSolution &other);
  VehicleNavigationSolution&
    operator = (const VehicleNavigationSolution &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 132;

  TimeDistance mTimeDistance;
  double mf64Latitude;
  double mf64Longitude;
  double mf64Altitude;
  float mf32NorthVelocity;
  float mf32EastVelocity;
  float mf32DownVelocity;
  double mf64Roll;
  double mf64Pitch;
  double mf64Heading;
  double mf64WanderAngle;
  float mf32TrackAngle;
  float mf32Speed;
  float mf32AngularRateLong;
  float mf32AngularRateTrans;
  float mf32AngularRateDown;
  float mf32AccLong;
  float mf32AccTrans;
  float mf32AccDown;
  uint8_t mu8AlignementStatus;

public:
  ~VehicleNavigationSolution();

  virtual VehicleNavigationSolution* clone() const;

  static const VehicleNavigationSolution mProto;

protected:
};

#endif // VEHICLENAVIGATIONSOLUTION_H
