/*
 * nat_pat_sim.c
 *
 * Summary:
 * This C program simulates Network Address Translation (NAT) Overloading, also known as 
 * Port Address Translation (PAT), as used in SOHO (Small Office/Home Office) networks. 
 * It mimics how a NAT router maps multiple private IP:port combinations to a single 
 * public IP with different public ports. The simulation includes a translation table 
 * with a fixed size, demonstrating how session management works in a basic NAT environment.
 *
 * Usage:
 * Compile with: gcc nat_pat_sim.c -o nat_pat_sim
 * Run with: ./nat_pat_sim
 *
 * Limitations:
 * - This is a simplified simulation; no actual networking is performed.
 * - Translation table size is fixed (MAX_SESSIONS).
 */

#include <stdio.h>
#include <string.h>

#define MAX_SESSIONS 5

typedef struct {
    char private_ip[16];
    int private_port;
    int public_port;
} NATSession;

NATSession nat_table[MAX_SESSIONS];
int current_port = 40000; // Starting public port

int find_session(char *ip, int port) {
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (strcmp(nat_table[i].private_ip, ip) == 0 &&
            nat_table[i].private_port == port) {
            return i;
        }
    }
    return -1;
}

int add_session(char *ip, int port) {
    for (int i = 0; i < MAX_SESSIONS; i++) {
        if (nat_table[i].private_port == 0) { // empty slot
            strcpy(nat_table[i].private_ip, ip);
            nat_table[i].private_port = port;
            nat_table[i].public_port = current_port++;
            return i;
        }
    }
    return -1;
}

void simulate_outgoing_packet(char *private_ip, int private_port) {
    int index = find_session(private_ip, private_port);
    if (index == -1) {
        index = add_session(private_ip, private_port);
        if (index == -1) {
            printf("NAT table full! Cannot establish new session.\n");
            return;
        }
    }
    printf("NAT: %s:%d -> Public IP:PORT %s:%d\n", private_ip, private_port,
           "203.0.113.1", nat_table[index].public_port);
}

int main() {
    printf("=== Simulating NAT Overloading (PAT) ===\n\n");

    simulate_outgoing_packet("192.168.0.2", 1234);
    simulate_outgoing_packet("192.168.0.3", 5678);
    simulate_outgoing_packet("192.168.0.4", 9012);
    simulate_outgoing_packet("192.168.0.5", 3456);
    simulate_outgoing_packet("192.168.0.6", 7890);
    simulate_outgoing_packet("192.168.0.7", 1111); // Will fail: table full

    return 0;
}
