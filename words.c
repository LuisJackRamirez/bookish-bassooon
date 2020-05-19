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
getInOut (char **input, char **output, char *buffer, char *sep)
{
  int length = 0;
  char def[256];
  char *i = NULL;
  char *in = NULL;
  char *o = NULL;

  i = strtok (buffer, sep);
  o = strtok (NULL, sep);

  trimTrailingSpace (i);
  o = trimLeadingSpace (o);
  trimTrailingSpace (o);

  length = strlen (i);

  in = malloc (sizeof (char) * (length + 2));

  memset (in, 0, sizeof (char) * (length + 2));

  in = strcpy (in, i);
  in[strlen (in)] = '\n';
  //in[strlen (in) + 1] = '\0';

  *output = o;
  *input = in;

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
  args = malloc ((words + 2) * sizeof (char *));

  //Preparar los argumentos que recibirá "comando.x".
  args[0] = "./comando.x";
  args[1] = strtok (buffer, " \n");

  for (int j = 2; j <= words; j++)
    args[j] = strtok (NULL, " \n");

  args[words + 1] = (char *) NULL;

  return args;
}

char ***
getPipedArgs (char *buffer)
{
  char **group;
  char ***pipedArgs;
  int i = 0;
  int pipes = 0;

  pipes = numPipes (buffer);

  if (pipes != 0)
    {
      group = getStrGroup (buffer, pipes);
      pipedArgs = getGroupSet (group, pipes);

      return pipedArgs;
    }
  else
    return NULL;

  free (group);
}

char ***
getGroupSet (char **group, int pipes)
{
  char ***pipedArgs;
  int i = 0;

  pipedArgs = malloc ((pipes + 1) * sizeof (char **));

  while (i <= pipes)
    {
      pipedArgs[i] = getArgs (group[i]);

      i++;
    }

  free (group);
  return pipedArgs;
}

char **
getStrGroup (char *buffer, int pipes)
{
  int i = 0;
  char *in;
  char **group;

  group = malloc ((pipes + 1) * sizeof (char *));

  group[0] = strtok (buffer, "|");
  group[0] = trimLeadingSpace (group[0]);
  trimTrailingSpace (group[0]);
      
  i++;
  while (i <= pipes)
    {
      group[i] = strtok (NULL, "|");
      group[i] = trimLeadingSpace (group[i]);
      trimTrailingSpace (group[i]);

      i++;
    }

  i = 0;
  while (i <= pipes)
    {
      in = malloc ((sizeof (char) * strlen (group[i])) + 3);

      memset (in, 0, sizeof (char) * strlen (group[i]) + 3);

      in = strcpy (in, group[i]);
      in[strlen (in)] = ' ';
      in[strlen (in) + 1] = '\0';

      group[i] = in;

      i++;
    }

  return group;
}

int
numPipes (char *buffer)
{
  int i = 0;	
  int pipes = 0;

  while (buffer[i] != '\0')
    {
      if (buffer[i] == '|')
        pipes++;

      i++;
    }

  return pipes;
}

char *
trimLeadingSpace (char *str)
{
  int i = 0;
  char *in;

  in = str;

  while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
    {
      in++;
      i++;
    }

  str = in;

  return in;
}

void
trimTrailingSpace (char *str)
{
  int index = 0;
  int i = 0;

  index = -1;

  while (str[i] != '\0')
    {
      if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        index = i;

      i++;
    }

  if (index != -1)
    str[index + 1] = '\0';

  return;
}

/*
void
shellPrompts (char *)
{ 
  //hello: "All your base are belong to us\n"
  //exit: Salir	
  
  int numOwnCommands = 0;

  numOwnCommands = 2;

  char* ownCommands[numOwnCommands];
  
  ownCommands[0] = "hello";

  if ()
    {
    }
}*/
