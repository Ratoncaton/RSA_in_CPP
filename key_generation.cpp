#include <iostream>
#include <cmath>
#include <random>
#include <gmpxx.h>
#include <cstdlib>
#include <ctime>

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

    bool finnish = false;
    int e;

    while(finnish == false){
        /*std::srand(static_cast<unsigned int>(std::time(0)));

        e = 2 + std::rand() % (an - 2 + 1);
        int comprovation_e = GCD(e, an); */

        int list_possible_e[an];

        //agregar lista para comprobar e = 1

        if(2 < e < an && comprovation_e == 1){

            finnish = true;
        }
    }

    return e;
}


int main() {
    
    long long p_primeNumber = randomPrimeGenerator(1000000);
    long long q_primeNumber = randomPrimeGenerator(1000000);

    long long n_primeNumber = p_primeNumber * q_primeNumber;
    
    long long int an = GCD(p_primeNumber -1, q_primeNumber -1);

    long long e_publicKey = e_creation(an);

    std::cout << e_publicKey << "\n";
    std::cout << an << "\n"; 
    
    return 0;
}