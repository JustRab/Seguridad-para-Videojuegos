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
				result += newPos; // Se cifra el caracter actual
			}
			else if (posActual >= 'A' && posActual <= 'Z') { // Se verifica si es mayuscula
				char newPos = ((posActual - 'A' + shift) % 26) + 'A';
				result += newPos; // Se cifra el caracter actual
			}
			else {
				result += posActual; // Si no esta en el alfabeto, lo dejamos igual
			}
		}
		return result;
	}
};