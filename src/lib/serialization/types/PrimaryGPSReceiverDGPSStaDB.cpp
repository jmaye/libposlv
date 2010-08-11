#include "PrimaryGPSReceiverDGPSStaDB.h"

#include "Connection.h"
#include "TypesFactory.h"

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

  uint32_t u32StationNbr = (u16ByteCount - 30) / 24;
  for (uint32_t i = 0; i < u32StationNbr; i++)
    stream >> maStationRecord[i];
}

void PrimaryGPSReceiverDGPSStaDB::write(ofstream &stream) const {
}

PrimaryGPSReceiverDGPSStaDB* PrimaryGPSReceiverDGPSStaDB::clone() const {
  return new PrimaryGPSReceiverDGPSStaDB(*this);
}