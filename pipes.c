#include "headers/pipes.h"
#include "headers/words.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

/*
int
main (void)
{
  char buffer[256];
  char ***pipedArgs;
  int pipes = 0;

  fgets (buffer, sizeof (buffer), stdin);

  pipedArgs = getPipedArgs (buffer, &pipes);

  if (pipedArgs != NULL)
    executePipes (pipedArgs, pipes, NULL, 0);
  else
    printf ("No pipes\n");

  exit (0);
}
*/

//Función que realiza la ejecución de
//los comandos de tubería.
void
executePipes (char ***pipedArgs, int pipes, char *output, int redirMode)
{
  int aux = 0;
  int argIn = 0;
  int in = 0;
  int newPipe[2];
  int oldPipe[2];
  int out = 0;
  int pid = 0;

  //Si la cadena output es nula, significa
  //que no hay redirección I/O.
  if (output != NULL)
    {
      //1 - Redirección de salida con sobreescritura
      //2 - Redirección de salida con concatenación
      //3 - Redirección de entrada
      if (redirMode == 1)
        out = open (output, O_CREAT|O_WRONLY|O_TRUNC, S_IRWXU);
      else if (redirMode == 2)
        out = open (output, O_CREAT|O_WRONLY|O_APPEND, S_IRWXU);
      else if (redirMode == 3)
        {
	  in = open (output, O_RDONLY, S_IRWXU);

	  if (in == -1)
	    {
              perror 
 	        ("\n\tError en open: executePipes (), pipes.c en línea 59 :");
              exit (1);
	    }

	  close (0);
	  dup (in);
	}
      
      if (out == -1)
        {
          perror ("\n\tError en open: executePipes (), pipes.c en línea 54/56 :");
          exit (1);
	}
    }
  else
    {
      //Se guarda el descriptor de archivos de stdout.
      out = dup(1);

      if (out == -1)
        {
          perror ("\n\tError en dup: executePipes (), pipes.c en línea 80 :");
          exit (-1);
	}
    }
	 
  argIn++;
  while (*pipedArgs != NULL)
    {
      if (argIn != pipes + 1)
        {
	  if (pipe (newPipe) == -1)
	    {
              perror ("\n\tError en pipe: executePipes (), pipes.c en línea 95 :");
	      exit (-1);
	    }
	}

      pid = fork ();

      //Error en fork
      if (pid == -1)
        {
          perror ("\n\tError en pid: executePipes (), pipes.c en línea 102 :");
	  exit (-1);
	}

      //Proceso hijo
      else if (pid == 0)
        {
	  //Si el comando actual no es el primero,
	  //se cierra la entrada estánda, se coloca el 
	  //lado de lectura de la tubería antigua, y se 
	  //cierran los duplicados de la tubería.
	  if (argIn != 1)
	    {
	      //dup2 (oldPipe[0], 0);
	      close (0);
	      dup (oldPipe[0]);
	      close (oldPipe[0]);
	      close (oldPipe[1]);
	    }

	  //Si el comando actual no es el último, se cierra
	  //la lectura de la tubería actual, y se coloca la
	  //escritura en la entrada estándar.
	  if (argIn != pipes + 1)
	    {
	      close (newPipe[0]);
	      //dup2 (newPipe[1], 1);
	      close (1);
	      dup (newPipe[1]);
	      close (newPipe[1]);
	    }
	  //De otra forma, se cierra la salida actual, y se
	  //coloca el descriptor de la salida, sea stdout, o
	  //el archivo de salida indicado en 'output'
	  else
	    {
	      close (1);
	      dup (out);
	      close (out);
	    }

	  execvp (*(pipedArgs[0]), *pipedArgs);
          perror ("\n\tError en exec: executePipes (), pipes.c en línea 148 :");
	}

      //Proceso padre
      else
        {
	  //Si el comando actual no es el primero,
	  //cerrar los duplicados
	  if (argIn != 1)
	    {
	      close (oldPipe[0]);
	      close (oldPipe[1]);
	    }

	  //Si el comando actual no es el último,
	  //la tubería actual se convierte en la 
	  //tubería vieja.
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

  //Se cierran los duplicados restantes
  close (newPipe[0]);
  close (newPipe[1]);

  return;
}
