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

//Función que ejecuta la redirección de
//entrada con sobreescritura o concatenación, 
//y la redirección de salida.
void
executeRedirection (char *input, char *output, int mode)
{
  int fileDes = 0;
  int pid = 0;

  //Obtención del conjunto de cadenas de argumentos
  char **inArgs;
  inArgs = getArgs (input);

  //Obtención del descriptor de archivo para el argumento output
  //  1 - Sobreescritura
  //  2 - Concatenación
  if (mode == 1)
    fileDes = open (output, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
  else if (mode == 2)
    fileDes = open (output, O_CREAT | O_WRONLY | O_APPEND, S_IRWXU);

  if (fileDes == -1)
    {
      perror
	("\n\tError en open: executeRedirection (), redirection.c en línea 48/50 :");
      exit (1);
    }

  pid = fork ();

  if (pid == -1)
    {
      perror
	("\n\tError en fork: executeRedirection (), redirection.c en línea 59 :");
      exit (-1);
    }
  else if (pid == 0)
    {
      //Se cierra la salida estándar, es reemplazada
      //por el descriptor de archivo obtenido previamente.

      //dup2 (fileDes, fileno (stdout));  
      close (1);
      dup (fileDes);

      execvp (inArgs[0], inArgs);
      perror
	("\n\tError en execvp: executeRedirection (), redirection.c en línea 72 :");
    }
  else
    {
      close (fileDes);
      wait (NULL);
    }

  //Se libera el espacio de memoria ocupado
  //por el conjunto de cadenas de argumentos
  free (inArgs);

  return;
}

void
executeRedirectionOut (char *input, char *output)
{
  int fileDes = 0;
  int pid = 0;

  //obtención del conjunto de cadenas de argumentos
  char **inArgs;
  inArgs = getArgs (output);

  fileDes = open (input, O_RDONLY, S_IRWXU);

  if (fileDes == -1)
    {
      perror
	("\n\tError en open: executeRedirectionOut (), redirection.c en línea 95 :");
      exit (1);
    }

  pid = fork ();

  if (pid == -1)
    {
      perror
	("\n\tError en fork: executeRedirectionOut (), redirection.c en línea 106 :");
      exit (-1);
    }
  else if (pid == 0)
    {
      //Se cierra la salida estándar, es reemplazada
      //por el descriptor de archivo obtenido previamente.

      //dup2 (fileDes, fileno (stdout));  
      close (0);
      dup (fileDes);

      execvp (inArgs[0], inArgs);
      perror
	("\n\tError en execvp: executeRedirectionOut (), redirection.c en línea 120 :");
    }
  else
    {
      close (fileDes);
      wait (NULL);
    }

  //Se libera el espacio de memoria ocupado
  //por el conjunto de cadenas de argumentos
  free (inArgs);

  return;
}
