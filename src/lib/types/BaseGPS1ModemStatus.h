#ifndef BASEGPS1MODEMSTATUS_H
#define BASEGPS1MODEMSTATUS_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class BaseGPS1ModemStatus : public Group {
  BaseGPS1ModemStatus();
  BaseGPS1ModemStatus(const BaseGPS1ModemStatus &other);
  BaseGPS1ModemStatus& operator = (const BaseGPS1ModemStatus &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 116;

  TimeDistance mTimeDistance;
  uint8_t mau8ModemResponse[16];
  uint8_t mau8ConnectionStatus[48];
  uint32_t mu32NumberOfRedialsPerDisconnect;
  uint32_t mu32MaximumNumberOfRedialsPerDisconnect;
  uint32_t mu32NumberOfDisconnects;
  uint32_t mu32DataGapLength;
  uint32_t mu32MaximumDataGapLength;

public:
  ~BaseGPS1ModemStatus();

  virtual BaseGPS1ModemStatus* clone() const;

  static const BaseGPS1ModemStatus mProto;

protected:
};

#endif // BASEGPS1MODEMSTATUS_H
