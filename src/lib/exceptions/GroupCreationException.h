#ifndef GROUPCREATIONEXCEPTION_H
#define GROUPCREATIONEXCEPTION_H

#include <stdexcept>
#include <string>

class GroupCreationException : public std::range_error {
  GroupCreationException& operator = (const GroupCreationException &other);

public:
  GroupCreationException(const std::string &msg = "");
  GroupCreationException(const GroupCreationException &other);

protected:

};

#endif // GROUPCREATIONEXCEPTION_H
