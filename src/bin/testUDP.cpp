#include <iostream>

#include <arpa/inet.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char** argv) {
  ssize_t sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (socket < 0) {
    perror("");
    return 1;
  }

  struct sockaddr_in server;
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(5600);
  if (bind(sock, (struct sockaddr*)&server, sizeof(struct sockaddr_in)) ==
    -1) {
    perror("");
    return 1;
  }

  char buffer[1500];

  while (1) {
    struct sockaddr_in client;
    socklen_t size;
    ssize_t res = recvfrom(sock, buffer, 1500, 0, (struct sockaddr*)&client,
      &size);
    std::cout << res << std::endl;
  }

  if (close(sock) < 0) {
    perror("");
    return 1;
  }

  return 0;
}
