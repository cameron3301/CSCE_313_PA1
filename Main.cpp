#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "Ackerman.h"
#include "BuddyAllocator.h"
using namespace std;

void easytest(BuddyAllocator* ba){
  // be creative here
  // know what to expect after every allocation/deallocation cycle

  // here are a few examples
  ba->printlist();
  // allocating a byte
  char * mem = ba->alloc (1);
  // now print again, how should the list look now
  ba->printlist ();

  ba->free (mem); // give back the memory you just allocated
  ba->printlist(); // shouldn't the list now look like as in the beginning

}



// convert a character array of numbers to an integer
int charsToInt(char* c) {
  string s(c);
  cout << "s = " << s << endl;

  stringstream foo(s);

  int out = 0;
  foo >> out;

  return out;
}


// returns true if input is a power of 2
bool powerOfTwo(int val) {
  int i = 2;

  // increment `i` to the next power of 2
  while (i < val) {
    i = i * 2;
  }

  return (i == val);
}


// ...
void validateInputArguments(int block_size, int mem_len) {

  cout << "11111" << endl;

  // Test 1: is `block_size` a power of 2
  if (!powerOfTwo(block_size)) {
    // throw error
    throw invalid_argument("Input received for Basic Block Size is not a power of 2");
  }

  cout << "22222" << endl;

  // Test 2: is `mem_len` a power of 2
  if (!powerOfTwo(mem_len)) {
    // throw error
    throw invalid_argument("Input received for Memory Length is not a power of 2");
  }

  cout << "33333" << endl;

  // Test 3: is `mem_len` greater than `block_size`
  if (mem_len <= block_size) {
    // throw error
    throw invalid_argument("Value of Basic Block Size may not be greater than that of Memory Length");
  }

  cout << "44444" << endl;

  // Test 4: is `mem_len` greater than 128 * 1024 * 1024
  if (mem_len < (128 * 1024 * 1024)) {
    // throw error
    throw invalid_argument("Value of Memory Length must be greater than or equal to 128 * 1024 * 1024 bytes");
  }

  cout << "55555" << endl;
}


int main(int argc, char ** argv) {

  int opt;

  char* block_size_chars = NULL;
  char* mem_length_chars = NULL;

  while ((opt = getopt(argc, argv, "b:cs:t")) != -1) {
    switch(opt)
    {
      case 'b':
        block_size_chars = optarg;
        break;
      case 's':
        mem_length_chars = optarg;
        break;
      case '?':
        // ...
        break;
    }
  }
  
  int basic_block_size;
  int memory_length;

  if (block_size_chars) {
    basic_block_size = charsToInt(block_size_chars);
  } else {
    basic_block_size = 128;
  }

  if (mem_length_chars) {
    memory_length = charsToInt(mem_length_chars);
  } else {
    memory_length = 128 * 1024 * 1024;
  }

  cout << "AAAAAA" << endl;

  validateInputArguments(basic_block_size, memory_length);





  cout << "basic_block_size = " << basic_block_size << endl;
  cout << "memory_length = " << memory_length << endl << endl;





  /* 
  int basic_block_size = 128, memory_length = 128 * 1024 * 1024;

  // create memory manager
  BuddyAllocator * allocator = new BuddyAllocator(basic_block_size, memory_length);

  // the following won't print anything until you start using FreeList and replace the "new" with your own implementation
  easytest (allocator);

  
  // stress-test the memory manager, do this only after you are done with small test cases
  Ackerman* am = new Ackerman ();
  am->test(allocator); // this is the full-fledged test. 
  
  // destroy memory manager
  delete allocator;
  */
}
