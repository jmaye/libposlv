#ifndef STATIONRECORD_H
#define STATIONRECORD_H

#include "exceptions/IOException.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class StationRecord {
  friend Connection& operator >> (Connection &stream, StationRecord &obj)
    throw(IOException);
  friend std::ofstream& operator << (std::ofstream &stream,
    const StationRecord &obj);

  StationRecord(const StationRecord &other);
  StationRecord& operator = (const StationRecord &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  uint8_t mu8RecordIndexAndFlags;
  uint16_t mu16StationID;
  uint16_t mu16StationHealth;
  float mf32Distance;
  float mf32Range;
  uint8_t mu8USCGIndex;
  uint64_t mu64Seconds;
  uint8_t mu8ModulationRate;

public:
  StationRecord();
  ~StationRecord();

protected:

};

#endif // STATIONRECORD_H
