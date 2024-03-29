# RSA in CPP

## Description

This project is a basic implementation of the RSA encryption algorithm in C++. 

## Installation

To install and run this project, you will need a C++ compiler. Follow these steps:

1. Clone the repository: `git clone https://github.com/Ratoncton/RSA_in_CPP`
2. Navigate to the project directory: `cd RSA_in_CPP`
3. Compile the project: `g++ -o gen key_generation.cpp`
   `g++ -o encryptor encryptor.cpp`
   `g++ -o decryptor decryptor.cpp`
4. Generate and encrypt, decrypt text

## Usage

### Key_generation
Generates the private and public key in a file .priv and .pub
You can put a name to the files, if no name given, it generates with the name key

### Encryptor
Encrypts a text you put after run the program with the .pub file.
You can specify the .pub file if you have more than one with `.\encryptor.exe [name of the .pub file without the extension]`.
After it encrypts the text, it will ask for a name of the file with the encrypted message (extension with .msg) if no name is given the file it will create with the name message

### Decryptor
Decrypts the text of a file .msg with the .priv file.
You can specify some options, these are:
* `.\decryptor.exe -f [.priv file]` Specify the private key with its .priv file.
* `.\decryptor.exe -m [.msg file]` Specify the message file with its .msg file.
* `.\decryptor.exe -fm [.priv file] [.msg file]` Specify the private key file and message file.
* `.\decryptor.exe -h` Helps with the understanding of the commands.

## Contributing

Contributions are welcome. Please fork the repository and create a pull request with your changes.
It can have some issues, so please add to the issues section.

## License

This project is licensed under the MIT License. See the LICENSE file for details.