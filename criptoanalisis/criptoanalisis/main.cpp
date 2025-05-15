#include <iostream>
#include <string>
#include "CaesarEncryption.cpp"
using namespace std;

int main()
{
	CaesarEncryption ce;
	string text;
	int shift;

	cout << "Enter the text to encrypt: ";
	getline(cin, text);

	cout << "Enter the shift value: ";
	cin >> shift;

	string encryptedText = ce.EncryptionCaesar(text, shift);

	cout << "Encrypted text: " << encryptedText << endl;

	return 0;
}