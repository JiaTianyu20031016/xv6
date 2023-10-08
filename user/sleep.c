#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc <= 1)
    fprintf(2, "usage: sleep arg1(int)\n");
  else
    sleep(atoi(argv[1]));
  exit(0);
}
