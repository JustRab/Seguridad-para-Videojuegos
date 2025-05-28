using namespace std;
#include <iostream>

class CaesarEncryption {
public:
	//Generamos nuestros constructores
	CaesarEncryption() = default;
	~CaesarEncryption() = default;

	string EncryptionCaesar(const string& text, int shift) {
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
			else if (posActual >= '0' && posActual<= '9') // Se verifica si es un numero
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

	string decode(const string& text, int shift) {
		cout << "===== TEXTO DESCIFRADO =====\n";
		return EncryptionCaesar(text, 26 - (shift % 26)); // Para decodificar, se le resta el desplazamiento
	}

	void bruteForceAttack(const string& ciphertext) {
		cout << "===== ATAQUE DE FUERZA BRUTA =====\n";
		cout << "POSIBLES DESCIFRAMIENTOS:\n";

		//Probamos todos los desplazamientos posibles (1 a 25)
		for (int shift = 1; shift < 26; shift++) {
			string decrypted = decode(ciphertext, shift);
			cout << "Desplazamiento " << shift << ": " << decrypted << "\n";
		}
	}

	int evaluatePossibleKey(const string& text) {
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