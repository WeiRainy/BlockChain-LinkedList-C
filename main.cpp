#include <string>
#include <iostream>
#include "SHA1.hpp"
using namespace std;

typedef bool state;
const bool failed = false;
const bool success = true;

// Block ID
int id = 0;
// Block Structure
struct Block
{
    string user;
    string product;
    string price;
    string pronum; // product number
    int blockID;
    string prevHash;                                                                                                                              // Pre-Hash
    Block *next;                                                                                                                                  // Post-Hash
    Block(string u, string p, string pr, string pd) : user(u), product(p), price(pr), pronum(pd), blockID(id), prevHash(""), next(NULL) { id++; } // Function
};

// Calculate Hash
string hashResult(string input)
{
    SHA1 checksum;
    checksum.update(input);
    string hash = checksum.final().c_str();
    return hash;
}

// create blockchain
Block *createBlockChain()
{
    Block *initBlock = new Block("This is the origin block.", "", "", "");
    initBlock->prevHash = "";
    initBlock->next = NULL;
    return initBlock;
}

// add new block
state addNewBlock(Block *chain)
{
    // Pointer Getting the newest block
    Block *prev = chain;
    while (prev->next != NULL)
    {
        prev = prev->next;
    }

    // input information for the new block
    cout << "Input User: "; string u; getline(cin, u);
    cout << "Input Product: "; string p; getline(cin, p);
    cout << "Input Price: "; string pr; getline(cin, pr);
    cout << "Input Product Number: "; string pd; getline(cin, pd);
    Block *block = new Block(u, p, pr, pd);
    if (!block)
        return failed;

    // calculate the Hash number
    block->prevHash = hashResult(prev->user + prev->product + prev->price + prev->pronum);

    // connect blockchain
    prev->next = block;
    // Print the added block info
    cout << "Added! The block ID is " << block->blockID << ". SHA1-PreviousNode is " << block->prevHash << "." << endl;

    return success;
}
// Addnewblock
state addNewBlock(Block *chain, string u, string p, string pr, string d)
{
    Block *prev = chain;
    while (prev->next != NULL)
    {
        prev = prev->next;
    }

    Block *block = new Block(u, p, pr, d);
    if (!block)
        return failed;

    // calculate hash
    block->prevHash = hashResult(prev->user + prev->product + prev->price + prev->pronum);

    // connect blockchain
    prev->next = block;
    // Print the added block info
    cout << "Added! The block ID is " << block->blockID << ". SHA1-PreviousNode is " << block->prevHash << "." << endl;

    return success;
}

// Print out certain block
void printBlock(Block *block)
{
    cout << "Block " << block->blockID << endl
         << "-------------------------" << endl
         << "User: " << block->user << endl
         << "Product: " << block->product << endl
         << "Price: " << block->price << endl
         << "Product Number: " << block->pronum << endl
         << "Previous Block Hash: " << block->prevHash << endl
         << "-------------------------" << endl
         << endl;
}

// print the whole chain
void printChain(Block *chain)
{
    Block *p = chain->next;
    while (p != NULL)
    {
        printBlock(p);
        p = p->next;
    }
}

// Verify the hash for block
state verifyHash(Block *chain)
{
    int vid;
    if (!chain) return failed;
    Block* p = chain;
    cout << "Input Block ID to verify: "; cin >> vid;
    while (vid >= id-1) {
        cout << "Only 1~" << id-2 << " is accepted. Please input again." << endl;
        cout << "Input Block ID to verify: "; cin >> vid;
    }
    while (p->next)
    {
        if (p->blockID == vid)
            break;
        p = p->next;
    }
    string curHash = hashResult(p->user + p->product + p->price + p->pronum);
    cout << "Hash stored in BlockChain: " << p->next->prevHash << endl;
    cout << "Hash calculated in this block: " << curHash << endl;
    if (curHash == p->next->prevHash)
    {
        cout << "Success! Data not changed." << endl;
    }
    else
    {
        cout << "Ooops! Data changed!" << endl;
    }
}

// print out a menu for user to use
void menu()
{
    cout << "1. Add a block to BlockChain." << endl
         << "2. Print the whole BlockChain." << endl
         << "3. Verify hash value." << endl
         << "0. Quit." << endl;
    cout << "Choose one operation: ";
}

void preset(Block *chain)
{
    addNewBlock(chain, "Chase Kim", "Sony a7r4", "$3,498", "20190212");
    addNewBlock(chain, "Lora Frazer", "Sony ZV-1", "$820", "20190512");
    addNewBlock(chain, "Ian Alvorado", "Cannon R5", "$3,899", "20201101");
    addNewBlock(chain, "Jimmy Tse", "Leica S3", "$19,995", "20210214");
}

int main()
{
    // create Genesis Block
    Block *Chain = createBlockChain();
    // preset
    preset(Chain);
    // auxiliary variable
    bool flag = true;
    int input = 1;
    // Menu
    while (flag)
    {
        menu();
        cin >> input;
        switch (input)
        {
            case 1:
                addNewBlock(Chain);
                break;
            case 2:
                printChain(Chain);
                break;
            case 3:
                verifyHash(Chain);
                break;
            case 0:
                flag = false;
        }
    }
    return 0;
}