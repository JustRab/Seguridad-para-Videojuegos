#pragma once
#include "Prerequisites.h"
#include <bitset>

/**
 * @class AsciiBinary
 * @brief Provides utility functions for converting between ASCII characters/strings and their binary representations.
 *
 * This class offers methods to convert a single character to its binary string representation,
 * convert a string to a space-separated binary string, and perform the reverse operations.
 */

class AsciiBinary
{
public:
  /**
   * @brief Default constructor and destructor.
   */
  AsciiBinary() = default;
  ~AsciiBinary() = default;

  /**
   * @brief Converts a character to its 8-bit binary string representation.
   * @param c The character to convert.
   * @return A string of 8 characters ('0' or '1') representing the binary value of the input character.
   */
  std::string
  bitset(char c) {
    std::string result(8, '0');
    int val = static_cast<unsigned char>(c);
    for (int i = 7; i >= 0; --i) {
      result[i] = (val % 2) + '0'; // Convert to character '0' or '1'
      val /= 2;
    }

    return result;
  }

  /**
   * @brief Converts a string to a space-separated binary string representation.
   * @param input The input string to convert.
   * @return A string where each character is represented by its 8-bit binary value, separated by spaces.
   */
  std::string 
  stringToBinary(const std::string& input) {
    std::ostringstream oss;
    for (char c : input) {
      oss << bitset(c) << " "; // Convert each character to its binary representation
    }

    std::string output = oss.str();
    if (!output.empty()) {
      output.pop_back(); // Remove the last space
    }

    return output;
  }

  /**
   * @brief Converts an 8-character binary string to its corresponding ASCII character.
   * @param binary The binary string (must be 8 characters long, containing only '0' or '1').
   * @return The ASCII character represented by the binary string.
   * @throws std::invalid_argument if the input string is not a valid 8-bit binary string.
   */
  char 
  binaryToChar(const std::string& binary) {
    int value = 0;
    for (char c : binary) {
      value = (value << 1) | (c - '0'); // Convert '0'/'1' to 0/1 and build the integer
    }
    return static_cast<char>(value);
  }

  /**
   * @brief Converts a space-separated binary string to its ASCII string representation.
   * @param binaryInput The input string containing space-separated 8-bit binary values.
   * @return The decoded ASCII string.
   * @throws std::invalid_argument if any binary segment is not exactly 8 characters long.
   */
  std::string 
  binaryToString(const std::string& binaryInput) {
    std::istringstream iss(binaryInput);
    std::string output;
    std::string binary;

    while (iss >> binary) {
      if (binary.length() == 8) { // Ensure we have a full byte
        output += binaryToChar(binary);
      }
      else {
        throw std::invalid_argument("Invalid binary string: " + binary);
      }

    }
    return output;
  }
};
