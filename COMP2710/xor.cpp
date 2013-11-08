#include <string>
#include <iostream>

int main() {

    std::cout << "Enter a message: ";
    std::string message;
    std::getline(std::cin, message);
    char key [3] = {'@', '$', '*'};
    char r;
    std::string enc, dec;
    for (int i = 0; i < message.length(); i++) {
            for (int j = 0; j < 3; j++) {
                r = message[i] ^ key[j];
                enc += r;
            }

    }

    for (int h = 0; h < enc.length(); h+=3) {
                char d = enc[h] ^ key[1];
                dec +=d;


    }
    std::cout << "Encrypted: " << enc << std::endl;
    std::cout << "Decrypted: " << dec << std::endl;

}
