#ifndef MERKLETREE_H_INCLUDED
#define MERKLETREE_H_INCLUDED
#include <openssl/sha.h>
// Merkle Node structure
typedef struct MerkleNode
{
    unsigned char Hash[SHA256_DIGEST_LENGTH];
    struct MerkleNode *right;
    struct MerkleNode *left;
}MerkleNode;
#endif
