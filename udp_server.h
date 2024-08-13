// udp_server.h
#ifndef UDP_SERVER_H
#define UDP_SERVER_H

#define PORT 8088
#define MAX_PACKET_SIZE 10
#define BUFFER_SIZE (2 * MAX_PACKET_SIZE + 1)

void start_udp_server();

#endif // UDP_SERVER_H
