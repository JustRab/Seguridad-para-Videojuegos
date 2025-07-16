#include "Prerequisites.h"
#include "CryptoGenerator.h"
#include "XOREncoder.h"
#include "Caesar.h"
#include "AsciiBinary.h"
#include "Vigenere.h"
#include "DES.h"

/**
 * Reads the entire contents of a file into a string.
 * Opens the file in binary mode for accurate reading.
 * @param filename Path to the file to read.
 * @return Contents of the file as a string.
 * @throws std::runtime_error if the file cannot be opened.
 */
std::string readFromFile(const std::string& filename) {
  std::ifstream file(filename, std::ios::binary);
  if (!file) throw std::runtime_error("Error al abrir el archivo: " + filename);
  std::ostringstream ss;
  ss << file.rdbuf();
  return ss.str();
}

/**
 * Saves a string to a file.
 * Opens the file in binary mode and truncates existing content.
 * @param filename Path to the file to write.
 * @param data String data to write to the file.
 * @throws std::runtime_error if the file cannot be opened for writing.
 */
void saveToFile(const std::string& filename, const std::string& data) {
  std::ofstream file(filename, std::ios::binary | std::ios::trunc);
  if (!file) throw std::runtime_error("Error al guardar el archivo: " + filename);
  file.write(data.data(), static_cast<std::streamsize>(data.size()));
}

/**
 * Converts a text key (up to 8 characters) to a 64-bit bitset.
 * Pads with zeros if the key is shorter than 8 characters.
 * @param input The text key to convert.
 * @return std::bitset<64> representing the key.
 */
std::bitset<64> convertTextKeyToBitset64(const std::string& input) {
  std::bitset<64> bits(0);
  int len = std::min(8, static_cast<int>(input.size()));
  for (int i = 0; i < len; ++i) {
    uint8_t c = static_cast<uint8_t>(input[i]);
    bits <<= 8;
    bits |= std::bitset<64>(c);
  }
  bits <<= (8 - len) * 8;
  return bits;
}

int main() {
  try {
    CryptoGenerator gen;    // Utility for password/key generation and hex conversion
    XOREncoder xorEnc;      // Utility for XOR-based encoding/decoding
    CaesarEncryption caesar;// Utility for Caesar cipher
    AsciiBinary ascii;      // Utility for ASCII-binary conversion

    // Main menu loop
    while (true) {
      std::cout << "\n==== Menu Principal ====" << std::endl;
      std::cout << "1. Cifrado XOR (irrecuperable)\n2. Caesar\n3. XOR con clave\n4. Ascii-Binario\n5. Vigenere\n6. DES\n0. Salir\nOpcion: ";
      int opcion;
      std::cin >> opcion;
      std::cin.ignore();

      if (opcion == 0) break;

      // Input and output file paths
      std::string pathIn, pathOut;
      std::cout << "Ruta del archivo de entrada: ";
      std::getline(std::cin, pathIn);
      std::cout << "Ruta del archivo de salida: ";
      std::getline(std::cin, pathOut);
      std::string data = readFromFile(pathIn);
      std::string result;

      switch (opcion) {
      case 1: {
        // XOR encryption with a random key (key is not saved, so decryption is impossible)
        std::string key = gen.generatePassword(16, true, true, true, false);
        std::string cipher = xorEnc.encode(data, key);
        std::vector<uint8_t> cipherBytes(cipher.begin(), cipher.end());
        std::string cipherHex = gen.toHex(cipherBytes);
        saveToFile(pathOut, cipherHex);
        std::cout << "\n[\u2713] Cifrado XOR irrecuperable completado.\n";
        break;
      }
      case 2: {
        // Caesar cipher encryption and decryption
        int shift;
        std::cout << "Desplazamiento: ";
        std::cin >> shift;
        std::cin.ignore();
        std::string encrypted = caesar.EncryptionCaesar(data, shift);
        saveToFile(pathOut, encrypted);
        std::cout << "[\u2713] Cifrado Caesar completado.\n";
        std::string decrypted = caesar.decode(encrypted, shift);
        std::cout << "Texto descifrado: " << decrypted << "\n";
        break;
      }
      case 3: {
        // XOR encryption with user-provided key (symmetric, reversible)
        std::string key;
        std::cout << "Clave: ";
        std::getline(std::cin, key);
        std::string encrypted = xorEnc.encode(data, key);
        saveToFile(pathOut, encrypted);
        std::cout << "[\u2713] Cifrado XOR con clave completado.\n";
        std::string decrypted = xorEnc.encode(encrypted, key);
        std::cout << "Texto descifrado: " << decrypted << "\n";
        break;
      }
      case 4: {
        // ASCII to binary conversion and back
        std::string binario = ascii.stringToBinary(data);
        saveToFile(pathOut, binario);
        std::cout << "[\u2713] Conversi\u00f3n a binario completada.\n";
        std::string decodificado = ascii.binaryToString(binario);
        std::cout << "Texto decodificado: " << decodificado << "\n";
        break;
      }
      case 5: {
        // Vigenère cipher encryption and decryption
        std::string clave;
        std::cout << "Clave: ";
        std::getline(std::cin, clave);
        Vigenere vig(clave);
        std::string cifrado = vig.encode(data);
        saveToFile(pathOut, cifrado);
        std::cout << "[\u2713] Cifrado Vigen\u00e8re completado.\n";
        std::string descifrado = vig.decode(cifrado);
        std::cout << "Texto descifrado: " << descifrado << "\n";
        break;
      }
      case 6: {
        // DES encryption and decryption (block cipher, 8-byte blocks)
        std::string userKey;
        std::cout << "Clave (hasta 8 caracteres): ";
        std::getline(std::cin, userKey);

        if (userKey.empty()) throw std::runtime_error("La clave no puede estar vac\u00eda.");
        std::bitset<64> keyBits = convertTextKeyToBitset64(userKey);
        DES des(keyBits);

        std::string output;
        // Encrypt in 8-byte blocks, padding with nulls if needed
        for (size_t i = 0; i < data.size(); i += 8) {
          std::string block = data.substr(i, 8);
          while (block.size() < 8) block += '\0'; // Padding
          auto encoded = des.encode(des.stringToBitset64(block));
          output += des.bitset64ToString(encoded);
        }
        saveToFile(pathOut, output);
        std::cout << "[\u2713] Cifrado DES completado.\n";

        // Immediate decryption for verification
        std::string descifrado;
        for (size_t i = 0; i < output.size(); i += 8) {
          std::string block = output.substr(i, 8);
          auto decoded = des.decode(des.stringToBitset64(block));
          descifrado += des.bitset64ToString(decoded);
        }
        std::cout << "Texto descifrado: " << descifrado << "\n";
        break;
      }
      default:
        std::cout << "Opcion no valida.\n";
        break;
      }
    }
  }
  catch (const std::exception& e) {
    std::cerr << "ERROR: " << e.what() << '\n';
  }
  return 0;
}
