#pragma once
#include "Prerequisites.h"

/**
 * @class DES
 * @brief Implements a simplified version of the Data Encryption Standard (DES) block cipher.
 *
 * This class provides methods for key scheduling, initial and final permutations, expansion,
 * substitution using S-boxes, permutation, and the Feistel function. It supports encoding
 * a 64-bit plaintext block using a 64-bit key.
 */
class 
DES {
public:
  /**
   * @brief Default constructor.
   */
  DES() = default;

  /**
   * @brief Constructs a DES object with a given 64-bit key and generates subkeys.
   * @param key The 64-bit key as a std::bitset.
   */
  DES(const std::bitset<64>& key) : key(key) {
    generateSubkeys();
  }

  /**
   * @brief Default destructor.
   */
  ~DES() = default;

  /**
   * @brief Generates 16 subkeys for the 16 DES rounds.
   *
   * This simplified version creates subkeys by rotating and masking the main key.
   */
  void 
  generateSubkeys() {
    for (int i = 0; i < 16; ++i) {
      // Simplificada: subclave fija con rotación de bits
      std::bitset<48> subkey((key.to_ullong() >> i) & 0xFFFFFFFFFFFF);
      subkeys.push_back(subkey);
    }
  }

  /**
   * @brief Performs the initial permutation (identity in this simplified version).
   * @param input The 64-bit input block.
   * @return The permuted 64-bit block.
   */
  std::bitset<64>
  iPermutation(const std::bitset<64>& input) {
    std::bitset<64> output;
    for (int i = 0; i < 64; i++) {
      output[i] = input[i];
    }
    return output;
  }

  /**
   * @brief Expands a 32-bit half-block to 48 bits using the expansion table.
   * @param halfBlock The 32-bit input half-block.
   * @return The expanded 48-bit block.
   */
  std::bitset<48>
  expand(const std::bitset<32>& halfBlock) {
    std::bitset<48> output;

    for (int i = 0; i < 48; i++) {
      output[i] = halfBlock[32 - EXPANSION_TABLE[i]];
    }

    return output;
  }

  /**
   * @brief Substitutes a 48-bit input using a simplified S-box.
   * @param input The 48-bit input block.
   * @return The substituted 32-bit block.
   */
  std::bitset<32>
  substitute(const std::bitset<48>& input) {
    std::bitset<32> output;

    for (int i = 0; i < 8; i++) {
      int row = (input[i * 6] << 1) | input[i * 6 + 5]; // Bits 1 y 6
      int col = (input[i * 6 + 1] << 3) | (input[i * 6 + 2] << 2) |
        (input[i * 6 + 3] << 1) | input[i * 6 + 4]; // Bits 2-5
      int sboxValue = SBOX[row % 4][col % 16]; // Valor de la S-Box

      for (int j = 0; j < 4; j++) {
        output[i * 4 + j] = (sboxValue >> (3 - j)) & 1; // Extraer bits
      }
    }

    return output;
  }

  /**
   * @brief Applies the P permutation to a 32-bit input block.
   * @param input The 32-bit input block.
   * @return The permuted 32-bit block.
   */
  std::bitset<32> 
  permuteP(const std::bitset<32>& input) {
    std::bitset<32> output;

    for (int i = 0; i < 32; i++) {
      output[i] = input[32 - P_TABLE[i]];
    }

    return output;
  }

  /**
   * @brief The Feistel function used in each DES round.
   * @param right The 32-bit right half-block.
   * @param subkey The 48-bit subkey for the round.
   * @return The 32-bit output of the Feistel function.
   */
  std::bitset<32>
  feistel(const std::bitset<32>& right, const std::bitset<48>& subkey) {
    auto expandend = expand(right);
    auto xored = expandend ^ subkey;
    auto substituted = substitute(xored);
    auto permuted = permuteP(substituted);
    return permuted;
  }

  /**
   * @brief Performs the final permutation (identity in this simplified version).
   * @param input The 64-bit input block.
   * @return The permuted 64-bit block.
   */
  std::bitset<64>
  fPermutation(const std::bitset<64>& input) {
    std::bitset<64> output;
    for (int i = 0; i < 64; i++) {
      output[i] = input[i];
    }
    return output;
  }

  /**
   * @brief Encrypts a 64-bit plaintext block using the DES algorithm.
   * @param plaintext The 64-bit plaintext block.
   * @return The 64-bit ciphertext block.
   */
  std::bitset<64> 
  encode(const std::bitset<64>& plaintext) {
    auto data = iPermutation(plaintext);
    std::bitset<32> left(data.to_ullong() >> 32);
    std::bitset<32> right(data.to_ullong());

    for (int round = 0; round < 16; round++) {
      auto newRight = left ^ feistel(right, subkeys[round]);
      left = right;
      right = newRight;
    }

    uint64_t combined = (static_cast<uint64_t>(right.to_ullong()) << 32) | left.to_ullong();
    return fPermutation(std::bitset<64>(combined));
  }

  std::bitset<64>
  decode(const std::bitset<64>& plaintext) {
    auto data = iPermutation(plaintext);
    std::bitset<32> left(data.to_ullong() >> 32);
    std::bitset<32> right(data.to_ullong());

    for (int round = 15; round >= 0; --round) {
      auto newRight = left ^ feistel(right, subkeys[round]);
      left = right;
      right = newRight;
    }

    uint64_t combined = (static_cast<uint64_t>(right.to_ullong()) << 32) | left.to_ullong();
    return fPermutation(std::bitset<64>(combined));
  }

  std::bitset<64>
  stringToBitset64(const std::string& block) {
    uint64_t bits = 0;
    for (int i = 0; i < block.size(); i++) {
      bits |= (uint64_t)(unsigned char)block[i] << ((7 - i) * 8);
    }
    return std::bitset<64>(bits);
  }

  std::string 
  bitset64ToString(const std::bitset<64>& bits) {
    std::string result(8, '\0');
    uint64_t val = bits.to_ullong();

    for (int i = 0; i < 8; i++) {
      result[7 - i] = (val >> (i * 8)) & 0xFF;
    }

    return result;
  }

private:
  std::bitset<64> key; ///< The 64-bit encryption key.
  std::vector<std::bitset<48>> subkeys; ///< The 16 subkeys for each DES round.

  /**
   * @brief Expansion table for expanding 32 bits to 48 bits.
   */
  const int
  EXPANSION_TABLE[48] = {
      32, 1, 2, 3, 4, 5,
      4, 5, 6, 7, 8, 9,
      8, 9,10,11,12,13,
     12,13,14,15,16,17,
     16,17,18,19,20,21,
     20,21,22,23,24,25,
     24,25,26,27,28,29,
     28,29,30,31,32,1
  };

  /**
   * @brief Permutation table P (simplified).
   */
  const int
  P_TABLE[32] = {
      16, 7, 20, 21,29,12,28,17,
       1,15,23,26, 5,18,31,10,
       2, 8,24,14,32,27, 3, 9,
      19,13,30, 6,22,11, 4,25
  };

  /**
   * @brief Simplified S-Box for substitution.
   */
  const int 
  SBOX[4][16] = {
      {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
      {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
      {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
      {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
  };
};