#include <iostream>
#include <cstdlib>
#include <ctime>

const int p = 23; // Prime number
const int g = 5;  // Primitive root modulo p

// Function to calculate (a^b) % p
int mod_pow(int base, int exponent, int modulus) {
    int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Function to generate a random private key in the range [1, p-1]
int generate_random_private_key() {
    return 1 + (std::rand() % (p - 1));
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int Alice_private_key, Bob_private_key;
    int Alice_public_key, Bob_public_key;
    int shared_secret_Alice, shared_secret_Bob;

    // Alice and Bob generate random private keys
    Alice_private_key = generate_random_private_key();
    Bob_private_key = generate_random_private_key();

    // Calculate public keys
    Alice_public_key = mod_pow(g, Alice_private_key, p);
    Bob_public_key = mod_pow(g, Bob_private_key, p);

    std::cout << "Alice's Private Key: " << Alice_private_key << std::endl;
    std::cout << "Bob's Private Key: " << Bob_private_key << std::endl;

    std::cout << "Alice's Public Key: " << Alice_public_key << std::endl;
    std::cout << "Bob's Public Key: " << Bob_public_key << std::endl;

    // Alice and Bob exchange public keys securely (not shown here)

    // Calculate shared secrets
    shared_secret_Alice = mod_pow(Bob_public_key, Alice_private_key, p);
    shared_secret_Bob = mod_pow(Alice_public_key, Bob_private_key, p);

    // Verify if both parties have the same shared secret
    if (shared_secret_Alice == shared_secret_Bob) {
        std::cout << "Key exchange successful." << std::endl;
        std::cout << "Shared Secret: " << shared_secret_Alice << std::endl;
    } else {
        std::cout << "Key exchange failed. Shared secrets do not match." << std::endl;
    }

    return 0;
}
