#include <stdio.h>
#include <unistd.h>
#include "Ackerman.h"
#include "BuddyAllocator.h"

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

int strToInt(char* str) {
  int c;
  int out = 0;
  int p = 1;

  for (int i = (sizeof(str) / sizeof(str[0]))-1; i >= 0; i--) {
    cout << sizeof(str) / sizeof(str[0]) << endl;
    cout << str << endl;
    c = str[i];

    if (c < 48 || c > 57) {
      // throw error
      // input must be alpha-numeric
    }

    out += (c-48) * p;
    p *= 10;
  }

  return out;
}

int main(int argc, char ** argv) {

  int opt;
  char* bbs;
  char* ml;

  while ((opt = getopt(argc, argv, "b:cs:t")) != -1) {
    switch(opt) {
      case 'b':
        bbs = optarg;
        break;
      case 's':
        ml = optarg;
        break;
      case '?':
        cout << "oops" << endl;
        break;
    }
  }

  int i = 0;
  char* temp = bbs;
  char* temp2 = ml;
  while (i < 20) {
    cout << *temp << " - " << *temp2 << endl;
    i++;
    temp++;
    temp2++;
  }



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
