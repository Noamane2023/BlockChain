#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <openssl/sha.h>
#include "src/helpful.c"
#include "src/blockchain.c"
#include "src/ledger.c"

int main()
{
    // Block 1 - Transactions
    T transactions1[2];
    strcpy(transactions1[0].sender, "Alice");
    strcpy(transactions1[0].receiver, "Bob");
    transactions1[0].amount = 100;

    strcpy(transactions1[1].sender, "Noaman");
    strcpy(transactions1[1].receiver, "Imad");
    transactions1[1].amount = 5000;


    Block *genesis_block = insertBlock(NULL, transactions1, 2);

    // Block 2 - Transactions
    T transactions2[2];
    strcpy(transactions2[0].sender, "Alice");
    strcpy(transactions2[0].receiver, "Charlie");
    transactions2[0].amount = 200;

    strcpy(transactions2[1].sender, "Bob");
    strcpy(transactions2[1].receiver, "Eve");
    transactions2[1].amount = 1000;



    genesis_block = insertBlock(genesis_block, transactions2, 2);
    // Block 2 - Transactions
    T transactions3[2];
    strcpy(transactions3[0].sender, "David");
    strcpy(transactions3[0].receiver, "Alice");
    transactions3[0].amount = 700;

    strcpy(transactions3[1].sender, "Eve");
    strcpy(transactions3[1].receiver, "Bob");
    transactions3[1].amount = 2500;

    genesis_block = insertBlock(genesis_block, transactions3, 2);

    //Write and Read from binary files
    writeLedger(genesis_block,"Noaman.bin");
    Block *SavedVersion = readLedger("Noaman.bin");
    displayBlock(SavedVersion);

    return 0;
}
