# Blockchain Implementation Using Linked List and Merkle Trees
This project represents a simple implementation of a blockchain using a linked list to store blocks and Merkle trees to manage transactions within each block. The blockchain is secured using SHA-256 hashing with the OpenSSL library.
## Project Structure
The project is structured as follows:

### Explanation of Directories and Files:

- **Include Directory**: This directory contains all the header files (`.h`) which define the structures and function declarations for the blockchain, Merkle tree, and ledger functionalities. These files are used to share information and function prototypes between source files.
  
- **src Directory**: This contains the source files (`.c`) that implement the actual logic of the blockchain, Merkle tree, and ledger. These files define the detailed functions required for creating, managing, and persisting the blockchain and its components.

  - **blockchain.h**: Defines the `Blockchain` structure, which includes the linked list that stores each block in the chain. It also declares functions for creating a new blockchain, mining blocks, and hashing blocks using the SHA-256 algorithm.

  - **Merkletree.h**: Declares the `MerkleTree` structure, which is used for managing transactions in each block. This header file includes function declarations for creating Merkle trees and verifying the integrity of transactions using the tree's root hash.

  - **Ledger.h**: Declares functions for reading and writing the blockchain in binary format, allowing for data persistence. It provides the mechanisms for saving the blockchain to disk and loading it back when the application is restarted.

  - **Blockchain.c**: Implements the blockchain's core functionality. This file includes functions for creating and deleting blocks, mining blocks (adding new blocks to the chain), and hashing blocks to ensure integrity and immutability.

  - **MerkleTree.c**: Implements the functionality for building and manipulating Merkle trees. The tree is used to store and verify the transactions in each block, providing efficient and secure proofs for transactions.

  - **LedgerFile.c**: Implements functions for serializing the blockchain into binary files and reading it back. This ensures that the blockchain's state is preserved even if the program is terminated and later restarted.


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
