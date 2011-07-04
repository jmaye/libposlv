#include "com/Connection.h"
#include "types/Group.h"

#include <iostream>
#include <fstream>

#include <stdlib.h>
#include <stdint.h>
#include <sys/time.h>

using namespace std;

static double seconds() {
  struct timeval now;
  if (gettimeofday(&now, 0L)) {
    perror("seconds");
    exit(1);
  } else
    return (double)((double)now.tv_sec + ((double)now.tv_usec / 1000000.0));
}

int main(int argc, char **argv) {
  if (argc != 4) {
    cerr << "Usage: " << argv[0] << " <IP> <Port> <LogFilename>" << endl;
    return -1;
  }
  Connection com(argv[1], atoi(argv[2]));
  com.open();
  while (1) {
    const Group *result = com.readGroup();
    ofstream logFile(argv[3], ios_base::app);
    logFile << fixed << seconds() << " ";
    logFile << *result;
    logFile << endl;
    logFile.close();
    delete result;
  }
  com.close();
  return 0;
}
