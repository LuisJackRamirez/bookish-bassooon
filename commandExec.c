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

  char **args;
  int returnVal = 0;
  int argsNum = argc - 1;
  int j = 0;

  //char *args[] = {};
  args = malloc ((sizeof (char *) * argsNum) + 1);

  for (j = 1; j < argc; j++)
    args[j - 1] = argv[j];

  args[j - 1] = NULL;

  //returnVal = execvp (argv[1], args);
  returnVal = execvp (args[0], args);
  //perror ("\n\tError en exec: commandExec.c, en línea 27 :");a
  abort ();
  
  return 1;
}

void
abrt_handler (int sig)
{
  printf ("Couldn't execute command.\n");
}
