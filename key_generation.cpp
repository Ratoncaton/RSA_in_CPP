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
long long randomPrimeGenerator(long long limit) {
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

long long GCD(long long a, long long b){
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

long long e_creation(long long int an){
    int _e = 65537;

    int comprovation_e = GCD(_e, an);
    if(comprovation_e == 1){
        return _e;
    }

    for(int e = an - 1; e < an && e > 2; e--){
        int comprovation_e = GCD(e, an);
        if(2 < e < an && comprovation_e == 1){
            _e += e;
            break;
        }
    }

    return _e;
}

long long d_creation(int a, long long an){
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

    if (x1 < 0) x1 += m0;

    return x1;

}

long long RSA_encryption(int message, unsigned long long int an, unsigned long long int e){

    unsigned long long result = 1;
    message = message % an;

    while (e > 0) {
        if (e % 2 == 1) {
            result = (result * message) % an;
        }

        e = e >> 1;
        message = (message * message) % an;
    }

    return result;
}

long long RSA_decryption(long long cypher_Message, unsigned long long int an, unsigned long long int d){

    unsigned long long result = 1;
    cypher_Message = cypher_Message % an;

    while (d > 0) {
        if (d % 2 == 1) {
            result = (result * cypher_Message) % an;
        }

        d = d >> 1;
        cypher_Message = (cypher_Message * cypher_Message) % an;
    }

    return result;
}

int main() {
    
    unsigned long p_primeNumber = randomPrimeGenerator(1000000);
    unsigned long long q_primeNumber = randomPrimeGenerator(1000000);

    unsigned long long n_primeNumber = p_primeNumber * q_primeNumber;
    
    unsigned long long int an = n_primeNumber / GCD(p_primeNumber -1, q_primeNumber -1);

    unsigned long long e_publicKey = e_creation(an);
    
    unsigned long long d_privateKey =  d_creation(e_publicKey, an);

    

    std::cout << "Public key: " << an << " / " << e_publicKey << "\n";
    std::cout << "Private key: " << an << " / " << d_privateKey << "\n";
    std::cout << "Put a number to encrypt: ";
    
    int message; 
    std::cin >> message;

    unsigned long long  encrypted_Message = RSA_encryption(message, an, e_publicKey);
    int decrypted_Message = RSA_decryption(encrypted_Message,an ,d_privateKey);

    std::cout << "\n" << "Encrypted Message: "<< encrypted_Message;
    std::cout << "\n" << "Decrypted Message: " << decrypted_Message;
    
    return 0;
}