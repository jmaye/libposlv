#ifndef VEHICLENAVIGATIONPERFORMANCE_H
#define VEHICLENAVIGATIONPERFORMANCE_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class VehicleNavigationPerformance : public Group {
  VehicleNavigationPerformance();
  VehicleNavigationPerformance(const VehicleNavigationPerformance &other);
  VehicleNavigationPerformance&
    operator = (const VehicleNavigationPerformance &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 80;

  TimeDistance mTimeDistance;
  float mf32NorthPositionRMSError;
  float mf32EastPositionRMSError;
  float mf32DownPositionRMSError;
  float mf32NorthVelocityRMSError;
  float mf32EastVelocityRMSError;
  float mf32DownVelocityRMSError;
  float mf32RollRMSError;
  float mf32PitchRMSError;
  float mf32HeadingRMSError;
  float mf32ErrorEllipsoidSemiMajor;
  float mf32ErrorEllipsoidSemiMinor;
  float mf32ErrorEllipsoidOrientation;


public:
  ~VehicleNavigationPerformance();

  virtual VehicleNavigationPerformance* clone() const;

  static const VehicleNavigationPerformance mProto;

protected:
};

#endif // VEHICLENAVIGATIONPERFORMANCE_H
