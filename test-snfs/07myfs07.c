/* 
 * My File System Interface
 * 
 * test-myrbig.c
 *
 * Tests the my file system interface:
 * - read the whole file using a buffer bigger than the file itself
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <myfs.h>
#include "tfuncs.h"


#define F_NAME "/f-big.txt"
#define F_SIZE (2*1024+10)


int main(int argc, char **argv)
{
   int fd, num;

   // mandatory to init the myfs layer
   my_init_lib();


   // create the empty file
   fd = my_open(F_NAME,O_CREATE);
   if (fd < 0) {
      printf("[test] unable to open file.\n");
      return -1;
   }

   // fill in a buffer with random binary data
   char data[F_SIZE];
   gen_data_rand_bin(data,F_SIZE);
   
   // write the data to the file
   num = my_write(fd, data, sizeof(data));
   if (num < sizeof(data)) {
      printf("[test] error writing data to file.\n");
      return -1;
   }

   // close the file
   if (my_close(fd) < 0) {
      printf("[test] error closing file.\n");
      return -1;
   }


   /*
    * check the file integrity
    */
 
   
   // reopen file
   fd = my_open(F_NAME,0);
   if (fd < 0) {
      printf("[test] unable to open file.\n");
      return -1;
   }
   
   // read file contents
   char buffer[2*F_SIZE];
   num = my_read(fd,buffer,sizeof(buffer));
   if (num != F_SIZE) {
      printf("[test] file size differ from the expected.\n");
      return -1;
   }
   
   // compare contents
   if (memcmp(data,buffer,F_SIZE) != 0) {
      printf("[test] file contents differ from data.\n");
      return -1;
   }
   
   // close the file
   if (my_close(fd) < 0) {
      printf("[test] error closing file.\n");
      return -1;
   }

   printf("[test] test passed.\n");
   return 0;
}
