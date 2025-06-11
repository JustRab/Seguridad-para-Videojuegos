#pragma once
#include "Prerequisites.h"

/**
 * @class XOREncoder
 * @brief Provides XOR-based encoding and decoding utilities, including brute-force attacks.
 *
 * This class allows encoding a string using a key with the XOR operation, converting hex strings to bytes,
 * printing data in hexadecimal format, validating printable text, and performing brute-force attacks
 * with 1-byte, 2-byte, and dictionary-based keys.
 */
class
XOREncoder {
public:

  /**
   * @brief Default constructor and destructor.
   */
  XOREncoder() = default;
  ~XOREncoder() = default;

  /**
   * @brief Encodes the input string using XOR with the provided key.
   * @param input The string to be encoded.
   * @param key The key to be used for encoding (repeats if shorter than input).
   * @return The encoded string.
   */
  std::string
  encode(const std::string& input, const std::string& key) {
    std::string output = input;
    for (int i = 0; i < input.size(); i++) {
      output[i] = input[i] ^ key[i % key.size()];
    }
    return output;
  }

  /**
   * @brief Converts a space-separated hex string to a vector of bytes.
   * @param input The input string containing hex values separated by spaces.
   * @return A vector of bytes corresponding to the hex values.
   */
  std::vector<unsigned char>
  HexToBytes(const std::string& input) {
    std::vector<unsigned char> bytes;
    std::istringstream iss(input);
    std::string hexValue;

    while (iss >> hexValue) {
      if (hexValue.size() == 1) {
        hexValue = "0" + hexValue;
      }
      unsigned int byte;
      std::stringstream ss;
      ss << std::hex << hexValue;
      ss >> byte;
      bytes.push_back(static_cast<unsigned char>(byte));
    }
    return bytes;
  }

  /**
   * @brief Prints the input string as hexadecimal values.
   * @param input The string to print in hex format.
   */
  void
  printHex(const std::string& input) {
    for (unsigned char c : input) {
      std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)c << " ";
    }
  }

  /**
   * @brief Checks if the given string contains only printable characters, spaces, or newlines.
   * @param data The string to validate.
   * @return True if all characters are printable or whitespace, false otherwise.
   */
  bool 
  isValidText(const std::string& data) {
    return std::all_of(data.begin(), data.end(), [](unsigned char c) {
      return std::isprint(c) || std::isspace(c) || c == '\n' || c == ' ';
      });
  }

  /**
   * @brief Performs a brute-force attack using all possible 1-byte keys.
   * @param cifrado The encrypted data as a vector of bytes.
   *
   * Prints all possible plaintexts that result in valid text.
   */
  void
  bruteForce_1Byte(const std::vector<unsigned char>& cifrado) {
    for (int clave = 0; clave < 256; ++clave) {
      std::string result;

      for (unsigned char c : cifrado) {
        result += static_cast<unsigned char>(c ^ clave);
      }

      if (isValidText(result)) {
        std::cout << "=============================\n";
        std::cout << "Clave 1 byte  : '" << static_cast<char>(clave)
          << "' (0x" << std::hex << std::setw(2) << std::setfill('0') << clave << ")\n";
        std::cout << "Texto posible : " << result << "\n";
      }
    }
  }

  /**
   * @brief Performs a brute-force attack using all possible 2-byte keys.
   * @param cifrado The encrypted data as a vector of bytes.
   *
   * Prints all possible plaintexts that result in valid text.
   */
  void
  bruteForce_2Byte(const std::vector<unsigned char>& cifrado) {
    for (int b1 = 0; b1 < 256; ++b1) {
      for (int b2 = 0; b2 < 256; ++b2) {
        std::string result;
        unsigned char key[2] = { static_cast<unsigned char>(b1), static_cast<unsigned char>(b2) };

        for (int i = 0; i < cifrado.size(); i++) {
          result += cifrado[i] ^ key[i % 2];
        }

        if (isValidText(result)) {
          std::cout << "=============================\n";
          std::cout << "Clave 2 bytes : '" << static_cast<char>(b1) << static_cast<char>(b2)
            << "' (0x" << std::hex << std::setw(2) << std::setfill('0') << b1
            << " 0x" << std::setw(2) << std::setfill('0') << b2 << ")\n";
          std::cout << "Texto posible : " << result << "\n";
        }

      }
    }
  }

  /**
   * @brief Performs a brute-force attack using a dictionary of common keys.
   * @param cifrado The encrypted data as a vector of bytes.
   *
   * Prints all possible plaintexts that result in valid text for each dictionary key.
   */
  void 
  bruteForceByDictionary(const std::vector<unsigned char>& cifrado) {
    std::vector<std::string> clavesComunes = {
      "clave", "admin", "1234", "root", "test", "abc", "hola", "user",
      "pass", "12345", "0000", "password", "default"
    };

    for (const auto& clave : clavesComunes) {
      std::string result;
      for (int i = 0; i < cifrado.size(); i++) {
        result += static_cast<unsigned char>(cifrado[i] ^ clave[i % clave.size()]);
      }
      if (isValidText(result)) {
        std::cout << "=============================\n";
        std::cout << "Clave de diccionario: '" << clave << "'\n";
        std::cout << "Texto posible : " << result << "\n";
      }
    }
  }
};