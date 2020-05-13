#include "headers/prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Se deja esta función main en caso
//de que el programador necesite hacer pruebas

/*
int
main (void)
{
  char buffer[256];
  char str[256];

  getPrompt (str);

  printf ("%s\n", str);

  return 0;
}
*/

void
getPrompt (char *str)
{
  char buffer[256];

  getOutput (buffer, "/usr/bin/whoami");
  strcpy (str, buffer);

  strcat (str, " @ ");

  getOutput (buffer, "/bin/hostname");
  strcat (str, buffer);

  strcat (str, " : ");

  getOutput (buffer, "/bin/pwd");
  strcat (str, buffer);

  strcat (str, " > ");
}

void
getOutput (char *str, char *command)
{
  FILE *fp;
  char buffer[256];
  char *aux;

  fp = popen (command, "r");

  if (fp == NULL)
    {
      perror ("Error en popen");
      exit (-1);
    }

  if (fgets (buffer, sizeof (buffer), fp) != NULL)
    strcpy (str, buffer);

  aux = strchr (str, '\n');
  if (aux != NULL)
    *aux = '\0';

  return;
}
