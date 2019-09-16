/****************************************************
* Name: vigenere.cpp                                *
* Description: C++ script to encrypt and decrypt    *
*     messages                                      *
* Author: Angel A. Valdenegro                       *
* TODO: Make algorithm more efficient in rewrite    *
*****************************************************/ 

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
            numtext.push_back(int(elem));       // convert char to int
        }
        return numtext; 
    }
    // create a vector of numbers from key
    std::vector<int> input_key() {
        std::cout << "Now enter key: ";
        std::string keytext; getline(std::cin, keytext);
        
        // only preserve alphabet position in numkey
        std::vector<int> numkey;
        for (char elem: keytext) {
            int num = int(elem);
            if ('a' <= num && num <= 'z') {
                numkey.push_back(num - 'a');
            } else if ('A' <= num && num <= 'Z') {
                numkey.push_back(num - 'A');
            }
        }
        return numkey;                      // turn key into 0->25
    }
};


namespace xcrypt {
    // algorithm to encrypt message
    std::string encrypt() {
        std::vector<int> input = entry::input_message();
        std::vector<int> key = entry::input_key();
        int kSz = key.size();

        std::string ciphertext;
        for (int i=0; i < input.size(); i++) {
            int num = input[i];
            // if lowercase
            if ( 'a' <= num && num <= 'z') {
                 ciphertext += char('a'+ ((num - 'a') + key[i % kSz]) % 26);
            } 
            // if uppercase
            else if ('A' <= num && num <= 'Z') {
                 ciphertext += char('A'+ ((num - 'A') + key[i % kSz]) % 26);
            } 
            // if other preserve whatever it was
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

        for (int i = 0; i < input.size(); i++) {
            // assign num as current int in message 
            int num = input[i];

            // if num is lowercase
            if ('a' <= num && num <= 'z') {
                if ( 0 > (num - 'a' - key[i % kSz])) {         // if key# > ascii#
                    plaintext += char('z'+ ((num - 'a' + 1) - key[i%kSz]) % 26);
                } 
                else {
                    plaintext += char(num - key[i % kSz]);  // if ascii# > key#
                }
            }  
            // if num is uppercase
            else if ('A' <= num && num <= 'Z') {
                if ( 0 > (num - 'A' - key[i % kSz])) {         // if key# > ascii#
                    plaintext += char('Z'+ ((num - 'A' + 1) - key[i % kSz]) % 26);
                } 
                else {
                    plaintext += char(num - key[i % kSz]);  // if ascii# > key#
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

    if (var_in == "E" || var_in == "e") {
        std::cout << "-----ENCRYPTION-----" << std::endl;
        encoded += xcrypt::encrypt();
    } 
    else if (var_in == "D" || var_in == "d") {
        std::cout << "-----DECRYPTION-----" << std::endl;
        encoded +=  xcrypt::decrypt();
    } 
    else {
        std::cout << "Invalid entry. Please try again." << std::endl;
        main();
    }
    std::cout << encoded << std::endl;
    return 0;
}
