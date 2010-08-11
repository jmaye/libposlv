#ifndef GENERALSTATUSFDIR_H
#define GENERALSTATUSFDIR_H

#include "Group.h"
#include "IOException.h"
#include "TimeDistance.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class GeneralStatusFDIR : public Group {
  GeneralStatusFDIR();
  GeneralStatusFDIR(const GeneralStatusFDIR &other);
  GeneralStatusFDIR& operator = (const GeneralStatusFDIR &other);

  virtual void read(Connection &stream) throw(IOException);
  virtual void write(std::ofstream &stream) const;

  static const uint16_t mcu16ByteCount = 60;

  TimeDistance mTimeDistance;
  uint32_t mu32GeneralStatusA;
  uint32_t mu32GeneralStatusB;
  uint32_t mu32GeneralStatusC;
  uint32_t mu32FDIRLevel1Status;
  uint16_t mu16FDIRLevel1Failures;
  uint16_t mu16FDIRLevel2Status;
  uint16_t mu16FDIRLevel3Status;
  uint16_t mu16FDIRLevel4Status;
  uint16_t mu16FDIRLevel5Status;
  uint32_t mu32ExtendedStatus;

public:
  ~GeneralStatusFDIR();

  virtual GeneralStatusFDIR* clone() const;

  static const GeneralStatusFDIR mProto;

protected:
};

#endif // GENERALSTATUSFDIR_H
