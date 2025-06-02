// arp_sim.c
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

/*
 * Simple ARP Table Implementation in C
 *
 * This program simulates basic ARP functionality by maintaining a small
 * ARP table that maps IPv4 addresses to MAC addresses.
 *
 * Key features:
 * - Initialize the ARP table with empty entries
 * - Add or update ARP entries (IP to MAC mappings)
 * - Lookup the MAC address associated with a given IP
 *
 * This example demonstrates how routers or hosts might manage ARP cache
 * entries to resolve network-layer IP addresses to link-layer MAC addresses
 * for local network communication.
 */

#define ARP_CACHE_SIZE 5

typedef struct {
    uint8_t ip[4];    // IPv4 address
    uint8_t mac[6];   // MAC address
    bool valid;
} arp_entry_t;

// Simulated ARP cache
arp_entry_t arp_cache[ARP_CACHE_SIZE];

// Helper to print IPv4 address
void print_ip(uint8_t ip[4]) {
    printf("%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);
}

// Helper to print MAC address
void print_mac(uint8_t mac[6]) {
    printf("%02X:%02X:%02X:%02X:%02X:%02X",
        mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

// Check ARP cache for given IP, returns index or -1 if not found
int arp_cache_lookup(uint8_t ip[4]) {
    for (int i = 0; i < ARP_CACHE_SIZE; i++) {
        if (arp_cache[i].valid && memcmp(arp_cache[i].ip, ip, 4) == 0)
            return i;
    }
    return -1;
}

// Add or update ARP cache entry
void arp_cache_add(uint8_t ip[4], uint8_t mac[6]) {
    int idx = arp_cache_lookup(ip);
    if (idx >= 0) {
        memcpy(arp_cache[idx].mac, mac, 6);
        printf("Updated ARP cache entry for IP ");
        print_ip(ip);
        printf("\n");
    } else {
        // Find empty slot
        for (int i = 0; i < ARP_CACHE_SIZE; i++) {
            if (!arp_cache[i].valid) {
                memcpy(arp_cache[i].ip, ip, 4);
                memcpy(arp_cache[i].mac, mac, 6);
                arp_cache[i].valid = true;
                printf("Added ARP cache entry for IP ");
                print_ip(ip);
                printf("\n");
                return;
            }
        }
        printf("ARP cache full, cannot add new entry.\n");
    }
}

// Simulate sending an ARP request and receiving a reply
void arp_request(uint8_t target_ip[4]) {
    printf("Sending ARP request for IP ");
    print_ip(target_ip);
    printf("\n");

    // For demo: simulate a device with MAC 11:22:33:44:55:66 responding
    uint8_t simulated_mac[6] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};

    printf("Received ARP reply: IP ");
    print_ip(target_ip);
    printf(" is at MAC ");
    print_mac(simulated_mac);
    printf("\n");

    // Add to ARP cache
    arp_cache_add(target_ip, simulated_mac);
}

int main() {
    // Initialize ARP cache empty
    memset(arp_cache, 0, sizeof(arp_cache));

    // Example IP addresses
    uint8_t ip1[4] = {192, 168, 1, 10};
    uint8_t ip2[4] = {192, 168, 1, 20};

    // Lookup IP1 in cache - expect miss
    int idx = arp_cache_lookup(ip1);
    if (idx < 0) {
        printf("IP ");
        print_ip(ip1);
        printf(" not in ARP cache, sending request...\n");
        arp_request(ip1);
    }

    // Lookup IP1 again - expect hit
    idx = arp_cache_lookup(ip1);
    if (idx >= 0) {
        printf("IP ");
        print_ip(ip1);
        printf(" found in ARP cache with MAC ");
        print_mac(arp_cache[idx].mac);
        printf("\n");
    }

    // Simulate ARP request for IP2
    arp_request(ip2);

    return 0;
}
