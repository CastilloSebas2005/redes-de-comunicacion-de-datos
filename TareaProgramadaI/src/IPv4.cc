// Copyright (c) 2025 Sebastian Orozco Castillo. All Rights Reserved.

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "../include/IPv4.hh"

IPv4::IPv4(std::string Address) {
  std::istringstream separator(Address);
  // to separate the IP numbers
  char dot = ' ';
  // To allocate the IP in the array we need use INT
  int octet[4];
  if (!(separator >> (octet[0]) >> dot >> (octet[1]) >> dot >> (octet[2]) >>
        dot >> (octet[3]))) {
    throw std::invalid_argument(
        "IPv4::IPv4(std::string Address), Invalid IP address format");
  }
  if ((octet[0] < 0 || octet[1] < 0 || octet[2] < 0 || octet[3] < 0) ||
      (octet[0] > 255 || octet[1] > 255 || octet[2] > 255 || octet[3] > 255)) {
    throw std::out_of_range("IPv4::IPv4(std::string Address), Invalid IP "
                            "address, out of the range");
  }
  // This is to save the address in 32 bits variable
  // if octet [0] = 192
  // shift left 24 bits and put octet [0] = 192
  // so the first 8 bits are gonna save that value
  // then with '|' operator, we can use this to save the next values
  address = (octet[0] << 24) | (octet[1] << 16) | (octet[2] << 8) | octet[3];
}

std::string IPv4::getAddress() const {
  // The same idea, but in this case we add the & 0xFF
  // this is just for touch the bits that we want and
  // no modify the others bits
  return std::to_string((address >> 24) & 0xFF) + "." +
         std::to_string((address >> 16) & 0xFF) + "." +
         std::to_string((address >> 8) & 0xFF) + "." +
         std::to_string(address & 0xFF);
}
