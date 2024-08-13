// udp_server.c
#include "udp_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void start_udp_server() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[MAX_PACKET_SIZE];
    char hex_buffer[BUFFER_SIZE];
    socklen_t client_len;
    ssize_t recv_len;
    int i;

    // 创建socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 初始化服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 绑定socket
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("UDP server is listening for hex packets on port %d\n", PORT);

    while (1) {
        // 接收数据
        client_len = sizeof(client_addr);
        recv_len = recvfrom(sockfd, buffer, MAX_PACKET_SIZE, 0, (struct sockaddr *)&client_addr, &client_len);
        if (recv_len < 0) {
            perror("recvfrom failed");
            close(sockfd);
            exit(EXIT_FAILURE);
        }

        // 将字节转换为十六进制字符串
        for (i = 0; i < recv_len; i++) {
            sprintf(hex_buffer + (i * 2), "%02X", (unsigned char)buffer[i]);
        }
        hex_buffer[2 * recv_len] = '\0';  // 添加字符串结束符

        // 输出接收到的十六进制数据
        printf("Received hex packet: %s\n", hex_buffer);

        // 这里可以添加你的数据处理逻辑
    }

    // 关闭socket
    close(sockfd);
}
