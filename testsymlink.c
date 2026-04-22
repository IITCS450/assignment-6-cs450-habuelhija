#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

int
memcmp(const void *v1, const void *v2, uint n)
{
  const uchar *s1, *s2;
  s1 = v1;
  s2 = v2;
  while(n-- > 0){
    if(*s1 != *s2)
      return *s1 - *s2;
    s1++, s2++;
  }
  return 0;
}

int
main(int argc, char *argv[])
{
  int fd;
  char buf[16];

  printf(1, "Starting symlink tests...\n");

  if(symlink("target", "link") < 0)
    printf(1, "error: symlink failed\n");

  fd = open("target", O_CREATE | O_RDWR);
  write(fd, "hello", 5);
  close(fd);

  fd = open("link", O_RDONLY);
  if(fd < 0) printf(1, "error: open link failed\n");
  
  read(fd, buf, 5);
  if(memcmp(buf, "hello", 5) == 0)
    printf(1, "Test 1 Passed: Read through link\n");
  else
    printf(1, "Test 1 Failed: Buffer mismatch\n");
  close(fd);

  symlink("a", "b");
  symlink("b", "a");
  if(open("a", O_RDONLY) < 0)
    printf(1, "Test 2 Passed: Cycle detection triggered failure\n");
  else
    printf(1, "Test 2 Failed: System allowed an infinite loop\n");

  exit();
}











