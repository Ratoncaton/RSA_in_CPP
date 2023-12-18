#include <iostream>
#include <cmath>
#include <random>

bool bPrimeMillerRobin(long long n, int k = 5) {
    if (n <= 1 || n == 4) return false;
    if (n <= 3) return true;

    long long d = n - 1;
    while (d % 2 == 0) {
        d /= 2;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    for (int i = 0; i < k; ++i) {
        long long a = 2 + std::uniform_int_distribution<long long>(1, n - 1)(gen);

        // Calcular a^d
        long long x = 1;
        while (d > 0) {
            if (d % 2 == 1) {
                x = (x * a) % n;
            }
            a = (a * a) % n;
            d /= 2;
        }

        // Si x no es congruente con 1 (mod n) ni con n-1 (mod n), entonces n no es primo
        if (x != 1 && x != n - 1) {
            return false;
        }
    }

    return true;
}

// Función para generar un número primo aleatorio utilizando Miller-Rabin
unsigned long long randomPrimeGenerator(long long limit) {
    // Generar números aleatorios en el rango [2, limite]
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<long long> dis(2, limit);

    long long randomNumber;
    do {
        // Seleccionar un número aleatorio
        randomNumber = dis(gen);
    } while (!bPrimeMillerRobin(randomNumber)); // Repetir hasta encontrar un primo

    return randomNumber;
}

unsigned long long GCD(long long a, long long b){
    long long quoficient_temp;
    long long residuos_temp;

    while(b > 0){
        quoficient_temp = a/b;
        residuos_temp = a%b;

        a = b;
        b = residuos_temp;


    };

    return a;
}

unsigned long e_creation(long long int an){
    int _e = 65537;

    int comprovation_e = GCD(_e, an);
    if(comprovation_e == 1){
        return _e;
    }

    for(int e = an - 1; e >= 2; e--){
        if(GCD(e, an) == 1){
            return e;
        }
    }

    return 0;
}
//a
unsigned long long d_creation(int a, long long an){
    long long m0 = an, t, q;
    long long x0 = 0, x1 = 1;

    if (an == 1) return 0;

    while (a > 1) {
        q = a / an;
        t = an;

        an = a % an;
        a = t;
        t = x0;

        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0) {
        x1 += m0;
    }

    return x1;

}

unsigned long long modPow(unsigned long long base, unsigned long long exp, unsigned long long modulus) {
    base %= modulus;
    unsigned long long result = 1;
    while (exp > 0) {
        if (exp & 1) result = (result * base) % modulus;
        base = (base * base) % modulus;
        exp >>= 1;
    }
    return result;
}

unsigned long long RSA_encryption(int message, unsigned long long int an, unsigned long long int e){

    return modPow(message, e, an);
}

unsigned long long RSA_decryption(long long cypher_Message, unsigned long long int an, unsigned long long int d){

    return modPow(cypher_Message, d, an);
}

int main() {
    
    unsigned long long p_primeNumber = randomPrimeGenerator(100000);
    unsigned long long q_primeNumber = randomPrimeGenerator(100000);

    if (p_primeNumber > 0 && q_primeNumber > std::numeric_limits<unsigned long long>::max() / p_primeNumber) {
        std::cerr << "Error: Multiplication would overflow.\n";
        return 1;  // Return an error code
    }

    unsigned long long n_primeNumber = p_primeNumber * q_primeNumber;
    
    unsigned long long int an = (p_primeNumber - 1) * (q_primeNumber - 1);

    unsigned long long e_publicKey = e_creation(an);
    
    unsigned long long d_privateKey =  d_creation(e_publicKey, an);

    

    std::cout << "Public key: " << an << " / " << e_publicKey << "\n";
    std::cout << "Private key: " << an << " / " << d_privateKey << "\n";
    std::cout << "Put a number to encrypt: ";
    
    int message; 
    std::cin >> message;

    unsigned long long  encrypted_Message = RSA_encryption(message, n_primeNumber, e_publicKey);
    int decrypted_Message = RSA_decryption(encrypted_Message,n_primeNumber ,d_privateKey);

    std::cout << "\n" << "Encrypted Message: "<< encrypted_Message;
    std::cout << "\n" << "Decrypted Message: " << decrypted_Message;
    
    return 0;
}