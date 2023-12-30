#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>

std::array<long long unsigned int, 2> specificOpenFile(std::string fileName){
    
    std::array<long long unsigned int, 2> key;
    std::string path = "./" + fileName + ".priv";
    std::ifstream file(path);

    if(!file){
        return {1, 1};
    }

    for(int i = 0; i <= 2;i++){
        file >> key[i];
    }
    
    return key;
}

std::vector<int> openMessageFile(std::string fileName){
    std::vector<int> message;
    std::string path = "./" + fileName + ".msg";
    std::ifstream file(path);

    if(!file){
        return {1};
    }

    for(int i = 0; i <= sizeof(file); i++){
        file >> message[i];
    }

    return message;
}

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

int main(int argc, char* argv[]){

    std::array<long long unsigned int, 2> key;
    std::string cMessage = "";
    std::vector<int> vCMessage;
    std::vector<int> cMessageInts = {};

    if(argc == 1){
        key = openFile();
    }
    else if (argc > 2){
        std::string option = argv[1];
        if(option == "-f"){
            key = specificOpenFile(argv[2]);
        }
        else if(option == "-m"){
            vCMessage = openMessageFile(argv[2]);
        }
        else if(option == "-fm"){
            key = specificOpenFile(argv[2]);
            vCMessage = openMessageFile(argv[3]);
        }
        else if(option == "-h"){
            std::cout << "option -h entered\n";
            std::cout << "Usage: decryptor [OPTION] [FILE]\n";
            std::cout << "Decrypts a message using the private key in the .priv file\n";
            std::cout << "REMINDER:\n";
            std::cout << "- The .priv file and .msg file has to be in the same directory as the program\n";
            std::cout << "- It is not necessary to put the extension of the files\n";

            std::cout << "\n" << "Options:\n";
            std::cout << "-f = specify a private key file name (.priv)\n";
            std::cout << "If no option is given, the program will search for a .priv file in the current directory\n";

            std::cout << "\n" << "-m = specify a message file name (.msg)\n";
            std::cout <<"If no option is given, the program will ask for a messsage, every message has to be separated with blank spaces\n";

            std::cout << "\n" << "-fm = specify both a private key file name (.priv) and a message file name (.msg) in this order\n";
            std::cout << "The order is: decryptor -fm [private key file name] [message file name]\n";
            return 0;
       }
        else{
            std::cout << "Invalid option, please use -h for help\n";
            return 1;
        }
    
    }

    if (key[0] == 1 && key[1] == 1){
        std::cout << "Something has gone wrong, please check if the .priv file is in the folder";
        return 1;
    }

    if(vCMessage.size() == 0){
    std::cout << "Enter the message you want to decrypt: ";
    std::getline(std::cin, cMessage);

    cMessageInts = splitStringToInts(cMessage);
    }
    else{
        cMessageInts = vCMessage;
    }

    std::vector<int> aMessage = decryption(cMessageInts, key[0], key[1]);

    std::vector<char> oMessage = Ascii_To_String(aMessage);

    for(char i : oMessage){
        std::cout << i << "";
    }

    return 0;
}