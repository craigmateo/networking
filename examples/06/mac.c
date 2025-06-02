#include <stdio.h>
#include <stdint.h>

/*
 * This program demonstrates basic interpretation of a MAC address.
 * It takes a MAC address as input and:
 * - Displays it in standard format
 * - Identifies whether it's a Unicast or Multicast address
 * - Identifies whether it's a Universally Administered Address (UAA) or Locally Administered Address (LAA)
 * - Extracts the Organizationally Unique Identifier (OUI)
 *
 * MAC Address Format: 6 bytes (48 bits)
 * Example MAC: 00:1A:2B:3C:4D:5E
 */

void print_mac_info(uint8_t mac[6]) {
    printf("MAC Address: %02X:%02X:%02X:%02X:%02X:%02X\n",
           mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

    // Check Unicast/Multicast
    if (mac[0] & 0x01) {
        printf("Address Type: Multicast\n");
    } else {
        printf("Address Type: Unicast\n");
    }

    // Check UAA/LAA
    if (mac[0] & 0x02) {
        printf("Admin Type: Locally Administered (LAA)\n");
    } else {
        printf("Admin Type: Universally Administered (UAA)\n");
    }

    printf("Organizationally Unique Identifier (OUI): %02X:%02X:%02X\n",
           mac[0], mac[1], mac[2]);
}

int main() {
    // Example MAC address (hex): 00:1A:2B:3C:4D:5E
    uint8_t mac[6] = {0x00, 0x1A, 0x2B, 0x3C, 0x4D, 0x5E};

    print_mac_info(mac);

    return 0;
}
