#ifndef CAESAR_H
#define CAESAR_H

#include <string>
using namespace std;

class CaesarEncryption {
public:
    CaesarEncryption() = default;
    ~CaesarEncryption() = default;

    string EncryptionCaesar(const string& texto, int desplazamiento);

private:
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
};

#endif