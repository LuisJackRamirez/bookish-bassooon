#include "headers/words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char **
getArgs (char *buffer)
{
  int i = 0;
  int words = 0;

  char **args;

  //Contar número de palabras para
  //poder obtener la memoria requerida

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

  return args;
}
