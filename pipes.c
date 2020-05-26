#include "headers/pipes.h"
#include "headers/words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void executePipes (char ***, int);

int
main (void)
{
  char buffer[256];
  char ***pipedArgs;
  int pipes = 0;

  fgets (buffer, sizeof (buffer), stdin);

  pipedArgs = getPipedArgs (buffer, &pipes);

  if (pipedArgs != NULL)
    executePipes (pipedArgs, pipes);
  else
    printf ("No pipes\n");

  exit (0);
}

void
executePipes (char ***pipedArgs, int pipes)
{
  int aux = 0;
  int argIn = 0;
  int newPipe[2];
  int oldPipe[2];
  int pid = 0;

  aux = dup(1);
	 
  argIn++;
  while (*pipedArgs != NULL)
    {
      if (argIn != pipes + 1)
        {
	  if (pipe (newPipe) == -1)
	    {
	      perror ("Error en pipe ");
	      exit (-1);
	    }
	}

      pid = fork ();

      if (pid == -1)
        {
	  perror ("Error en pid ");
	  exit (-1);
	}
      else if (pid == 0)
        {
	  if (argIn != 1)
	    {
	      dup2 (oldPipe[0], 0);
	      close (oldPipe[0]);
	      close (oldPipe[1]);
	    }

	  if (argIn != pipes + 1)
	    {
	      close (newPipe[0]);
	      dup2 (newPipe[1], 1);
	      close (newPipe[1]);
	    }
	  else
	    {
	      close (1);
	      dup (aux);
	      close (aux);
	    }

	  execvp (*(pipedArgs[0]), *pipedArgs);
	  perror ("Error en exec ");
	  exit (-1);
	}
      else
        {
	  if (argIn != 1)
	    {
	      close (oldPipe[0]);
	      close (oldPipe[1]);
	    }

	  if (argIn != pipes + 1)
	    {
	      oldPipe[0] = newPipe[0];
	      oldPipe[1] = newPipe[1];
	    }

	  wait (NULL);
	  argIn++;
	}

      *pipedArgs++;
    }

  close (newPipe[0]);
  close (newPipe[1]);

  return;
}
