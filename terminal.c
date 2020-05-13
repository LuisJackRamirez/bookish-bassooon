#include "headers/prompt.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main (void)
{
  int flag = 1;
  int i = 0;
  int pid = 0;
  int exit_status = 0;
  int status = 0;
  int words = 0;

  char **args;
  char buffer[256];
  char prompt[256];

  while (1)
    {
      if (exit_status != 0)
        break;

      pid = fork ();

      if (pid == -1)
	perror ("Error en la llamada a fork ()");
      else if (pid == 0)
	{
	  flag = 1;

	  //Se obtiene el prompt desde
	  //el archivo prompt.c
	  getPrompt (prompt);
	  printf ("%s", prompt);

	  //Recibir los commandos de entrada
	  fgets (buffer, 256, stdin);

	  while (buffer[i] != '\0')
	    {
	      if (buffer[i] == ' ' || buffer[i] == '\n')
		words++;

	      i++;
	    }

	  args = malloc (words * sizeof (char *) + 2);

	  args[0] = "./comando.x";
	  args[1] = strtok (buffer, " \n");

	  for (int j = 2; j <= words; j++)
	    args[j] = strtok (NULL, " \n");

	  args[words + 1] = NULL;

	  if (strcmp (args[1], "exit") == 0)
	    exit (-1);

	  if (flag == 1)
	    execvp (args[0], args);

	  memset (buffer, '\0', sizeof (buffer));
	}
      else
	{
	  pid = wait (&status);
	}

      exit_status = WEXITSTATUS (status);

      printf ("\n");
    }

  return 0;
}
