#ifndef ChannelStatusData_H
#define ChannelStatusData_H

#include "exceptions/IOException.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class ChannelStatusData {
  friend Connection& operator >> (Connection &stream, ChannelStatusData &obj)
    throw(IOException);
  friend std::ofstream& operator << (std::ofstream &stream,
    const ChannelStatusData &obj);

  ChannelStatusData(const ChannelStatusData &other);
  ChannelStatusData& operator = (const ChannelStatusData &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  uint16_t mu16SVPRN;
  uint16_t mu16ChannelTrackingStatus;
  float mf32SVAzimuth;
  float mf32SVElevation;
  float mf32SVL1SNR;
  float mf32SVL2SNR;

public:
  ChannelStatusData();
  ~ChannelStatusData();

protected:

};

#endif // ChannelStatusData_H
