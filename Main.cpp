#include <stdio.h>
#include <unistd.h>
#include <string>
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

int main(int argc, char ** argv) {

  int opt;
  int bbs = 0;
  int ml = 0;

  char* b = "";
  char* s = "";

  while ((opt = getopt(argc, argv, "b:cs:t")) != -1) {
    switch(opt) {
      case 'b':
        b = optarg;
        // bbs = strToInt(b);
        break;
      case 's':
        l = optarg;
        // ml = strToInt(l);
        break;
      case '?':
        cout << "oops" << endl;
        break;
    }
  }
  /*
  if (b != "") {

  }*/

  cout << "bbs = " << bbs << endl;
  cout << "ml = " << ml << endl << endl;
  /*
  int i = 0;
  char* temp = bbs;
  char* temp2 = ml;

  string s1(temp);
  string s2(temp2);
  cout << s1 << " - " << s1.length() << endl;
  cout << s2 << " - " << s2.length() << endl << endl;

  cout << temp << " - " << temp2 << endl;
  cout << sizeof(temp) << " / " << sizeof(temp[0]) << endl;
  cout << sizeof(temp2) << " / " << sizeof(temp2[0]) << endl;
  i++;
  */
  


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
