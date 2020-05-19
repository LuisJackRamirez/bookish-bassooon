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
  char def[256];
  char *i;
  char *in;
  char *o;

  i = strtok (buffer, sep);
  o = strtok (NULL, sep);

  trimTrailingSpace (i);
  o = trimLeadingSpace (o);
  trimTrailingSpace (o);

  in = malloc ((sizeof (char) * strlen (i)) + 2);
  in = strcpy (in, i);
  in[strlen (in)] = '\n';
  in[strlen (in) + 1] = '\0';

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
