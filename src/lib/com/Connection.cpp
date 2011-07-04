#include "com/Connection.h"

#include "serialization/TypesFactory.h"

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <string.h>
#include <math.h>

using namespace std;

Connection::Connection(const string &strHost, uint32_t u32Port,
  double f64Timeout)
 : mstrHost(strHost),
   mu32Port(u32Port),
   mf64Timeout(f64Timeout),
   mi32Socket(0) {
}

Connection::~Connection() {
  close();
}

const string& Connection::getHost() const {
  return mstrHost;
}

uint32_t Connection::getPort() const {
  return mu32Port;
}

double Connection::getTimeout() const {
  return mf64Timeout;
}

void Connection::setTimeout(double f64Time) {
  mf64Timeout = f64Time;
}

void Connection::open() throw(IOException) {
  mi32Socket = socket(AF_INET, SOCK_STREAM, 0);
  if (mi32Socket == -1)
    throw IOException("Connection::open: Socket creation failed");

  int32_t i32Flag = 1;
  if (setsockopt(mi32Socket, IPPROTO_TCP, TCP_NODELAY, (char*)&i32Flag,
    sizeof(int32_t)) == -1)
    throw IOException("doOpen: Set TCP_NODELAY failed");

  struct sockaddr_in server;
  memset(&server, 0, sizeof(struct sockaddr_in));
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(mstrHost.c_str());
  server.sin_port = htons(mu32Port);
  if (connect(mi32Socket, (struct sockaddr*)&server, sizeof(server)) == -1)
    throw IOException("Connection::open: Socket connection failed");
}

void Connection::close() throw(IOException) {
  if (mi32Socket != 0) {
    int32_t i32Res = ::close(mi32Socket);
    if (i32Res == -1)
      throw IOException("Connection::close: Socket closing failed");
  }
  mi32Socket = 0;
}

bool Connection::isOpen() const {
  return (mi32Socket != 0);
}

uint8_t Connection::readByte() const throw(IOException) {
  double f64IntPart;
  double f64FractPart = modf(mf64Timeout , &f64IntPart);
  struct timeval waitd;
  waitd.tv_sec = f64IntPart;
  waitd.tv_usec = f64FractPart * 1000000;
  fd_set readFlags;
  FD_ZERO(&readFlags);
  FD_SET(mi32Socket, &readFlags);
  int32_t i32Res = select(mi32Socket + 1, &readFlags, (fd_set*)0,
    (fd_set*)0, &waitd);
  if(i32Res < 0)
    throw IOException("Connection::readByte: Read select failed");
  uint8_t u8Byte;
  if (FD_ISSET(mi32Socket, &readFlags)) {
    FD_CLR(mi32Socket, &readFlags);
    if (::read(mi32Socket, &u8Byte, 1) == -1)
      throw IOException("Connection::readByte: Read failed");
  }
  else
    throw IOException("Connection::readByte: Read timeout");
  return u8Byte;
}

const Group* Connection::readGroup()
  throw(IOException, GroupCreationException) {
  if(mi32Socket == 0)
    open();
  string startString;
  do {
    startString = readStartGroup();
  } while (startString != "$GRP");

  uint16_t u16GroupID;
  *this >> u16GroupID;

  Group *groupRead = TypesFactory::createGroup(u16GroupID);
  *this >> *groupRead;

  uint16_t u16Checksum;
  *this >> u16Checksum;

  // TODO: Checksum control

  string endString = readEndGroup();
  if (endString != "$#")
    throw IOException("Connection::readGroup: End of group read failed");
  return groupRead;
}

string Connection::readStartGroup() const throw(IOException) {
  string outputString;
  outputString.push_back(readByte());
  outputString.push_back(readByte());
  outputString.push_back(readByte());
  outputString.push_back(readByte());
  return outputString;
}

string Connection::readEndGroup() const throw(IOException) {
  string outputString;
  outputString.push_back(readByte());
  outputString.push_back(readByte());
  return outputString;
}

void Connection::sendControl() throw(IOException) {
  if(mi32Socket == 0)
    open();
  
}

