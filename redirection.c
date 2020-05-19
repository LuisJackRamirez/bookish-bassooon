#include "headers/redirection.h"
#include "headers/words.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

/*
int
main (void)
{
  int mode = 0;

  char buffer[256];
  char *in;
  char *out;

  fgets (buffer, sizeof (buffer), stdin); 
  mode = checkRedirection (buffer);
		
  getInOut (&in, &out, buffer, ">");

  if (in != NULL || out != NULL)
    executeRedirection (in, out, 1);
  else
    printf ("Error en redirección\n");
  
  exit (0);
}
*/

void
executeRedirection (char *input, char *output, int mode)
{
  int fileDes = 0;
  int pid = 0;

  char **inArgs;
  inArgs = getArgs (input);

  if (mode == 1)      
    fileDes = open (output, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
  else if (mode == 2)
    fileDes = open (output, O_CREAT|O_WRONLY|O_APPEND, S_IRWXU);

  if (fileDes == -1)
    {
      perror ("\nError en apertura de archivo\n");
      exit (-1);
    }

  pid = fork ();

  if (pid == -1)
    {
      perror ("\nError en fork ()\n");
      exit (-1);
    }
  else if (pid == 0)
    {
      //dup2 (fileDes, fileno (stdout));  
      close (1);
      dup (fileDes);

      execvp (inArgs[0], inArgs);
      perror ("\nError en exec ()\n");
    }
  else
    {
      close (fileDes);
      wait (NULL);
    }

  free (inArgs);

  return;
}

void
executeRedirectionOut (char *input, char *output)
{
  int fileDes = 0;
  int pid = 0;

  char **inArgs;
  inArgs = getArgs (output);

  fileDes = open (input, O_RDONLY, S_IRWXU);

  if (fileDes == -1)
    {
      perror ("\nError en apertura de archivo\n");
      exit (-1);
    }

  pid = fork ();

  if (pid == -1)
    {
      perror ("\nError en fork ()\n");
      exit (-1);
    }
  else if (pid == 0)
    {
      //dup2 (fileDes, fileno (stdout));  
      close (0);
      dup (fileDes);

      execvp (inArgs[0], inArgs);
      perror ("\nError en exec ()\n");
    }
  else
    {
      close (fileDes);
      wait (NULL);
    }

  free (inArgs);

  return;
}
