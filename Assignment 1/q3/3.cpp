#include <iostream>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <openssl/sha.h>
#include <cstring>

RSA* generateRSAKeyPair(int bits) {
    RSA* rsa = RSA_generate_key(bits, RSA_F4, nullptr, nullptr);
    if (!rsa) {
        std::cerr << "Error generating RSA key pair." << std::endl;
        ERR_print_errors_fp(stderr);
    }
    return rsa;
}

bool createDigitalSignature(const char* message, RSA* privateKey, unsigned char* signature, unsigned int* signatureLength) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)message, strlen(message), digest);

    if (RSA_sign(NID_sha256, digest, SHA256_DIGEST_LENGTH, signature, signatureLength, privateKey) != 1) {
        std::cerr << "Error creating digital signature." << std::endl;
        ERR_print_errors_fp(stderr);
        return false;
    }

    return true;
}

bool verifyDigitalSignature(const char* message, unsigned char* signature, unsigned int signatureLength, RSA* publicKey) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256((const unsigned char*)message, strlen(message), digest);

    if (RSA_verify(NID_sha256, digest, SHA256_DIGEST_LENGTH, signature, signatureLength, publicKey) != 1) {
        std::cerr << "Error verifying digital signature." << std::endl;
        ERR_print_errors_fp(stderr);
        return false;
    }

    return true;
}

int main() {
    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    RSA* privateKey = generateRSAKeyPair(2048);
    RSA* publicKey = RSAPublicKey_dup(privateKey);

    const char* message = "Hello, World!";
    unsigned char signature[4096];
    unsigned int signatureLength = 0;

    if (createDigitalSignature(message, privateKey, signature, &signatureLength)) {
        std::cout << "Digital signature created successfully." << signature << std::endl;

        if (verifyDigitalSignature(message, signature, signatureLength, publicKey)) {
            std::cout << "Digital signature is valid." << std::endl;
        } else {
            std::cout << "Digital signature is invalid." << std::endl;
        }
    }

    EVP_cleanup();
    ERR_free_strings();

    return 0;
}
