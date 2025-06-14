// Copyright (c) 2025 Sebastian Orozco Castillo. All Rights Reserved.

#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

/**
 * @class Controller
 * @brief Manages the flow of the program and read manual input and test file
 *
 */
class Controller {
 public:
  /**
   * @brief Constructor, calls the validateParametersCount and readRequestEntry
   *
   * @param argc count of parameters
   * @param argv parameters
   */
  Controller(int argc, char *argv[]);

  /**
   * @brief to init the program, the Constructor just load the values
   */
  void initController();

  /**
   * @brief Default destructor, we don't need liberate resources
   */
  ~Controller() = default;

 private:
  /**
   * @brief saves the A=25 input in a vector with "A" and 25
   */
  std::vector<std::pair<char, uint32_t>> request;

  /**
   * @brief IP base, that includes in the parameters or test file
   */
  std::string baseIP;

  /**
   * @brief The form to manages the Subnet
   */
  bool biggerToLower;

  /**
   * @brief This is to validate the count of parameters
   *
   * @param argc count of parameters
   * @return true if parameters are 4 (manual input) or 1 (test file)
   */
  bool validateParametersCount(int argc);
  bool isTestFileEntry(int argc);

  std::array<std::string, 3> readTestFile(std::string fileName);

  /**
   * @brief This subroutine is to read the entry in case of manual input
   *
   * @param argv the argument that contains the input A=25,B=45 for example
   */
  void createSets(std::string sets);
};
