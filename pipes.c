#include "headers/pipes.h"
#include "headers/words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void executePipes (char ***);

int
main (void)
{
  char buffer[256];
  char ***pipedArgs;

  fgets (buffer, sizeof (buffer), stdin);

  pipedArgs = getPipedArgs (buffer);
  executePipes (pipedArgs);

  exit (0);
}

void
executePipes (char ***pipedArgs)
{
  int argIn = 0;
  int fd[2] = {0, 0};
  int pid = 0;

  char **index = NULL;

  index = *pipedArgs;

  while (index != NULL)
    {
      if (pipe (fd) == -1)
        {
	  perror ("Error en pipe ");
	  exit (-1);
	}

      pid = fork ();

      if (pid == -1)
        {
	  perror ("Error en pid ");
	  exit (-1);
	}
      if (pid == 0)
        {
	  close (0);
	  dup (argIn);

	  if (*(pipedArgs + 1) != NULL)
	    {
	      close (1);
	      dup (fd[1]);
	    }

	  close (fd[0]);
	  execvp (index[0], index);
	  perror ("Error en exec ");
	  exit (-1);
	}
      else
        {
	  wait (NULL);
	  close (fd[1]);
	  argIn = fd[0];
	  index++;
	}
    }

  return;
}
