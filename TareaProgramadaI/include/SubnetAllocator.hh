// Copyright (c) 2025 Sebastian Orozco Castillo. All Rights Reserved.

#pragma once

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "../include/Subnet.hh"

/**
 * @class SubnetAllocator
 * @brief To allocate the subnets of Subnet class
 *
 */
class SubnetAllocator {
 private:
  /**
   * @brief IP base
   */
  std::string baseIP;

  /**
   * @brief the request that needs solve
   */
  std::vector<std::pair<char, uint32_t>> request;


  /**
   * @brief vector of subnets already solved (with Mask and conjunt solved)
   */
  std::vector<Subnet> subnet;

 public:
  /**
   * @brief Constructor to allocate subnets
   *
   * @param BaseIP IP base of the test file or parameter
   * @param Request The requests of subnets to allocate
   */
  SubnetAllocator(std::string BaseIP,
                  std::vector<std::pair<char, uint32_t>> Request)
      : baseIP(BaseIP), request(Request) {}

  /**
   * @brief This is to run the program, the principal function
   *
   * @param biggerToLower this means the biggest IP to lower set
   * if that changes the form is lower IP to the biggest set
   */
  void makeSubnets(bool biggerToLower);
  /**
   * @brief to get the vector of subnets
   *
   * @return subnet vector
   */
  std::vector<Subnet> getSubnets() { return subnet; }
};
