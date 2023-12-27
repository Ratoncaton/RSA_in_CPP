#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>

std::array<long long unsigned int, 2> openFile(){
    std::string path = "."; // The current directory
    std::string extension = ".priv"; // search public key

    for (const auto & entry : std::filesystem::directory_iterator(path)) {
        if (entry.path().extension() == extension) {
            // Open the file
            std::ifstream file(entry.path());

            // Check if the file was opened successfully
            if (!file) {
                std::array<long long unsigned int, 2> fail = {1, 1};
                return fail;
            }

            // Read the file
            std::string line;
            std::array<long long unsigned int, 2> key;

            for(int i = 0; i <= 2;i++){
               file >> key[i];
               
            }

            file.close();
            return key;
        }
    }
    std::array<long long unsigned int, 2> fail = {1, 1};
    return fail;

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




std::vector<char> Ascii_To_String(const std::vector<int>& message){
    
    std::vector<char> ascii;
    
    for(int i : message){
        ascii.push_back(static_cast<char>(i));
    }
    return ascii;
}

std::vector<int> decryption(std::vector<int> cMessage, unsigned long long int n, unsigned long long int d){
    std::vector<int> message;
    for(int m : cMessage){
        message.push_back(modPow(m, d, n));
    }

    return message;
}

std::vector<int> splitStringToInts(const std::string& str) {
    std::istringstream iss(str);
    std::vector<int> numbers;
    std::string word;
    while (iss >> word) {
        numbers.push_back(std::stoi(word));
    }
    return numbers;
}

int main(){

    //TODO: make it command line compatible
    std::string cMessage;
    std::array<long long unsigned int, 2> key = openFile();

    if (key[0] == 1 && key[1] == 1){
        std::cout << "Something has gone wrong, please check if the .pub file is in the folder";
        return 1;
    }

    std::cout << "Enter the message you want to decrypt: ";
    std::getline(std::cin, cMessage);

    std::vector<int> cMessageInts = splitStringToInts(cMessage);

    std::vector<int> aMessage = decryption(cMessageInts, key[0], key[1]);

    std::vector<char> oMessage = Ascii_To_String(aMessage);

    

    for(char i : oMessage){
        std::cout << i << "";
    }

    return 0;
}


