#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int 
main (char argc, char *argv[])
{
  int j = 0;

  char *args[] = {};

  for (j = 1; j < argc; j++)
    args[j - 1] = argv[j];

  args[j - 1] = NULL;

  execvp (argv[1], args);
  
  return 0;
}
