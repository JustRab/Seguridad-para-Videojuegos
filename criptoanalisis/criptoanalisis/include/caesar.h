using namespace std;
#include <iostream>

/**
 * @class CaesarEncryption
 * @brief Implements Caesar cipher encryption, decryption, brute-force attack, and key evaluation.
 *
 * This class provides methods to encrypt and decrypt text using the Caesar cipher,
 * perform brute-force attacks to try all possible shifts, and evaluate the most likely key
 * based on frequency analysis.
 */
class
CaesarEncryption {
public:

  /**
   * @brief Default constructor and destructor.
   */
  CaesarEncryption() = default;
  ~CaesarEncryption() = default;

  /**
   * @brief Encrypts a string using the Caesar cipher with the specified shift.
   * @param text The input string to encrypt.
   * @param shift The number of positions to shift each character.
   * @return The encrypted string.
   *
   * Lowercase and uppercase letters are shifted within their respective ranges.
   * Digits are shifted within '0'-'9'. Non-alphanumeric characters are left unchanged.
   */
  string 
  EncryptionCaesar(const string& text,
                   int shift) {
    string result = ""; // Se inicializa la variable de la respuesta

    for (int i = 0; i < text.size(); i++) {
      char posActual = text[i]; // Se obtiene el caracter actual

      if (posActual >= 'a' && posActual <= 'z') { // Se verifica si es minuscula
        char newPos = ((posActual - 'a' + shift) % 26) + 'a';
        result += newPos;
      }
      else if (posActual >= 'A' && posActual <= 'Z') { // Se verifica si es mayuscula
        char newPos = ((posActual - 'A' + shift) % 26) + 'A';
        result += newPos;
      }
      else if (posActual >= '0' && posActual <= '9') // Se verifica si es un numero
      {
        char newPos = ((posActual - '0' + shift) % 10) + '0';
        result += newPos;
      }
      else {
        result += posActual; // Si no esta en el alfabeto, lo dejamos igual
      }
    }
    return result;
  }

  /**
   * @brief Decrypts a string encrypted with the Caesar cipher using the specified shift.
   * @param text The encrypted string to decrypt.
   * @param shift The number of positions the original text was shifted.
   * @return The decrypted string.
   *
   * This method reverses the encryption by shifting in the opposite direction.
   */
  string 
  decode(const string& text,
         int shift) {
    cout << "===== TEXTO DESCIFRADO =====\n";
    return EncryptionCaesar(text, 26 - (shift % 26)); // Para decodificar, se le resta el desplazamiento
  }

  /**
   * @brief Attempts to decrypt the ciphertext by trying all possible Caesar cipher shifts.
   * @param ciphertext The encrypted string to attack.
   *
   * Prints all possible decrypted strings for shifts from 1 to 25.
   */
  void 
  bruteForceAttack(const string& ciphertext) {
    cout << "===== ATAQUE DE FUERZA BRUTA =====\n";
    cout << "POSIBLES DESCIFRAMIENTOS:\n";

    //Probamos todos los desplazamientos posibles (1 a 25)
    for (int shift = 1; shift < 26; shift++) {
      string decrypted = decode(ciphertext, shift);
      cout << "Desplazamiento " << shift << ": " << decrypted << "\n";
    }
  }

  /**
   * @brief Evaluates the most probable Caesar cipher key using frequency analysis.
   * @param text The encrypted string to analyze.
   * @return The most likely key (shift value) based on the frequency of letters.
   *
   * Assumes that the most frequent letter in the ciphertext corresponds to 'e' in plaintext.
   */
  int 
  evaluatePossibleKey(const string& text) {
    int frequency[26] = { 0 }; // Inicializamos el arreglo de frecuencias

    for (char c : text) {
      if (isalpha(c)) { // Verificamos si es una letra
        c = tolower(c); // Convertimos a minuscula
        frequency[c - 'a']++; // Incrementamos la frecuencia
      }
    }

    int indexMax = 0;
    for (int i = 0; i < 26; i++) {
      if (frequency[i] > frequency[indexMax]) { // Buscamos la letra con mayor frecuencia
        indexMax = i;
      }
    }

    int key = (indexMax - ('e' - 'a') + 26) % 26;
    return key; // Calculamos la clave
  }
};