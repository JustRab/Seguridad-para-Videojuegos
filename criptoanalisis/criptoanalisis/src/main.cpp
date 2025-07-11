#include "Prerequisites.h"
#include "CryptoGenerator.h"
#include "XOREncoder.h"

/**
 * Reads the entire contents of a file into a string.
 * Opens the file in binary mode for accurate reading.
 * @param filename Path to the file to read.
 * @return Contents of the file as a string.
 * @throws std::runtime_error if the file cannot be opened.
 */
std::string 
readFromFile(const std::string& filename) {
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
void 
saveToFile(const std::string& filename, const std::string& data) {
  std::ofstream file(filename, std::ios::binary | std::ios::trunc);
  if (!file) throw std::runtime_error("Error al guardar el archivo: " + filename);
  file.write(data.data(), static_cast<std::streamsize>(data.size()));
}

int 
main() {
  try {
    // Show the current working directory
    std::cout << "Ruta de ejecución actual: " << std::filesystem::current_path() << "\n\n";

    CryptoGenerator gen; // Utility for password/key generation and hex conversion
    XOREncoder xorEnc;   // Utility for XOR-based encoding/decoding

    // --- Input file paths ---
    std::string srcPath, cipherPath;
    std::cout << "Ruta del archivo original a cifrar: ";
    std::getline(std::cin, srcPath);

    std::cout << "Nombre del archivo cifrado a guardar: ";
    std::getline(std::cin, cipherPath);

    // --- Read the original file to encrypt ---
    std::string original = readFromFile(srcPath);

    // --- Generate a random key (16 printable ASCII characters) ---
    std::string key = gen.generatePassword(16, true, true, true, false);

    // --- Encrypt the original text using XOR ---
    std::string cipher = xorEnc.encode(original, key);

    // --- Convert encrypted data to HEX format for safe storage ---
    std::vector<uint8_t> cipherBytes;
    cipherBytes.reserve(cipher.size());
    for (unsigned char c : cipher)
      cipherBytes.push_back(static_cast<uint8_t>(c));

    std::string cipherHex = gen.toHex(cipherBytes);

    // --- Save the HEX-encoded ciphertext to file ---
    saveToFile(cipherPath, cipherHex);

    // --- Internal decryption for verification (does not save or display key/plaintext) ---
    std::string loadedHex = readFromFile(cipherPath);
    std::vector<uint8_t> loadedBytes = gen.fromHex(loadedHex);

    std::string cipherLoaded;
    cipherLoaded.reserve(loadedBytes.size());
    for (uint8_t b : loadedBytes)
      cipherLoaded.push_back(static_cast<char>(b));

    std::string plain = xorEnc.encode(cipherLoaded, key);

    // --- Verify that decrypted text matches the original ---
    std::cout << "\nVerificacion: "
      << (plain == original ? "Exito! El contenido coincide."
        : "Fallo: El contenido no coincide.")
      << '\n';

  }
  catch (const std::exception& e) {
    std::cerr << "ERROR: " << e.what() << '\n';
  }
  return 0;
}
