// Copyright (c) 2025 Sebastian Orozco Castillo. All Rights Reserved.

#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "../include/Controller.hh"
#include "../include/SubnetAllocator.hh"

Controller::Controller(int argc, char *argv[]) {
  std::string sets = "";

  if (!validateParametersCount(argc))
    throw std::runtime_error(
        "Controller::Controller(int, char*), parameters are incorrect");

  if (!isTestFileEntry(argc)) {
    this->baseIP = argv[1];
    sets = argv[2];
    this->biggerToLower = (*argv[3] == '0') ? false : true;
  } else {
    std::array<std::string, 3> testFileEntry = readTestFile(argv[1]);
    this->baseIP = testFileEntry[0];
    sets = testFileEntry[1];
    this->biggerToLower = (testFileEntry[2][0] == '0') ? false : true;
  }
  createSets(sets);
}

void Controller::initController() {
  SubnetAllocator subnetting(this->baseIP, request);
  subnetting.makeSubnets(this->biggerToLower);
  std::vector<Subnet> subnet;
  subnet = subnetting.getSubnets();
  std::cout << std::left << std::setw(6) << "Set" << std::setw(8) << "N"
            << std::setw(18) << "Net" << std::setw(8) << "Mask" << std::setw(18)
            << "BC" << std::setw(18) << "First" << std::setw(18) << "Last"
            << std::endl;
  for (auto it : subnet) {
    std::cout << std::left << std::setw(6) << it.getName() << std::setw(8)
              << it.getRequiredHosts() << std::setw(18)
              << it.getNetworkAddress().getAddress() << std::setw(8)
              << it.getSubnetMask() << std::setw(18)
              << it.getBroadcast().getAddress() << std::setw(18)
              << it.getFirstHost().getAddress() << std::setw(18)
              << it.getLastHost().getAddress() << std::endl;
  }
}

bool Controller::validateParametersCount(int argc) {
  return (argc == 4 || argc == 2) ? true : false;
}

bool Controller::isTestFileEntry(int argc) {
  return (argc == 2) ? true : false;
}

std::array<std::string, 3> Controller::readTestFile(std::string filename) {
  std::string path = "tests/" + filename;
  std::string entrySplit = "";
  std::array<std::string, 3> entryToProcess = {" ", " ", " "};
  size_t index = 0;
  std::ifstream file(path);
  // check if the file exist
  if (!file.is_open())
    throw std::runtime_error("Controller::readTestFile(std::string filename), "
                             "can't open file, check the path");

  while (std::getline(file, entrySplit, ' ') && index < 3) {
    entryToProcess[index] = entrySplit;
    index++;
  }
  file.close();
  return entryToProcess;
}

void Controller::createSets(std::string sets) {
  std::stringstream processing(sets);
  // This is going to save A=56 for example
  std::string requestComplete;
  // Separate the entry with the commas
  while (std::getline(processing, requestComplete, ',')) {
    char name = requestComplete[0];
    size_t equalSymbol = requestComplete.find('=');
    uint32_t hostsRequired = std::pow(
        2, std::ceil(std::log2(
               std::stoi(requestComplete.substr(equalSymbol + 1)) + 2)));
    request.push_back(std::make_pair(name, hostsRequired));
  }
}
