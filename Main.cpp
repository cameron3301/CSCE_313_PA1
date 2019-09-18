#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <sstream>
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

int strToInt(string str) {
  cout << "str = " << str << endl;
  return 1;
}


// convert a character array of numbers to an integer
long charsToLong(char* c) {
  string s(c);
  cout << "s = " << s << endl;

  stringstream foo(s);

  long out = 0;
  foo >> out;

  return out;
}


int main(int argc, char ** argv) {

  int opt;
  long block_size_long = 0;
  long mem_length_long = 0;

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
  
  if (block_size_chars) {
    block_size_long = charsToLong(block_size_chars);
  }

  if (mem_length_chars) {
    mem_length_long = charsToLong(mem_length_chars);
  }

  cout << "block_size_long = " << block_size_long << endl;
  cout << "mem_length_long = " << mem_length_long << endl << endl;





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
