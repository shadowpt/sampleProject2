/* 
 * My File System Interface
 * 
 * test-mycopy1
 *
 * Tests my file system interface:
 * - Copying a file to another
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <myfs.h>

int main(int argc, char **argv)
{

   int fd, num;

   // mandatory to init the myfs layer
   my_init_lib();

   // create the empty file 'test.txt' in the root directory
   fd = my_open("/test.txt",O_CREATE);
   if (fd < 0) {
      printf("[test] unable to open file.\n");
      return -1;
   }

   // fill in a buffer with ascii chars
   char data[100];
   for (int i = 0; i < sizeof(data); data[i]='a'+i%10, i++);

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

   // check that the file exists by reopening it without the O_CREATE flag
   fd = my_open("/test.txt",0);
   if (fd < 0) {
      printf("[test] unable to open existing.\n");
      return -1;
   }
          
   // close the file
   if (my_close(fd) < 0) {
      printf("[test] error closing file.\n");
      return -1;
   }
   
   // copy the empty file 'test.txt' in the root directory to 'test2.txt'
   fd = my_copy("/test.txt", "/test2.txt");
   if (fd < 0) {
      printf("[test] unable to copy a file.\n");
      return -1;
   }

   // check that the file exists by reopening it without the O_CREATE flag
   fd = my_open("/test2.txt",0);
   if (fd < 0) {
      printf("[test] unable to open existing.\n");
      return -1;
   }
         
   printf("[test] PASSED.\n");

   return 0;
}


