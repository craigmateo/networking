#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void classify_ip(const char *ip_str) {
    unsigned int o1, o2, o3, o4;
    sscanf(ip_str, "%u.%u.%u.%u", &o1, &o2, &o3, &o4);

    printf("IP Address: %s\n", ip_str);

    // Class
    if (o1 <= 127)
        printf("Class: A\n");
    else if (o1 <= 191)
        printf("Class: B\n");
    else if (o1 <= 223)
        printf("Class: C\n");
    else if (o1 <= 239)
        printf("Class: D (Multicast)\n");
    else
        printf("Class: E (Experimental)\n");

    // Type
    if (o1 == 10 ||
        (o1 == 172 && o2 >= 16 && o2 <= 31) ||
        (o1 == 192 && o2 == 168))
        printf("Type: Private IP\n");
    else if (o1 == 169 && o2 == 254)
        printf("Type: Link-Local IP\n");
    else if (o1 == 127)
        printf("Type: Loopback IP\n");
    else
        printf("Type: Public IP\n");

    printf("\n");
}

int main() {
    struct ifaddrs *ifaddr, *ifa;
    char ip[INET_ADDRSTRLEN];

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        return 1;
    }

    printf("=== Local Interface IP Addresses ===\n\n");
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if (!ifa->ifa_addr || ifa->ifa_addr->sa_family != AF_INET)
            continue;

        void *addr_ptr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
        inet_ntop(AF_INET, addr_ptr, ip, sizeof(ip));
        printf("Interface: %s\n", ifa->ifa_name);
        classify_ip(ip);
    }

    freeifaddrs(ifaddr);
    return 0;
}
