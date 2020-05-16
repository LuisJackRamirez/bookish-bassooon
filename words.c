#include "headers/redirection.h"
#include "headers/words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
int
main (void)
{
  int mode = 0;	
  char buffer[256];
  char *input;
  char *output;

  fgets (buffer, sizeof (buffer), stdin);
  scanf ("%i", &mode);

  getInOut (&input, &output, buffer); 
  executeRedirection (input, output, mode);

  return 0;
}
*/

int
checkRedirection (char *buffer)
{
  //Simple función de cadena que revisa 
  //por caracteres específicos.
  for (int i = 0; buffer[i] != '\n'; i++)
    {
      if (buffer[i] == '>')
        {
	  if (buffer[i + 1] == '>')
	    return 2;
	  else
	    return 1;
	}
      else if (buffer[i] == '<')
        return 3;
    }

  return 0;
}

void
getInOut (char **input, char **output, char *buffer)
{
  char *i;
  char *o;

  i = strtok (buffer, ">");
  o = strtok (NULL, ">");

  i[strlen(i) - 1] = '\n';
  o++;
  o = strtok (o, "\n");

  *input = i;
  *output = o;

  return;
}

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

  //Conseguir espacio de memoria con el tamaño requerido
  args = malloc ((words + 1) * sizeof (char *));

  //Preparar los argumentos que recibirá "comando.x".
  args[0] = "./comando.x";
  args[1] = strtok (buffer, " \n");

  for (int j = 2; j <= words; j++)
    args[j] = strtok (NULL, " \n");

  args[words + 1] = NULL;

  return args;
}
