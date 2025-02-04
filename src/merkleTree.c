#include "../include/MerkleTree.h"

// convert transaction data to bytes
void Data(T transaction, unsigned char *output) {
    unsigned char *buffer = output;
    size_t offset = 0;

    // Copy the amount (integer)
    intToBytes(transaction.amount, buffer + offset);
    offset += sizeof(transaction.amount);
    // Copy sender string into the buffer
     stringToBytes(transaction.sender, buffer + offset);
    offset += sizeof(transaction.sender);
    // Copy receiver string into the buffer
     stringToBytes(transaction.receiver, buffer + offset);
    offset += sizeof(transaction.receiver);
}

void ComputeTransactionHash(T transaction,char *Hash) {
    // Calculate the total size of data to be concatenated (excluding block->Hash)
    size_t totalSize = sizeof(transaction.amount) +sizeof(transaction.sender)+ sizeof(transaction.receiver);
    unsigned char *dataBuffer = (unsigned char *)malloc(totalSize);
    memset(dataBuffer, 0, totalSize);  // Zero out the buffer
    // Fill the data buffer with the block's data
    Data(transaction, dataBuffer);
    // Calculate SHA256 hash
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, dataBuffer, totalSize);  // Use totalSize, not sizeof(dataBuffer)
    SHA256_Final(Hash, &sha256);
    // Free allocated memory
    free(dataBuffer);
}
void computeHash(const char *data, size_t len, unsigned char *output) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    SHA256_Update(&ctx, data, len);
    SHA256_Final(output, &ctx);
}


MerkleNode *createLeaf(T transaction){
    MerkleNode *node =(MerkleNode*)malloc(sizeof(MerkleNode));
    ComputeTransactionHash(transaction,node->Hash);

    node->left=node->right=NULL;
    return node;
}
// Combine two nodes to create a parent node
MerkleNode *CombineNode(MerkleNode *left,MerkleNode *right){
    MerkleNode *parent=(MerkleNode*)malloc(sizeof(MerkleNode));
    unsigned char combined[SHA256_DIGEST_LENGTH * 2];
    memcpy(combined, left->Hash, SHA256_DIGEST_LENGTH);
    memcpy(combined + SHA256_DIGEST_LENGTH, right->Hash, SHA256_DIGEST_LENGTH);
    computeHash((char *)combined, sizeof(combined), parent->Hash);
    parent->left = left;
    parent->right = right;
    return parent;
}
// Build the Merkle root from the list of leaves
MerkleNode* buildMerkleRoot(MerkleNode **leaves, int count) {
    while (count > 1) {
        int parentCount = (count + 1) / 2;
        for (int i = 0; i < parentCount; i++) {
            if (i * 2 + 1 < count) {
                leaves[i] = CombineNode(leaves[i * 2], leaves[i * 2 + 1]);
            } else {
                leaves[i] = leaves[i * 2];
            }
        }
        count = parentCount;
    }
    return leaves[0];
}

// Build a Merkle tree from a list of transactions
MerkleNode* buildMerkleTree(T *transaction,int count) {
    MerkleNode *leaves[count];
    for(int i=0;i<count;i++)
    {
        leaves[i]=createLeaf(transaction[i]);
    }
    return buildMerkleRoot(leaves,count);
}
// Validate the Merkle root
int ValidateMerkleRoot(MerkleNode *root,T *transaction,int count) {
    MerkleNode *copy = buildMerkleTree(transaction,count);
        return memcmp(root->Hash, copy->Hash, SHA256_DIGEST_LENGTH) == 0;
}
// Delete the Merkle tree
MerkleNode *DeleteMerkleTree(MerkleNode *root) {
    if(root)
    {
        DeleteMerkleTree(root->left);
        DeleteMerkleTree(root->right);
        MerkleNode *tmp = root;
        free(tmp);
        root=NULL;

    }
    return NULL;
}


