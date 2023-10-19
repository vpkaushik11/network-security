#include <iostream>
#include <cstring>

unsigned int custom_hash(const char* data, size_t length) {
    unsigned int hash = 0;

    for (size_t i = 0; i < length; ++i) {
        hash ^= (hash << 5) ^ (hash >> 27); // Basic bitwise rotation
        hash ^= data[i];
    }

    return hash;
}

void custom_hmac(const char* message, const char* key) {
    const size_t block_size = 64; 
    char padded_key[block_size];

    if (strlen(key) > block_size) {
        unsigned int hashed_key = custom_hash(key, strlen(key));
        snprintf(padded_key, block_size + 1, "%08x", hashed_key);
    } else {
        snprintf(padded_key, block_size + 1, "%s", key);
        for (size_t i = strlen(key); i < block_size; ++i) {
            padded_key[i] = '\0';
        }
    }

    for (size_t i = 0; i < block_size; ++i) {
        padded_key[i] ^= message[i];
    }

    unsigned int hmac_result = custom_hash(padded_key, block_size);

    std::cout << "Custom HMAC: " << std::hex << hmac_result << std::dec << std::endl;
}

int main() {
    const char* message = "Hello, World!";
    const char* key = "MySecretKey";

    custom_hmac(message, key);

    return 0;
}
