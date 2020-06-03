#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void
abrt_handler (int sig);

int 
main (char argc, char *argv[])
{
  signal (SIGABRT, abrt_handler);

  int returnVal = 0;
  int j = 0;

  char *args[] = {};

  for (j = 1; j < argc; j++)
    args[j - 1] = argv[j];

  args[j - 1] = NULL;

  returnVal = execvp (argv[1], args);
  
  return (returnVal);
}

void
abrt_handler (int sig)
{
  printf ("Couldn't execute command.\n");
}
