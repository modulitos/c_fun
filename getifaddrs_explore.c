#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include <ifaddrs.h>
#include <linux/if_link.h>
#include <netdb.h>

// This program returns ipv4 and ipv6 addresses for all our network
// interfaces. It's basically returning a subset of what `ip addr`
// would return.

// Exploring usage of getifaddrs:
// https://www.man7.org/linux/man-pages/man3/getifaddrs.3.html

// Inspired from i3status bar, which uses getifaddrs to display
// information about the current network connection:
// https://github.com/i3/i3status/blob/master/src/print_ip_addr.c

int main(int argc, char *argv[]) {
    struct ifaddrs *ifaddr, *addrp;
    bool found = false;

    getifaddrs(&ifaddr);

    if (ifaddr == NULL) {
        printf("ifaddr is null!\n");
        return 1;
    }

    int family, s;
    char host[NI_MAXHOST];
    for (addrp = ifaddr; addrp != NULL; addrp = addrp->ifa_next) {
        struct sockaddr *my_addr;
        my_addr = addrp->ifa_addr;

        family = addrp->ifa_addr->sa_family;

        /* Display interface name and family (including symbolic form
                    of the latter for the common families). */
        printf("%-8s %s (%d)\n", addrp->ifa_name,
               (family == AF_PACKET)  ? "AF_PACKET"
               : (family == AF_INET)  ? "AF_INET"
               : (family == AF_INET6) ? "AF_INET6"
                                      : "???",
               family);

        /* For an AF_INET* interface address, display the address. */
        if (family == AF_INET || family == AF_INET6) {
            s = getnameinfo(addrp->ifa_addr,
                            (family == AF_INET) ? sizeof(struct sockaddr_in)
                                                : sizeof(struct sockaddr_in6),
                            host, NI_MAXHOST, NULL, 0, NI_NUMERICHOST);
            if (s != 0) {
                printf("getnameinfo() failed: %s\n", gai_strerror(s));
                exit(EXIT_FAILURE);
            }

            printf("\t\taddress: <%s>\n", host);

        } else if (family == AF_PACKET && addrp->ifa_data != NULL) {
            printf("\t\tThis address is an AF_PACKET family - details won't be "
                   "displayed.\n");
        }

        found = true;
    }

    if (found == false) {
        printf("no interfaces found!\n");
        exit(EXIT_FAILURE);
    }

    freeifaddrs(ifaddr);
    exit(EXIT_SUCCESS);
}
