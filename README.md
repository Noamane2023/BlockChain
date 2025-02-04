# Blockchain Implementation Using Linked List and Merkle Trees
This project represents a simple implementation of a blockchain using a linked list to store blocks and Merkle trees to manage transactions within each block. The blockchain is secured using SHA-256 hashing with the OpenSSL library.
## Project Structure
The project is structured as follows:
BlockChain 
│ ├── Include 
│  ├── blockchain.h : Contains the structure of the blockchain. 
│  ├── Merkletree.h : Contains the structure of the Merkle tree. 
│  └── Ledger.h : Contains the structure for storing and reading data. 
│ ├── src 
│   ├── Blockchain.c : Implements functions for blockchain creation, mining, deletion, hashing, etc. 
│   ├── MerkleTree.c : Implements functions for creating and deleting Merkle trees for block transactions. 
│   └── LedgerFile.c : Implements functions for writing and reading the blockchain in binary files.

## Features

- **Blockchain**: 
  - Uses a linked list to store blocks.
  - Secure SHA-256 hashing for block integrity.
  - Blockchain creation, mining, and deletion features.
  
- **Merkle Tree**:
  - Each block contains a Merkle tree for transaction data.
  - Merkle trees ensure the integrity of transactions within the block.

- **Ledger**:
  - The blockchain can be written to and read from binary files for persistent storage.

## Prerequisites
Ensure that you have the following software installed:

- **C Compiler** (e.g., GCC or Clang)
- **OpenSSL** library for SHA-256 hashing
