#include "merkleTree.c"
#include "../include/blockchain.h"




// Function to create a new block
Block *createBlock(T *transaction, Block *prevBlock,int count) {
    int index = 0;
    char prev_Hash[SHA256_DIGEST_LENGTH] = {0};
    if (prevBlock) {
        index = prevBlock->index + 1;
        memcpy(prev_Hash, prevBlock->Hash, SHA256_DIGEST_LENGTH);
    }

    Block *newBlock = (Block*)calloc(1, sizeof(Block));
    newBlock->index = index;
    newBlock->nbrTransaction=count;
    memcpy(newBlock->Prev_Hash, prev_Hash, SHA256_DIGEST_LENGTH);
    for (int i = 0; i < count; i++) {
        newBlock->transaction[i] = transaction[i];
    }
    MerkleNode *root = buildMerkleTree(transaction,count);
    newBlock->Merkleroot=root;
    newBlock->Nonce = 0;
    newBlock->timestamp = time(NULL);
    return newBlock;
}

// Function to concatenate the data of a block
void concatenateData(Block *block, unsigned char *output,int Nonce) {
    unsigned char *buffer = output;
    size_t offset = 0;
    // Copy the previous hash (SHA256_DIGEST_LENGTH bytes)
    stringToBytes(block->Prev_Hash, buffer + offset);
    offset += SHA256_DIGEST_LENGTH;
    // Copy the Merkle root
    stringToBytes(block->Merkleroot, buffer + offset);
    offset += SHA256_DIGEST_LENGTH;
    // Copy the index (integer)
    intToBytes(block->index, buffer + offset);
    offset += sizeof(block->index);
     // Copy the nonce (integer)
    intToBytes(Nonce, buffer + offset);
    offset += sizeof(block->Nonce);

}
// Function to calculate the hash of a block
void calculateBlockHash(Block *block,char *Hash,int Nonce) {
    // Calculate the total size of data to be concatenated
    size_t totalSize = SHA256_DIGEST_LENGTH*2 + sizeof(block->index) +sizeof(block->Nonce);
    unsigned char *dataBuffer = (unsigned char *)malloc(totalSize);
    memset(dataBuffer, 0, totalSize);
    concatenateData(block, dataBuffer,Nonce);

    // Calculate SHA256 hash
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, dataBuffer, totalSize);
    SHA256_Final(Hash, &sha256);
    // Free allocated memory
    free(dataBuffer);
}
// Function to mine a block
void  mineBlock(Block *block ){
    int Nonce=0;
    unsigned char hash[SHA256_DIGEST_LENGTH];
    calculateBlockHash(block,hash,Nonce);
    while (hash[0] != 0x00 || hash[1] != 0x00) {
        Nonce++;
        calculateBlockHash(block, hash, Nonce);

    }
    // Copy the hash and nonce into the block
    memcpy(block->Hash, hash, SHA256_DIGEST_LENGTH);
    block->Nonce = Nonce;
}
// Function to insert a block into the blockchain
Block *insertBlock(Block *head, T *transaction,int count) {
    if (!head) {
            Block *genesisBlock=createBlock(transaction, NULL,count);
            mineBlock(genesisBlock);

        return genesisBlock;
    }

    Block *tmp1 = head;
    while (tmp1->next) {
        tmp1 = tmp1->next;
    }

    Block *tmp = createBlock(transaction,tmp1,count);
    mineBlock(tmp);
    tmp1->next = tmp;
    return head;
}
// Function to delete a block from the blockchain
Block *deleteBlock(Block *head, int index) {
    if (!head) {
        return NULL;
    }

    if (head->index == index) {
        Block *tmp = head;
        head = head->next;
        if (head){
            char prev_Hash[SHA256_DIGEST_LENGTH] = {0};
            memcpy(head->Prev_Hash,prev_Hash, SHA256_DIGEST_LENGTH);
            mineBlock(head);
            Block *current = head;
            Block *tmp1=head->next;
            while(tmp1)
            {
                memcpy(tmp1->Prev_Hash,current->Hash, SHA256_DIGEST_LENGTH);
                mineBlock(tmp1);
                current=tmp1;
                tmp1=tmp1->next;
            }

        }
        tmp->Merkleroot=DeleteMerkleTree(tmp->Merkleroot);
        free(tmp);
        return head;
    }

    Block *current = head;

    while (current->next && current->next->index != index) {
        current = current->next;
    }

    if (current->next) {
        Block *tmp = current->next;
        if (!tmp->next) {
            tmp->Merkleroot=DeleteMerkleTree(tmp->Merkleroot);
            free(tmp);
            current->next = NULL;
        } else {

            current->next = tmp->next;
            tmp->Merkleroot=DeleteMerkleTree(tmp->Merkleroot);
            free(tmp);
            Block *tmp1 = current->next;
            memcpy(tmp1->Prev_Hash, current->Hash, SHA256_DIGEST_LENGTH);
            mineBlock(tmp1);

            while (tmp1->next) {
                Block *prev = tmp1;
                tmp1 = tmp1->next;
                memcpy(tmp1->Prev_Hash, prev->Hash, SHA256_DIGEST_LENGTH);
                mineBlock(tmp1);
            }
        }
    }else{
        printf("No block with index : %d ",index);
    }

    return head;
}
// Function to display a block
void displayBlock(Block *block) {
    if (!block) {
        printf("Block is NULL.\n");
        return;
    }
        while(block)
    {
        printf("=====================================\n");
        printf("Block Index: %d\n", block->index);
        printf("Block Nonce: %d\n", block->Nonce);
        printf("Timestamp: %s", ctime(&(block->timestamp)));
        printf("Transactions :\n");
        for(int i=0;i<block->nbrTransaction;i++)
        {
        printf("Transaction %d :\n",i+1);
        printf("  Sender: %s\n", block->transaction[i].sender);
        printf("  Receiver: %s\n", block->transaction[i].receiver);
        printf("  Amount: %d\n", block->transaction[i].amount);
        }


        printf("Merkle Root Hash: ");
        printHash(block->Merkleroot->Hash);
        printf("\n");
        printf("Hash: ");
        printHash(block->Hash);
        printf("\n");
        if (block->index == 0) {
                printf("Previous Hash: None (Genesis Block)\n");
            } else {
                printf("Previous Hash: ");
                printHash(block->Prev_Hash);
                printf("\n");
            }
        block = block->next;
    }

}
// Function to validate the blockchain
// Function to validate the blockchain and display the block that was changed
int validateBlockChain(Block *block) {
    if (!block) {
        printf("The block is empty\n");
        return 0;
    }

    Block *curr = block;
    unsigned char calculatedHash[SHA256_DIGEST_LENGTH];

    while (curr) {
        // Validate Merkle root
        if (ValidateMerkleRoot(curr->Merkleroot, curr->transaction, curr->nbrTransaction)) {
            // Calculate block hash and compare it
            calculateBlockHash(curr, calculatedHash, curr->Nonce);
            if (memcmp(calculatedHash, curr->Hash, SHA256_DIGEST_LENGTH) != 0) {
                printf("Block %d has an invalid hash.\n", curr->index);
                return 0;
            }

            // Compare previous block's hash
            if (curr->next && memcmp(curr->Hash, curr->next->Prev_Hash, SHA256_DIGEST_LENGTH) != 0) {
                printf("Block %d has an invalid link to the next block.\n", curr->index);
                return 0;
            }
        } else {
            printf("Block %d has an invalid Merkle root.\n", curr->index);
            return 0;
        }

        curr = curr->next;
    }

    // If all blocks are valid
    printf("all blocks are valid");
    return 1;
}
