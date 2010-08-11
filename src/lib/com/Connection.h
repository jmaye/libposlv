#ifndef CONNECTION_H
#define CONNECTION_H

#include "IOException.h"
#include "GroupCreationException.h"
#include "Group.h"

#include <string>

#include <stdint.h>

class Connection {
  Connection(const Connection &other);
  Connection& operator = (const Connection &other);

  uint8_t readByte() const throw(IOException);

  std::string readStartGroup() const throw(IOException);

  std::string readEndGroup() const throw(IOException);

  std::string mstrHost;
  uint32_t mu32Port;
  double mf64Timeout;
  int32_t mi32Socket;

public:
  Connection(const std::string &strHost, uint32_t u32Port,
    double f64Timeout = 2.5);
  ~Connection();

  const std::string& getHost() const;

  uint32_t getPort() const;

  double getTimeout() const;

  void setTimeout(double f64Time);

  void open() throw(IOException);

  void close() throw(IOException);

  bool isOpen() const;

  const Group* readGroup() throw(IOException, GroupCreationException);

  Connection& operator >> (int8_t &i8Value) throw(IOException);
  Connection& operator >> (uint8_t &u8Value) throw(IOException);
  Connection& operator >> (int16_t &i16Value) throw(IOException);
  Connection& operator >> (uint16_t &u16Value) throw(IOException);
  Connection& operator >> (int32_t &i32Value) throw(IOException);
  Connection& operator >> (uint32_t &u32Value) throw(IOException);
  Connection& operator >> (int64_t &i64Value) throw(IOException);
  Connection& operator >> (uint64_t &u64Value) throw(IOException);
  Connection& operator >> (std::string &strValue) throw(IOException);
  Connection& operator >> (float &f32Value) throw(IOException);
  Connection& operator >> (double &f64Value) throw(IOException);

protected:

};

#endif // CONNECTION_H
