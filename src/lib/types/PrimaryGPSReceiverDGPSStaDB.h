#ifndef PRIMARYGPSRECEIVERDGPSSTADB_H
#define PRIMARYGPSRECEIVERDGPSSTADB_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"
#include "types/StationRecord.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class PrimaryGPSReceiverDGPSStaDB : public Group {
  PrimaryGPSReceiverDGPSStaDB();
  PrimaryGPSReceiverDGPSStaDB(const PrimaryGPSReceiverDGPSStaDB &other);
  PrimaryGPSReceiverDGPSStaDB& operator =
    (const PrimaryGPSReceiverDGPSStaDB &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 30;

  TimeDistance mTimeDistance;
  StationRecord maStationRecord[10];
  uint32_t mu32StationNbr;

public:
  ~PrimaryGPSReceiverDGPSStaDB();

  virtual PrimaryGPSReceiverDGPSStaDB* clone() const;

  static const PrimaryGPSReceiverDGPSStaDB mProto;

protected:
};

#endif // PRIMARYGPSRECEIVERDGPSSTADB_H
