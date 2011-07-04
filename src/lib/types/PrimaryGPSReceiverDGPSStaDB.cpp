#include "types/PrimaryGPSReceiverDGPSStaDB.h"

#include "com/Connection.h"
#include "utils/TypesFactory.h"

#include <fstream>

using namespace std;

const PrimaryGPSReceiverDGPSStaDB PrimaryGPSReceiverDGPSStaDB::mProto;

PrimaryGPSReceiverDGPSStaDB::PrimaryGPSReceiverDGPSStaDB() : Group(26) {
}

PrimaryGPSReceiverDGPSStaDB::
  PrimaryGPSReceiverDGPSStaDB(const PrimaryGPSReceiverDGPSStaDB &other)
  : Group(other) {
}

PrimaryGPSReceiverDGPSStaDB::~PrimaryGPSReceiverDGPSStaDB() {
}

void PrimaryGPSReceiverDGPSStaDB::read(Connection &stream)
  throw(IOException) {
  uint16_t u16ByteCount;
  stream >> u16ByteCount;

  stream >> mTimeDistance;
  mu32StationNbr = (u16ByteCount - 30) / 24;
  for (uint32_t i = 0; i < mu32StationNbr; i++)
    stream >> maStationRecord[i];
}

void PrimaryGPSReceiverDGPSStaDB::write(ofstream &stream) const {
  stream << mu16TypeID;
  stream << " ";
  stream << mTimeDistance;
  for (uint32_t i = 0; i < mu32StationNbr; i++)
    stream << maStationRecord[i];
}

PrimaryGPSReceiverDGPSStaDB* PrimaryGPSReceiverDGPSStaDB::clone() const {
  return new PrimaryGPSReceiverDGPSStaDB(*this);
}
