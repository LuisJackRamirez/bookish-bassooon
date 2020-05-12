#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

void getPuts (char **, char [256]);

int
main (void)
{
  int pid = 0;
  int fd[2] = {0, 0};

  char * ins;
  char *puts[2];
  char buff[256];

  printf ("Comando > ");
  fgets (buff, 256, stdin);

  getPuts (puts, buff);
  getIn ();

  if (pipe (fd) == -1)
    {
      perror ("\nError en pipe\n");
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
      close (0);	//Se cierra STDIN
      dup (fd[0]);	//para colocar la salida
      			//del proceso padre

      //Se cierra STDOUT
      //para mandarlo al archivo
      //y no al monitor

      close (1);				
      open ("file2.dat", O_CREAT|O_RDWR, S_IRWXU);

      wait (NULL);
      close (fd[0]);
      close (fd[1]);
      execlp (puts[1], puts[1], NULL);
      perror ("\nError en exec sort\n");
    }
  else
    {
      close (1);	//Se cierra STDOUT
      dup (fd[1]);	//Para escribir en la tuberia,
      			//y no en el monitor
      close (fd[0]);
      close (fd[1]);	//Para eliminar la tuberia del descriptor
      execlp (puts[0], puts[0], NULL);
      perror ("\nError en exec\n");
    }

  return 0;
}

void
getPuts (char **puts, char buff[256])
{
  puts[0] = strtok (buff, ">");
  puts[1] = strtok (NULL, ">");
  puts[0] = strtok (puts[0], " ");
  puts[1] = strtok (puts[1], "\n");
  puts[1] = strtok (puts[1], " ");
}
