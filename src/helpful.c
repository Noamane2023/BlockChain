
// Structure representing a transaction
typedef struct {
    char sender[256];    // Sender's address
    char receiver[256];  // Receiver's address
    int amount;          // Transaction amount
    } T;

// Function to convert an integer to bytes
void intToBytes(int num, unsigned char *output) {
        for (int i = 0; i < sizeof(int); i++) {
            output[i] = (num >> (i * 8)) & 0xFF;
        }
    }
// Function to convert an unsigned long to bytes
void ulongToBytes(unsigned long num, unsigned char *output) {
    for (int i = 0; i < sizeof(unsigned long); i++) {
        output[i] = (num >> (i * 8)) & 0xFF;
    }
}
// Function to convert a string to bytes
void stringToBytes(const char *str, unsigned char *output) {
    size_t length = strlen(str);
    for (size_t i = 0; i < length; i++) {
        output[i] = (unsigned char)str[i];
    }
}
// Function to print a hash
void printHash(unsigned char *hash) {
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");
}