Connection& Connection::operator >> (int8_t &i8Value) throw(IOException) {
  i8Value = (int8_t)readByte();
  return *this;
}

Connection& Connection::operator >> (uint8_t &u8Value) throw(IOException) {
  u8Value = readByte();
  return *this;
}

Connection& Connection::operator >> (int16_t &i16Value) throw(IOException) {
  ((uint8_t*)&i16Value)[0] = readByte();
  ((uint8_t*)&i16Value)[1] = readByte();
  return *this;
}

Connection& Connection::operator >> (uint16_t &u16Value) throw(IOException) {
  ((uint8_t*)&u16Value)[0] = readByte();
  ((uint8_t*)&u16Value)[1] = readByte();
  return *this;
}

Connection& Connection::operator >> (int32_t &i32Value) throw(IOException) {
  ((uint8_t*)&i32Value)[0] = readByte();
  ((uint8_t*)&i32Value)[1] = readByte();
  ((uint8_t*)&i32Value)[2] = readByte();
  ((uint8_t*)&i32Value)[3] = readByte();
  return *this;
}

Connection& Connection::operator >> (uint32_t &u32Value) throw(IOException) {
  ((uint8_t*)&u32Value)[0] = readByte();
  ((uint8_t*)&u32Value)[1] = readByte();
  ((uint8_t*)&u32Value)[2] = readByte();
  ((uint8_t*)&u32Value)[3] = readByte();
  return *this;
}

Connection& Connection::operator >> (int64_t &i64Value) throw(IOException) {
  ((uint8_t*)&i64Value)[0] = readByte();
  ((uint8_t*)&i64Value)[1] = readByte();
  ((uint8_t*)&i64Value)[2] = readByte();
  ((uint8_t*)&i64Value)[3] = readByte();
  ((uint8_t*)&i64Value)[4] = readByte();
  ((uint8_t*)&i64Value)[5] = readByte();
  ((uint8_t*)&i64Value)[6] = readByte();
  ((uint8_t*)&i64Value)[7] = readByte();
  return *this;
}

Connection& Connection::operator >> (uint64_t &u64Value) throw(IOException) {
  ((uint8_t*)&u64Value)[0] = readByte();
  ((uint8_t*)&u64Value)[1] = readByte();
  ((uint8_t*)&u64Value)[2] = readByte();
  ((uint8_t*)&u64Value)[3] = readByte();
  ((uint8_t*)&u64Value)[4] = readByte();
  ((uint8_t*)&u64Value)[5] = readByte();
  ((uint8_t*)&u64Value)[6] = readByte();
  ((uint8_t*)&u64Value)[7] = readByte();
  return *this;
}


Connection& Connection::operator >> (std::string &strValue) throw(IOException) {
  uint32_t u32Length;
  ((uint8_t*)&u32Length)[0] = readByte();
  ((uint8_t*)&u32Length)[1] = readByte();
  ((uint8_t*)&u32Length)[2] = readByte();
  ((uint8_t*)&u32Length)[3] = readByte();
  for (uint32_t i = 0; i < u32Length; i++)
    strValue.push_back(readByte());
  return *this;
}

Connection& Connection::operator >> (float &f32Value) throw(IOException) {
  ((uint8_t*)&f32Value)[0] = readByte();
  ((uint8_t*)&f32Value)[1] = readByte();
  ((uint8_t*)&f32Value)[2] = readByte();
  ((uint8_t*)&f32Value)[3] = readByte();
  return *this;
}

Connection& Connection::operator >> (double &f64Value) throw(IOException) {
  ((uint8_t*)&f64Value)[0] = readByte();
  ((uint8_t*)&f64Value)[1] = readByte();
  ((uint8_t*)&f64Value)[2] = readByte();
  ((uint8_t*)&f64Value)[3] = readByte();
  ((uint8_t*)&f64Value)[4] = readByte();
  ((uint8_t*)&f64Value)[5] = readByte();
  ((uint8_t*)&f64Value)[6] = readByte();
  ((uint8_t*)&f64Value)[7] = readByte();
  return *this;
}
