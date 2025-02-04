#ifndef LEDGER_H
#define LEDGER_H
// structure of a Ledger Entry
typedef struct LedgerEntry{
    int index;
    char prevHash[SHA256_DIGEST_LENGTH];
    T transaction[10];
    MerkleNode *Merkleroot;
    int nonce;
    int nbrTransaction;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    time_t timestamp;
} LedgerEntry;

void writeLedger(Block *head, const char *filename);
Block *readLedger(const char *filename);
#endif
