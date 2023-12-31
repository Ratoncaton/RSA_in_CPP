#include <iostream>
#include <fstream>
#include <filesystem>
#include <array>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <cstring>
#include <cstdlib>

std::array<long long unsigned int, 2> specificOpenFile(std::string fileName){
    
    std::array<long long unsigned int, 2> key;
    std::string path = "./" + fileName + ".priv";
    std::ifstream file(path);

    if(!file){
        return {1, 1};
    }

    for(int i = 0; i < 2;i++){
        file >> key[i];
    }
    
    return key;
}

std::vector<long long unsigned int> openMessageFile(std::string fileName){
    std::vector<long long unsigned int> message;
    std::string path = "./" + fileName + ".msg";
    std::ifstream file(path);

    if(!file){
        message.push_back(1);
        return message;
    }
    
    int num;
    while (file >> num) {
        message.push_back(num);
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

            for(int i = 0; i < 2;i++){
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

std::vector<char> Ascii_To_String(const std::vector<long long unsigned int>& message){
    
    std::vector<char> ascii;
    
    for(int i : message){
        ascii.push_back(static_cast<char>(i));
    }
    return ascii;
}

std::vector<long long unsigned int> decryption(std::vector<long long unsigned int> cMessage, unsigned long long int n, unsigned long long int d){
    std::vector<long long unsigned int> message;
    for(int m : cMessage){
        message.push_back(modPow(m, d, n));
    }

    return message;
}

std::vector<long long unsigned int> splitStringToInts(const std::string& str) {
    std::istringstream iss(str);
    std::vector<long long unsigned int> numbers;
    std::string word;
    while (iss >> word) {
        numbers.push_back(std::stoi(word));
    }
    return numbers;
}

int main(int argc, char* argv[]){

    std::array<long long unsigned int, 2> key;
    std::string cMessage = "";
    std::vector<long long unsigned int> vCMessage;
    std::vector<long long unsigned int> cMessageInts;

    if(argc == 1){
        key = openFile();
    }
    else{
        for (int i = 1; i < argc; ++i) {
            if (std::strcmp(argv[i], "-f") == 0 && i + 1 < argc) {

                key = specificOpenFile(argv[i + 1]);
                break;

            } else if (std::strcmp(argv[i], "-m") == 0 && i + 1 < argc) {
                vCMessage = openMessageFile(argv[i + 1]);
            
                if(vCMessage[0] = 1){
                    std::cout << "Something has gone wrong, please check if the .msg file is in the folder";
                    return 1;
                }

                key = openFile();
                break;

            } else if(std::strcmp(argv[i], "-fm") == 0 && i + 1 < argc && i + 2 < argc){
            

                key = specificOpenFile(argv[i + 1]);
                vCMessage = openMessageFile(argv[i + 2]);
                break;

            } else if(std::strcmp(argv[i], "-h") == 0){
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
            }else{
                std::cout << "Invalid option, please use -h for help\n";
                return 1;
            }
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
    } else{
        cMessageInts = vCMessage;
    }

    std::vector<long long unsigned int> aMessage = decryption(cMessageInts, key[0], key[1]);

    std::vector<char> oMessage = Ascii_To_String(aMessage);

    for(char i : oMessage){
        std::cout << i << "";
    }

    return 0;
}