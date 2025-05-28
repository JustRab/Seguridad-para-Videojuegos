#pragma once
#include "Prerequisites.h"
#include <bitset>

class AsciiBinary
{
public:
	AsciiBinary() = default;
	~AsciiBinary() = default;

	std::string bitset(char c) {
		std::string result(8, '0');
		int val = static_cast<unsigned char>(c);
		for (int i = 7; i >= 0; --i) {
			result[i] = (val % 2) + '0'; // Convert to character '0' or '1'
			val /= 2;
		}

		return result;
	}

	std::string stringToBinary(const std::string& input) {
		std::ostringstream oss;
		for (char c : input) {
			oss << bitset(c)<< " "; // Convert each character to its binary representation
		}

		std::string output = oss.str();
		if (!output.empty()) {
			output.pop_back(); // Remove the last space
		}

		return output;
	}

	char binaryToChar(const std::string& binary) {
		int value = 0;
		for (char c : binary) {
			value = (value << 1) | (c - '0'); // Convert '0'/'1' to 0/1 and build the integer
		}
		return static_cast<char>(value);
	}

	std::string binaryToString(const std::string& binaryInput) {
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

private:

};
