#include <iostream>
#include <string>
#include <vector>


namespace entry {

    // create a vector of numbers for message
    std::vector<int> input_message() {
        std::cout << "Please enter message: ";
        std::string plaintext; getline(std::cin, plaintext);
        std::vector<int> numtext;

        for (char elem: plaintext) {
            numtext.push_back(int(elem));    // convert char to int
        }
        return numtext;                      // preserves ascii # for capitals
    }
    // create a vector of numbers from key
    std::vector<int> input_key() {
        std::cout << "Now enter key: ";
        std::string keytext; getline(std::cin, keytext);
        std::vector<int> numkey;

        for (char elem: keytext) {
            int num = int(elem);
            if (97 <= num && num <= 122) {
                numkey.push_back(num-97);
            } else if (65 <= num && num <= 90) {
                numkey.push_back(num-65);
            }
        }
        return numkey;                      // turn key into 0->25
    }
};


namespace encrypt {

    // algorithm to encrypt message
    std::string encrypt() {
        std::vector<int> input = entry::input_message();
        std::vector<int> key = entry::input_key();
        std::string ciphertext;
        int kSz = key.size();

        for (int i=0; i < input.size(); i++) {
            int num = input[i];
            // if lowercase
            if ( 97 <= num && num <= 122) {
                 ciphertext += char(97+( (num - 97) + key[i%kSz] )%26 );
            } 
            // if uppercase
            else if (65 <= num && num <= 90) {
                 ciphertext += char(65+( (num - 65) + key[i%kSz] )%26 );
            } 
            // if other
            else {
                 ciphertext += char(num);
            }
        }
        return ciphertext;
    }
    // algorithm to decrypt message
    std::string decrypt() {
        std::vector<int> input = entry::input_message();
        std::vector<int> key = entry::input_key();
        std::string plaintext;
        int kSz = key.size();

        for (int i=0; i < input.size(); i++) {
            int num = input[i];
            // if lowercase
            if (97 <= num && num <= 122) {
                if ( 0 > (num-97-key[i%kSz])) {         // if key# > ascii#
                    plaintext += char(122+( (num - 96) - key[i%kSz] )%26 );
                } 
                else {
                    plaintext += char(num-key[i%kSz]);  // if ascii# > key#
                }
            }  
            // if uppercase
            else if (65 <= num && num <= 90) {
                if ( 0 > (num-65-key[i%kSz])) {         // if key# > ascii#
                    plaintext += char(90+( (num - 64) - key[i%kSz] )%26 );
                } 
                else {
                    plaintext += char(num-key[i%kSz]);  // if ascii# > key#
                }
            }
            else {
                plaintext += char(num);
            }
            
        }
        return plaintext;
    }
};

int main() {
    std::cout << "Would you like to encrypt or decrypt? Type E/D: ";
    std::string var_in; getline(std::cin, var_in);
    std::string encoded;

    if (var_in == "E") {
        std::cout << "-----ENCRYPTION-----" << std::endl;
        encoded += encrypt::encrypt();
    } 
    else if (var_in == "D") {
        std::cout << "-----DECRYPTION-----" << std::endl;
        encoded +=  encrypt::decrypt();
    } 
    else {
        std::cout << "Invalid entry. Please try again." << std::endl;
    }
    std::cout << encoded << std::endl;
    return 0;
}

