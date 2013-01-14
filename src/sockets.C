#include "sockets.H"
#include "debug.H"
#include "functions.H"
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFF 2048

void start_socket_example()
{
  struct addrinfo hints, *res;
  int socketfd, r2;
  char ipstr[INET6_ADDRSTRLEN];

  memset(&hints, 0, sizeof(hints));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  printf("Getaddrinfo for preset www.internic.at ...\n");

  if((r2 = getaddrinfo("www.internic.at", "80", &hints, &res)) != 0)
    {
      printf("getaddrinfo: %s\n", gai_strerror(r2));
      return;
    }

  if ((socketfd = socket(res->ai_family, res->ai_socktype,
		       res->ai_protocol)) == -1) {
    printf("client: socket\n");
  }
  void *addr = NULL;
  if (res->ai_family == AF_INET) 
    { 
      struct sockaddr_in *ipv4 = (struct sockaddr_in *)res->ai_addr;
      addr = &(ipv4->sin_addr);
    }else{ 
    struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)res->ai_addr;
    addr = &(ipv6->sin6_addr);
  }

  inet_ntop(res->ai_family, addr, ipstr, sizeof(ipstr));
  printf("Connecting to: %s ...\n", ipstr);

  if(connect(socketfd, res->ai_addr, res->ai_addrlen) == -1)
    {
      printf("Error %s\n", clean_errno()); //connect sets errno
      freeaddrinfo(res);
      return;
    }

  printf("Connected!\n");

  printf("Sending GET /index.html HTTP/1.0\n");
  
  char *buffer = (char *) malloc(BUFF);
  strcpy(buffer, "GET /index.html HTTP/1.0\n\r\n\r");
  send(socketfd, buffer, strlen(buffer), 0);
  
  int rcvfd;
  rcvfd=recv(socketfd, buffer, BUFF-1, 0);

  if(rcvfd > 0)
    buffer[rcvfd] = '\0';

  printf("GOT: %s\n", buffer);

  free(buffer);
  close(socketfd);

  freeaddrinfo(res);
}
