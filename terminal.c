#include "headers/prompt.h"
#include "headers/pipes.h"
#include "headers/redirection.h"
#include "headers/words.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main (void)
{
  int exit_status = 0;
  int i = 0;
  int pid = 0;
  int pipes = 0;
  int status = 0;
  int redirectionStatus = 0;

  char buffer[256];
  char unalteredBuffer[256];
  char prompt[256];

  char *input;
  char *output;
  char **args;
  char ***pipedArgs;

  while (1)
    {
      if (exit_status < 0 || exit_status > 128)
	break;

      //Se obtiene el prompt desde
      //el archivo prompt.c.
      pid = fork ();
      if (pid == -1)
	{
	  perror ("Error en fork (): main (), terminal.c en línea 38 :");
	  exit (-1);
	}
      else if (pid == 0)
	{
          getPrompt (prompt);
	  printf ("%s", prompt);
	  exit (0);
	}
      else
        {
          wait (&status);
	}

      pid = fork ();
      if (pid == -1)
	{
	  perror ("Error en fork (): main (), terminal.c en línea 55 :");
	  exit (-1);
	}
      else if (pid == 0)
	{
	  //Recibir la linea de comandos de entrada.
	  fgets (buffer, 256, stdin);
	  strcpy (unalteredBuffer, buffer);

	  //shellPrompts (unalteredBuffer);

	  //Descubrir si hay redirección > >> < en la entrada.
	  //  0. No hay redirección.
	  //  1. >      Redirección de salida, sobreescritura.
	  //  2. >>     Redirección de salida, concatenación.
	  //  3. <      Redirección de entrada.
	  redirectionStatus = checkRedirection (buffer);

	  if (checkEgg (redirectionStatus, unalteredBuffer) == 1)
	    exit (0);
	  else
	    {
	      switch (redirectionStatus)
		{
		case 0:
		  pipes = numPipes (buffer);

		  if (pipes == 0)
		    {
		      //Separar argumentos, preparar para llevar a execvp ()
		      args = getArgs (buffer);

		      if (strcmp (args[1], "exit") == 0)
		        _exit (-1);

		      execvp (args[0], args);
	 	      perror ("\n\tError en exec: main (), terminal.c en línea 93 :");
		    }
		  else
		    {
		      pipes = 0;
		      pipedArgs = getPipedArgs (buffer, &pipes);
		      executePipes (pipedArgs, pipes, NULL, 0);
		      exit (0);
		    }

		  break;

		case 1:
		  getInOut (&input, &output, buffer, ">");
		  pipes = numPipes (input);

		  if (pipes == 0)
		    {
		      if (input != NULL || output != NULL)
			executeRedirection (input, output, 1);
		      else
			printf ("\n\tError en redirección: main (), terminal.c en línea 113 :: Bad input/output parsing\n");
		    }
		  else
		    {
		      pipes = 0;
		      pipedArgs = getPipedArgs (input, &pipes);
		      executePipes (pipedArgs, pipes, output, 1);
		    }

		  exit (0);
		  break;

		case 2:
		  getInOut (&input, &output, buffer, ">>");
		  pipes = numPipes (input);

		  if (pipes == 0)
		    {
		      if (input != NULL || output != NULL)
			executeRedirection (input, output, 2);
		      else
			printf ("\n\tError en redirección: main (), terminal.c en línea 134 :: Bad input/output parsing\n");
		    }
		  else
		    {
		      pipes = 0;
		      pipedArgs = getPipedArgs (input, &pipes);
		      executePipes (pipedArgs, pipes, output, 2);
		    }

		  exit (0);
		  break;

		case 3:
		  getInOut (&output, &input, buffer, "<");
		  pipes = numPipes (output);

		  if (pipes == 0)
		    {
		      if (input != NULL || output != NULL)
			executeRedirectionOut (input, output);
		      else
			printf ("\n\tError en redirección: main (), terminal.c en línea 155 :: Bad input/output parsing\n");
		    }
		  else
		    {
		      pipes = 0;
		      pipedArgs = getPipedArgs (output, &pipes);
		      executePipes (pipedArgs, pipes, input, 3);
		    }

		  exit (0);
		  break;
		}
	    }
	}
      else
	wait (&status);

      if (WIFEXITED (status))
	exit_status = WEXITSTATUS (status);

      printf ("\n");
    }

  return 0;
}
