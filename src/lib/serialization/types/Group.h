#ifndef GROUP_H
#define GROUP_H

#include "GroupCreationException.h"
#include "TypeCastException.h"
#include "IOException.h"

#include <iosfwd>

#include <stdint.h>

class Connection;

class Group {
  friend Connection& operator >> (Connection &stream, Group &obj)
    throw(IOException);
  friend std::ofstream& operator << (std::ofstream &stream,
    const Group &obj);

  virtual void read(Connection &stream) throw(IOException) = 0;
  virtual void write(std::ofstream &stream) const = 0;

public:
  virtual ~Group();

  virtual Group* clone() const = 0;

  virtual uint16_t getTypeID() const;

  template<class O> const O& typeCast() const throw(TypeCastException) {
    if (this->mu16TypeID == O::mProto.mu16TypeID)
      return (const O&)*this;
    else
      throw TypeCastException("Group: Cast failed");
  }

  template<class O> O& typeCast() throw(TypeCastException) {
    if (this->mu16TypeID == O::mProto.mu16TypeID)
      return (O&)*this;
    else
      throw TypeCastException("Group: Cast failed");
  }

  template<class O> bool instanceof() const {
    if (this->mu16TypeID == O::mProto.mu16TypeID)
      return true;
    else
      return false;
  }

  template<class O> bool instanceof() {
    if (this->mu16TypeID == O::mProto.mu16TypeID)
      return true;
    else
      return false;
  }

protected:
  Group() throw(GroupCreationException);
  Group(uint16_t u16TypeID);
  Group(const Group &other);
  Group& operator = (const Group &other);

  const uint16_t mu16TypeID;

};

#endif // GROUP_H
