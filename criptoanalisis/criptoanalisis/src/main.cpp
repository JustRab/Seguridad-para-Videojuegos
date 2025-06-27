#include "Prerequisites.h"
#include "CryptoGenerator.h"
int main() {
	// 1) Generar una contraseña de 16 caracteres (mayúsculas, minúsculas, dígitos)Add commentMore actions
	CryptoGenerator cryptoGen;
	cryptoGen.generatePassword(16); // Generate a password of length 16

	// 2) Generar 16 bytes aleatorios genéricos
	auto randomBytes = cryptoGen.generateBytes(16);
	std::cout << "Random Bytes (hex): " << cryptoGen.toHex(randomBytes) << std::endl;

  // 3) Generar uan clave AES de 128 bits
  auto key128 = cryptoGen.generateKey(128);
  std::cout << "AES Key (128 bits, hex): " << cryptoGen.toHex(key128) << std::endl;

  // 4) IV de 16 bytes
  auto iv = cryptoGen.generateIV(16);
  std::cout << "IV (hex): " << cryptoGen.toHex(iv) << std::endl;

  // 5) Salt de 16 bytes
  auto salt = cryptoGen.generateSalt(16);
  std::cout << "Salt (hex): " << cryptoGen.toHex(salt) << std::endl;

	return 0;
}