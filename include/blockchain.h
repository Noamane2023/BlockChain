#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

// Strcture of a Block in the Blockchain
typedef struct Block{
	int index;
	T transaction[10]; // Array of transactions
	int nbrTransaction;
	char Hash[SHA256_DIGEST_LENGTH];
	char Prev_Hash[SHA256_DIGEST_LENGTH];
	time_t timestamp;
	int Nonce; 
	struct Block *next; 
	MerkleNode *Merkleroot; // Merkle Root of the transactions
}Block;

#endif
