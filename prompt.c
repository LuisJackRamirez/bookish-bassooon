#include "prompt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
void getPrompt (char *);
void getMachineName (char *);
void getPath (char *);
void getUsername (char *);

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

  getUsername (buffer);
  strcpy (str, buffer);

  strcat (str, " @ ");

  getMachineName (buffer);
  strcat (str, buffer);

  strcat (str, " : ");

  getPath (buffer);
  strcat (str, buffer);

  strcat (str, " > ");
}

void
getMachineName (char *str)
{
  FILE *fp;
  char buffer[256];
  char *aux;

  fp = popen ("/bin/hostname", "r");

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

void
getPath (char *str)
{
  FILE *fp;
  char buffer[256];
  char *aux;

  fp = popen ("/bin/pwd", "r");

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

void
getUsername (char *str)
{
  FILE *fp;
  char buffer[256];
  char *aux;

  fp = popen ("/usr/bin/whoami", "r");

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
