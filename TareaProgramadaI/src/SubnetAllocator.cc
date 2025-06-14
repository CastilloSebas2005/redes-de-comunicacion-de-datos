// Copyright (c) 2025 Sebastian Orozco Castillo. All Rights Reserved.

#include <algorithm>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <utility>
#include <vector>

#include "../include/SubnetAllocator.hh"
#include "../include/IPv4.hh"
#include "../include/Subnet.hh"

void SubnetAllocator::makeSubnets(bool biggerToLower) {
  IPv4 currentIP(baseIP);
  std::vector<std::pair<char, uint32_t>> requestC = request;
  // Bigger set with lower IP
  if (biggerToLower) {
    std::sort(requestC.begin(), requestC.end(),
              [](const std::pair<char, uint32_t> &a,
                 const std::pair<char, uint32_t> &b) {
                if (a.second == b.second)
                  return a.first < b.first;
                return a.second > b.second;
              });
    // Bigger set with higher IP
  } else {
    std::sort(requestC.begin(), requestC.end(),
              [](const std::pair<char, uint32_t> &a,
                 const std::pair<char, uint32_t> &b) {
                if (a.second == b.second)
                  return a.first > b.first;
                return a.second > b.second;
              });
    currentIP = currentIP.addHosts(requestC[0].second);
  }
  for (size_t i = 0; i < requestC.size(); i++) {
    Subnet createSubnet(requestC[i].first, requestC[i].second, currentIP);
    subnet.push_back(createSubnet);
    if (i < requestC.size() - 1) {
      currentIP =
          createSubnet.getNextNetwork(biggerToLower, requestC[i + 1].second);
    }
  }
  std::sort(subnet.begin(), subnet.end(),
            [](Subnet &a, Subnet &b) { return a.getName() < b.getName(); });
}
