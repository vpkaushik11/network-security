#include <iostream>
#include <cstring>
#include <openssl/hmac.h>
#include <openssl/md5.h>

int main() {
    // Message and secret key
    const char* message = "Hello, World!";
    const char* secret_key = "MySecretKey";

    // Calculate HMAC-MD5
    unsigned char digest[MD5_DIGEST_LENGTH];
    HMAC_CTX* ctx = HMAC_CTX_new();
    HMAC_Init_ex(ctx, secret_key, strlen(secret_key), EVP_md5(), NULL);
    HMAC_Update(ctx, reinterpret_cast<const unsigned char*>(message), strlen(message));
    HMAC_Final(ctx, digest, NULL);

    // Print the HMAC result
    std::cout << "HMAC-MD5: ";
    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        printf("%02x", digest[i]);
    }
    std::cout << std::endl;

    HMAC_CTX_free(ctx);

    return 0;
}
