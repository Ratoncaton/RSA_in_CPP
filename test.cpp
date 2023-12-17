#include <iostream>
#include <cmath>

// Función para calcular la exponenciación modular
unsigned long long mod_pow(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    unsigned long long result = 1;
    base = base % modulus;

    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }

        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }

    return result;
}

// Función para cifrar un mensaje utilizando la clave pública RSA
unsigned long long encrypt(unsigned long long message, unsigned long long e, unsigned long long n) {
    // Calcular C ≡ M^e (mod n)
    return mod_pow(message, e, n);
}

// Función para descifrar un mensaje utilizando la clave privada RSA
unsigned long long decrypt(unsigned long long ciphertext, unsigned long long d, unsigned long long n) {
    // Calcular M ≡ C^d (mod n)
    return mod_pow(ciphertext, d, n);
}

int main() {
    // Clave pública del destinatario (e, n)
    unsigned long long e = 65537;
    unsigned long long n = 66459316853;

    // Clave privada del destinatario (d, n)
    unsigned long long d = 67395263412175262;

    // Mensaje a cifrar
    unsigned long long message = 12;

    // Cifrar el mensaje
    unsigned long long ciphertext = encrypt(message, e, n);

    // Imprimir el mensaje cifrado
    std::cout << "Encrypted Message: " << ciphertext << std::endl;

    // Descifrar el mensaje
    unsigned long long decryptedMessage = decrypt(ciphertext, d, n);

    // Imprimir el mensaje descifrado
    std::cout << "Decrypted Message: " << decryptedMessage << std::endl;

    return 0;
}

