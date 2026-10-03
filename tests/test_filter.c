#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "packet_filter.h"

int main() {
    struct packet_filter filter;
    filter.proto = IPPROTO_TCP;
    filter.src_ip = htonl(INADDR_ANY);
    filter.src_port = htons(80);
    filter.dst_ip = htonl(INADDR_ANY);
    filter.dst_port = htons(8080);

    if (packet_filter_init(&filter) != 0) {
        fprintf(stderr, "Failed to initialize packet filter.
");
        return EXIT_FAILURE;
    }

    time_t start = time(NULL);
    while (time(NULL) - start < 5) {
        struct packet pkt;
        pkt.data = "Hello, world!\n";
        pkt.len = 14;
        pkt.timestamp = time(NULL);

        if (packet_filter_match(&filter, &pkt) != 0) {
            printf("Packet matched the filter.
");
        }
    }

    packet_filter_destroy(&filter);
    return EXIT_SUCCESS;
}