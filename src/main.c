#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <net/if.h>

#include "ring_buffer.h"
#include "packet_filter.h"
#include "sliding_window.h"

#define MAX_PACKET_SIZE 1500

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <interface>
", argv[0]);
        return EXIT_FAILURE;
    }

    char *iface = argv[1];
    int sock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
    if (sock < 0) {
        perror("socket");
        return EXIT_FAILURE;
    }

    struct sockaddr_ll sll;
    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = if_nametoindex(iface);
    sll.sll_protocol = htons(ETH_P_ALL);

    if (bind(sock, (struct sockaddr *)&sll, sizeof(sll)) < 0) {
        perror("bind");
        close(sock);
        return EXIT_FAILURE;
    }

    printf("Listening on %s...
", iface);

    while (1) {
        char buffer[MAX_PACKET_SIZE + 1];
        struct packet pkt;
        ssize_t bytes_read = recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
        if (bytes_read <= 0) {
            if (errno == EINTR) {
                continue;
            }
            perror("recvfrom");
            close(sock);
            return EXIT_FAILURE;
        }

        pkt.data = buffer;
        pkt.len = bytes_read;
        pkt.timestamp = (uint64_t)time(NULL);

        if (process_packet(&pkt) < 0) {
            perror("process_packet");
            continue;
        }
    }

    close(sock);
    return EXIT_SUCCESS;
}

int process_packet(const struct packet *pkt) {
    // Placeholder function to demonstrate usage of packet_filter.h
    // Implement your packet processing logic here
    return 0;
}