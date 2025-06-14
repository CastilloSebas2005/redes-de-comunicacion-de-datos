// Copyright (c) 2025 Sebastian Orozco Castillo. All Rights Reserved.

#pragma once

#include <cmath>
#include <cstdint>

#include "../include/IPv4.hh"

/**
 * @class Subnet
 * @brief This class is to manage the Subnet operation
 *
 */
class Subnet {
 private:
  char name;

  IPv4 networkAddress;
  IPv4 firstHost;
  IPv4 lastHost;
  IPv4 broadcast;

  uint32_t subnetMask;
  uint32_t requiredHosts;

 public:
  /**
   * @brief Constructor of Subnet class
   *
   * @param Name The name of the host, or set, in this case it's gonna be a char
   * @param hosts requests hosts of that network
   * @param NetworkAddress the ip address of the network
   */
  Subnet(char Name, uint32_t hosts, IPv4 NetworkAddress)
      : name(Name), networkAddress(NetworkAddress) {
    uint32_t powHosts = std::log2(hosts);
    subnetMask = 32 - powHosts;
    requiredHosts = hosts;

    firstHost = networkAddress.addHosts(1);
    lastHost = networkAddress.addHosts(requiredHosts - 2);
    broadcast = networkAddress.addHosts(requiredHosts - 1);
  }

  /**
   * @brief To get the next network available
   *
   * @param biggerToLower bool
   * @param nextHost to calculate the next network
   * @return next network with IPv4 class
   */
  IPv4 getNextNetwork(bool biggerToLower, uint32_t nextHost) {
    // This is to calculate the next network available
    if (biggerToLower) {
      return networkAddress.addHosts(requiredHosts);
    }
    return networkAddress.subsHosts(nextHost);
  }

  char getName() { return name; }

  uint32_t getSubnetMask() { return subnetMask; }

  uint32_t getRequiredHosts() { return requiredHosts; }

  IPv4 getNetworkAddress() { return networkAddress; }

  IPv4 getFirstHost() { return firstHost; }

  IPv4 getLastHost() { return lastHost; }

  IPv4 getBroadcast() { return broadcast; }
};
