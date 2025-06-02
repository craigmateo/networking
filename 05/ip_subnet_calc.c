#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

/*
 * This program demonstrates basic IP subnetting operations.
 * Given an IP address and a subnet mask (in dotted-decimal form),
 * it calculates and displays:
 * - The network address (by performing a bitwise AND of the IP and mask)
 * - The broadcast address (by OR-ing the network address with the inverted mask)
 * - The number of usable hosts in the subnet
 *
 * Example:
 * IP: 192.168.123.132
 * Mask: 255.255.255.0
 * -> Network Address: 192.168.123.0
 * -> Broadcast Address: 192.168.123.255
 * -> Usable Hosts: 254
 */

// Convert dotted decimal IP to 32-bit unsigned int
unsigned int ip_to_int(const char *ip_str) {
    unsigned int b1, b2, b3, b4;
    sscanf(ip_str, "%u.%u.%u.%u", &b1, &b2, &b3, &b4);
    return (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
}

// Convert 32-bit int to dotted decimal
void int_to_ip(unsigned int ip, char *buffer) {
    sprintf(buffer, "%u.%u.%u.%u",
        (ip >> 24) & 0xFF,
        (ip >> 16) & 0xFF,
        (ip >> 8) & 0xFF,
        ip & 0xFF);
}

// Count number of 1s in subnet mask (to get prefix length)
int count_ones(unsigned int mask) {
    int count = 0;
    while (mask) {
        count += mask & 1;
        mask >>= 1;
    }
    return count;
}

int main() {
    char ip_str[20], mask_str[20];
    printf("Enter IP address (e.g., 192.168.1.10): ");
    scanf("%19s", ip_str);

    printf("Enter Subnet Mask (e.g., 255.255.255.0): ");
    scanf("%19s", mask_str);

    unsigned int ip = ip_to_int(ip_str);
    unsigned int mask = ip_to_int(mask_str);

    unsigned int network = ip & mask;
    unsigned int broadcast = network | (~mask);

    char network_str[20], broadcast_str[20];
    int_to_ip(network, network_str);
    int_to_ip(broadcast, broadcast_str);

    int prefix_length = count_ones(mask);
    int host_bits = 32 - prefix_length;
    unsigned int usable_hosts = (host_bits >= 2) ? (1 << host_bits) - 2 : 0;

    printf("\nNetwork ID:     %s\n", network_str);
    printf("Broadcast Addr: %s\n", broadcast_str);
    printf("Prefix Length:  /%d\n", prefix_length);
    printf("Usable Hosts:   %u\n", usable_hosts);

    return 0;
}
