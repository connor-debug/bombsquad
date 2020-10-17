#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
  while(1){
  vfork();
  sleep(1);
  }
  return 0;
}
