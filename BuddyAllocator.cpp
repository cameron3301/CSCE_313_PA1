#include "BuddyAllocator.h"
#include <vector>
#include <iostream>
using namespace std;

int f(int b, int s) {
  int i = 0;
  int total = b;

  while (total < s) {
    total = total * 2;
    i++;
  }

  if (total == s) { 
    return i;
  } else {
    //throw validation error
    return -1;  // TO-DO: replace with validation error
  } 
}


BuddyAllocator::BuddyAllocator (int _basic_block_size, int _total_memory_length){
  basic_block_size = _basic_block_size;
  total_memory_size = _total_memory_length;

	memoryStart = new char[_total_memory_length];
  BlockHeader* bhp = (BlockHeader*)(memoryStart);

  bhp->block_size = total_memory_size;
  bhp->free = true;
  bhp->next = NULL;

  int j = f(basic_block_size, total_memory_size);

  FreeList.resize(j+1);

  for (int i = 0; i <= j; i++) {
    FreeList[i].head = NULL;
  }

  FreeList[j].insert(bhp);
}


BuddyAllocator::~BuddyAllocator (){
	// ...
  // ...
  // ...
}


char* BuddyAllocator::alloc(int _length) {
  int rx = _length + sizeof(BlockHeader);
  int i = f(basic_block_size, rx);

  if (FreeList[i].head == NULL) {
    int j = i;
    while (FreeList[j].head == NULL) {
      j++;
      if (j == FreeList.size()) {
        // throw error
      }
    }

    while (j > i) {
      BlockHeader* b = FreeList[j].remove(FreeList[j].head);
      BlockHeader* bb = split(b);
      FreeList[j-1].insert(b);
      FreeList[j-1].insert(bb);
      j--;
    }
  }

  BlockHeader* bhp = FreeList[i].remove(FreeList[i].head);
  bhp->free = false;
  return (char*)(bhp+1);
}


void BuddyAllocator::free(char* _a) {
  BlockHeader* bhp = (BlockHeader*)(_a - sizeof(BlockHeader));
  int i = f(basic_block_size, bhp->block_size);

  while (hasbuddy(bhp)) {
    BlockHeader* b = FreeList[i].remove(getbuddy(bhp));
    bhp = merge(bhp, b);
    i++;
  }

  FreeList[i].insert(bhp);
}


void BuddyAllocator::printlist (){
  cout << "Printing the Freelist in the format \"[index] (block size) : # of blocks\"" << endl;
  for (int i=0; i<FreeList.size(); i++){
    cout << "[" << i <<"] (" << ((1<<i) * basic_block_size) << ") : ";  // block size at index should always be 2^i * bbs
    int count = 0;
    BlockHeader* b = FreeList [i].head;
    // go through the list from head to tail and count
    while (b){
      count ++;
      // block size at index should always be 2^i * bbs
      // checking to make sure that the block is not out of place
      if (b->block_size != (1<<i) * basic_block_size){
        cerr << "ERROR:: Block is in a wrong list" << endl;
        exit (-1);
      }
      b = b->next;
    }
    cout << count << endl;  
  }
}


bool BuddyAllocator::arebuddies(BlockHeader * block1, BlockHeader * block2) {  // TO-DO: Check for mutual parents
// checks whether the two blocks are buddies are not
  return (getbuddy(block1) == block2);
}


bool BuddyAllocator::hasbuddy(BlockHeader* addr) {
  return (!(getbuddy(block1) == NULL));
}


BlockHeader* BuddyAllocator::getbuddy(BlockHeader * addr) {
// given a block address, this function returns the address of its buddy 
  char* chp1 = (char*)addr;
  char* chpBuddy = memoryStart + ((chp1 - memoryStart) ^ addr->block_size);

  BlockHeader* buddy = (BlockHeader*)chpBuddy;

  if ((addr->block_size == buddy->block_size) && (buddy->free == true)) {
    return buddy;
  } else {
    return NULL;
  }
}


BlockHeader* BuddyAllocator::merge(BlockHeader* block1, BlockHeader* block2) {
// this function merges the two blocks returns the beginning address of the merged block
// note that either block1 can be to the left of block2, or the other way around
  if (!arebuddies(block1, block2)) {
    // Throw error
    // blocks must be buddies
  }

  char* chp1 = (char*)block1;
  char* chp2 = (char*)block2;

  // if block1 is to the left of block2
  if ((chp1+(block1->block_size)) == chp2) {
    block1->block_size = (block1->block_size) * 2;
    return block1;
  }

  // if block1 is to the right of block2
  if ((chp2+(block2->block_size)) == chp1) {
    block2->block_size = (block2->block_size) * 2;
    return block2;
  }

  // Throw error
  // something went wrong
}


BlockHeader* BuddyAllocator::split(BlockHeader* block) {
// splits the given block by putting a new header halfway through the block
// also, the original header needs to be corrected
  int size = block->block_size;
  int new_size = size / 2;

  char* chp1 = (char*)block;
  char* chp2 = chp1+new_size;

  BlockHeader* block2 = (BlockHeader*)chp2;

  block->block_size = new_size;

  block2->block_size = new_size;
  block2->free = true;

  return block2;
}