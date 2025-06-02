/*
 * Filename: raw_ip_send.c
 *
 * Summary:
 * This example demonstrates how to create and send a raw IPv4 packet using a raw socket in C.
 * It manually constructs an IPv4 header, calculates the checksum, and sends the packet to a specified destination IP.
 * The example conceptually illustrates the Network Layer functionality and the idea of a "next-hop" in routing,
 * where the packet is sent to the next IP address on its path.
 * 
 * Note: Requires root/admin privileges to run.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/ip.h> // Provides declarations for IP header

// Function to calculate simple checksum (for IP header)
unsigned short checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum=0;
    unsigned short result;

    for (sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if (len == 1)
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

int main() {
    int sockfd;
    char buffer[4096];

    struct iphdr *ip = (struct iphdr *) buffer;
    struct sockaddr_in dest_info;

    // Create raw socket
    sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_RAW);
    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // Clear buffer
    memset(buffer, 0, 4096);

    // Fill in the IP header fields
    ip->ihl = 5; // Header length
    ip->version = 4; // IPv4
    ip->tos = 0; // Type of service
    ip->tot_len = htons(sizeof(struct iphdr)); // Total length (header only for simplicity)
    ip->id = htons(54321); // Identification
    ip->frag_off = 0; // Fragment offset
    ip->ttl = 64; // Time to live
    ip->protocol = IPPROTO_ICMP; // Protocol (using ICMP for example)
    ip->check = 0; // Checksum (set to 0 before calculating)
    
    // Source IP (your machine, example)
    ip->saddr = inet_addr("192.168.1.2");
    // Destination IP (target machine)
    ip->daddr = inet_addr("8.8.8.8");

    // Calculate checksum
    ip->check = checksum((unsigned short *)buffer, ip->ihl * 4);

    // Set up destination info (next hop or final destination)
    dest_info.sin_family = AF_INET;
    dest_info.sin_addr.s_addr = ip->daddr; // Next-hop IP address

    printf("Sending raw IPv4 packet to %s\n", inet_ntoa(dest_info.sin_addr));

    // Send the packet
    if (sendto(sockfd, buffer, ntohs(ip->tot_len), 0,
               (struct sockaddr *)&dest_info, sizeof(dest_info)) < 0) {
        perror("Packet send failed");
        close(sockfd);
        return 1;
    }

    printf("Packet sent successfully.\n");

    close(sockfd);
    return 0;
}
