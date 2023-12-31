#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>
#include <cmath>
#include <string>
#include <vector>

std::array<long long unsigned int, 2> specificOpenFile(std::string fileName){
    
    std::array<long long unsigned int, 2> key;
    std::string path = "./" + fileName + ".pub";
    std::ifstream file(path);

    if(!file){
        return {1, 1};
    }
    std::string line;
    for(int i = 0; i <= 2;i++){
        file >> key[i];
    }
    
    return key;
}

std::array<long long unsigned int, 2> openFile(){
    std::string path = "."; // The current directory
    std::string extension = ".pub"; // search public key

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

            // Close the file
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

std::vector<int> String_To_Ascii(const std::string& message){
    
    std::vector<int> ascii;
    
    for(char i : message){
        ascii.push_back(static_cast<int>(i));
    }
    return ascii;
}

std::vector<int> encryption(std::vector<int> message, unsigned long long int n, unsigned long long int e){

    std::vector<int> cypher_Message;

    for(int m : message){
        cypher_Message.push_back(modPow(m, e, n));
    }

    return cypher_Message;
}

void toFile(std::vector<int> cMessage, std::string fileName){
    std::ofstream file;
    file.open(fileName + ".msg");

    for(int m : cMessage){
        file << m << "\n";
    }

    file.close();
}

int main(int argc, char* argv[]){

    std::array<long long unsigned int, 2> key;

    if(argc == 1){
        key = openFile();
    }
    else if (argc == 2){
        key = specificOpenFile(argv[1]);
    }
    else if(argc > 2){
        std::cout << "Too many arguments, please enter one public key file name or none\n";
        return 1;
    }
    
    if (key[0] == 1 && key[1] == 1){
        std::cout << "Something has gone wrong, please check if the .pub file is in the folder";
        return 1;
    }

    std::string message = "";
    std::cout << "Write the message you want to encrypt: ";
    std::getline(std::cin, message);
    std::vector<int> mAscii = String_To_Ascii(message);

    std::vector<int> cAscii = encryption(mAscii, key[0], key[1]);

    std::string fileName = "";
    std::cout << "Enter the file name (default: message): ";
    std::getline(std::cin, fileName);
    
    if(fileName == ""){
        fileName = "message";
    }

    toFile(cAscii, fileName);

    return 0;
}
