#define _DEFAULT_SOURCE
#include "../ministat.h"
#include <ifaddrs.h>
#include <net/if.h>
#include <sys/socket.h>
#include <string.h>

int
network(char *buf, size_t len, const char *interface)
{
  struct ifaddrs *ifaddr, *ifa;
  const char *icon = "󰤭";

  if (getifaddrs(&ifaddr) < 0)
    return snprintf(buf, len, "%s", icon);

  for (ifa = ifaddr; ifa; ifa = ifa->ifa_next) {
    if (!ifa->ifa_addr)
      continue;

    if (strcmp(ifa->ifa_name, interface) == 0 &&
      (ifa->ifa_flags & IFF_UP) &&
      (ifa->ifa_addr->sa_family == AF_INET)) {
      icon = "󰤨";
      break;
    }
  }

  freeifaddrs(ifaddr);

  return snprintf(buf, len, "%s", icon);
}
