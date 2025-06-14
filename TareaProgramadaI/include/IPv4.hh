// Copyright (c) 2025 Sebastian Orozco Castillo. All Rights Reserved.

#pragma once

#include <cstdint>
#include <string>

/**
 * @class IPv4
 * @brief To manages the IPv4
 *
 */
class IPv4 {
 private:
  /**
   * @brief The address is gonna saved in 32 bits
   */
  uint32_t address;

 public:
  /**
   * @brief Constructor
   */
  IPv4():address(0) {}

  /**
   * @brief Constructor that receive the IPv4 in uint32_t
   *
   * @param Address uint32_t
   */
  explicit IPv4(uint32_t Address) : address(Address) {}

  /**
   * @brief Constructor that receive the IPv4 in string
   *
   * @param Address std::string
   */
  explicit IPv4(std::string Address);

  /**
   * @brief get the address, needs to shift the bits to converts the bits to string
   * is more like a parser
   */
  std::string getAddress() const;

  /**
   * @brief To add hosts and create a new IPv4 class of that
   *
   * @param hosts uint32_t
   * @return IPv4
   */
  IPv4 addHosts(uint32_t hosts) const { return IPv4(address + hosts); }

  /**
   * @brief Same of addHosts but in this case with a subtraction
   *
   * @param hosts uint32_t
   * @return IPv4
   */
  IPv4 subsHosts(uint32_t hosts) const { return IPv4(address - hosts); }
};
