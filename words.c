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

//Función que revisa por algún comando
//de redirección en el buffer de entrada
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

//Función que realiza el procesamiento
//de la cadena de entrada y la de salida,
//separando con el caracter solicitad
void
getInOut (char **input, char **output, char *buffer, char *sep)
{
  int length = 0;
  char def[256];
  char *i = NULL;
  char *in = NULL;
  char *o = NULL;

  //Obtener las cadenas
  i = strtok (buffer, sep);
  o = strtok (NULL, sep);

  //Eliminar espacios innecesarios
  trimTrailingSpace (i);
  o = trimLeadingSpace (o);
  trimTrailingSpace (o);

  length = strlen (i);

  //Conseguir el espacio para 
  //la cadena de entrada final
  in = malloc (sizeof (char) * (length + 2));
  memset (in, 0, sizeof (char) * (length + 2));
  in = strcpy (in, i);
  in[strlen (in)] = '\n';
  //in[strlen (in) + 1] = '\0';

  *output = o;
  *input = in;

  return;
}

//Función para obtener un conjunto de
//cadenas, cada una representan un comando 
//y sus parámetros, si es que los tiene.
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

//Función que procesa el buffer de entrada
//para obtener el conjunto de arreglos de
//cadenas que representan los varios comandos con
//sus argumentos al ejecutar una función con tuberías.
char ***
getPipedArgs (char *buffer, int *pipes)
{
  char **group;
  char ***pipedArgs;
  int i = 0;

  *pipes = numPipes (buffer);

  if (*pipes != 0)
    {
      //Arreglo de cadenas
      group = getStrGroup (buffer, *pipes);
      //Conjunto de arreglos
      pipedArgs = getGroupSet (group, *pipes);

      return pipedArgs;
    }
  else
    return NULL;

  free (group);
}

//Función para obtener el conjunto 
//de arreglos de cadenas
char ***
getGroupSet (char **group, int pipes)
{
  char ***pipedArgs;
  int i = 0;

  //Obtener memoria para el conjunto
  pipedArgs = malloc ((pipes + 1) * sizeof (char **) + 1);
  memset (pipedArgs, 0, (pipes + 1) * sizeof (char **) + 1);

  while (i <= pipes)
    {
      pipedArgs[i] = getArgs (group[i]);
      i++;
    }

  free (group);
  return pipedArgs;
}

//Función para obtener los arreglos
//de cadenas de comandos y argumentos
char **
getStrGroup (char *buffer, int pipes)
{
  int i = 0;
  char *in;
  char **group;

  //Obtener memoria para el arreglo
  group = malloc ((pipes + 1) * sizeof (char *));
  memset (group, 0, sizeof (char *) * (pipes + 1));

  //Procesamiento del buffer
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

  //Obtención de memoria y procesamiento final
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

//Función que cuenta el número de
//operadores de tubería '|' en el
//buffer de entrada.
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

//Función que elimina espacios en blanco
//que preceden a una cadena
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

//Función que elimina espacios en blanco
//que preceden a una cadena
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

//Función que revisa comandos especiales,
//como 'hello', 'exit'
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




//Easter eggs
int
checkEgg (int redirectionStatus, char *unalteredBuffer)
{
  if (redirectionStatus != 0)
    return 0;

  if (strcmp (unalteredBuffer, "painkiller\n") == 0)
    {
      painkiller ();
      return 1;
    }
  else if (strcmp (unalteredBuffer, "tuscany\n") == 0)
    {
      tuscany ();
      return 1;
    }
  else if (strcmp (unalteredBuffer, "redemption\n") == 0)
    {
      redemption ();
      return 1;
    }
  else if (strcmp (unalteredBuffer, "redemption2\n") == 0)
    {
      redemption2 ();    
      return 1;
    }

  return 0;
}

void
lovely (void)
{
  printf ("\n\tWhat a day, what a lovely day!\n");
}

void
painkiller (void)
{
  printf ("\n\tThis day will last forever");
  printf ("\n\tDeep in the hearts of men");
  printf ("\n\tCourage and victory");
  printf ("\n\tRemember, remember!");

  printf ("\n\n\tOne shot at glory");
  printf ("\n\tDriving hard and seeing red");
  printf ("\n\tDestiny calls me");
  printf ("\n\tOne night of fire, one shot at glory\n");
}

void
redemption (void)
{
  printf ("\n\tPeople don't forget. Nothing gets forgiven\n");
}

void
redemption2 (void)
{
  printf ("\n\tWe're thieves, in a world that don't want us no more\n");
}

void
tuscany (void)
{
  printf ("\n\tCould this be the end? Is this the way I die?");
  printf ("\n\tSitting here alone"); 
  printf ("\n\tNo one by my side");

  printf ("\n\n\tI don't understand"); 
  printf ("\n\tI don't feel that I deserve this");
  printf ("\n\tWhat did I do wrong? I just don't understand\n");
}
