#include "GroupCreationException.h"

using namespace std;

GroupCreationException::GroupCreationException(const string &msg)
  : range_error(msg) {
}
