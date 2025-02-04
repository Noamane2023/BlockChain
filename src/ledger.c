#include "../include/ledger.h"


// Function to write the blockchain to a file
void writeLedger(Block *head, const char *filename) {
    FILE *file = fopen(filename, "wb"); // binary format
    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    Block *current = head;
    while (current != NULL) {
        // Prepare the ledger entry for the current block
        LedgerEntry entry;
        entry.index = current->index;

        entry.nbrTransaction=current->nbrTransaction;
        memcpy(entry.prevHash, current->Prev_Hash, SHA256_DIGEST_LENGTH);

        for (int i = 0; i < current->nbrTransaction; i++) {
                entry.transaction[i] = current->transaction[i];
        }
        entry.nonce = current->Nonce;
        memcpy(entry.hash, current->Hash, SHA256_DIGEST_LENGTH);
        entry.Merkleroot= current->Merkleroot;
        entry.timestamp = current->timestamp;

        // Write the entry to the binary file
        size_t written = fwrite(&entry, sizeof(LedgerEntry), 1, file);
        if (written != 1) {
            printf("Error writing to file.\n");
            fclose(file);
            return;
        }

        // Move to the next block in the chain
        current = current->next;
    }

    fclose(file);
    printf("Blockchain written to ledger file successfully.\n");
}
// Function to read the blockchain from a file
Block *readLedger(const char *filename) {
    FILE *file = fopen(filename, "rb");  // Open file for reading in binary mode
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }

    LedgerEntry entry;  // Temporary variable to read each ledger entry
    Block *head = NULL, *tail = NULL, *newBlock;

    // Read one ledger entry at a time
    while (fread(&entry, sizeof(LedgerEntry), 1, file) == 1) {  // Ensure complete structures are read


        // Allocate memory for a new block and zero-initialize
        newBlock = (Block *)calloc(1, sizeof(Block));
        if (!newBlock) {
            perror("Error allocating memory");
            fclose(file);
            exit(EXIT_FAILURE);
        }

        // Populate the block using the ledger entry data
        newBlock->index = entry.index;
        newBlock->nbrTransaction=entry.nbrTransaction;
        memcpy(newBlock->Prev_Hash, entry.prevHash, SHA256_DIGEST_LENGTH);
        newBlock->Merkleroot=entry.Merkleroot;
        for (int i = 0; i < newBlock->nbrTransaction; i++) {
                newBlock->transaction[i] = entry.transaction[i];
        }

        memcpy(newBlock->Hash, entry.hash, SHA256_DIGEST_LENGTH);
        newBlock->Nonce = entry.nonce;
        newBlock->timestamp = entry.timestamp;

        newBlock->next = NULL;

        // Link the new block into the linked list
        if (!head) {
            head = newBlock;  // If this is the first block, set it as the head
        } else {
            tail->next = newBlock;  // Link the new block to the previous block
        }

        tail = newBlock;  // Update the tail to the new block
        printf("Block completed\n");
    }

    // Check for errors after the loop
    if (ferror(file)) {
        perror("Error reading file");
    }

    fclose(file);  // Close the file
    return head;   // Return the head of the reconstructed blockchain
}
