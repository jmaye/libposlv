#ifndef BASEGPS2MODEMSTATUS_H
#define BASEGPS2MODEMSTATUS_H

#include "types/Group.h"
#include "exceptions/IOException.h"
#include "types/TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class BaseGPS2ModemStatus : public Group {
  BaseGPS2ModemStatus();
  BaseGPS2ModemStatus(const BaseGPS2ModemStatus &other);
  BaseGPS2ModemStatus& operator = (const BaseGPS2ModemStatus &other);

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
  ~BaseGPS2ModemStatus();

  virtual BaseGPS2ModemStatus* clone() const;

  static const BaseGPS2ModemStatus mProto;

protected:
};

#endif // BASEGPS2MODEMSTATUS_H
