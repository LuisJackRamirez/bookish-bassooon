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


//Funcion que obtiene el prompt del shell.
//El prompt tiene soporte para 256 caracteres.
void
getPrompt (char *str)
{
  char buffer[256];

  //Usuario del equipo
  getOutput (buffer, "/usr/bin/whoami");
  strcpy (str, buffer);

  //Caracter A
  strcat (str, " @ ");

  //Nombre del equipo
  getOutput (buffer, "/bin/hostname");
  strcat (str, buffer);

  //Caracter B
  strcat (str, " : ");

  //Directorio de trabajo actual
  getOutput (buffer, "/bin/pwd");
  strcat (str, buffer);

  //Caracter C
  strcat (str, " > ");
}

//Función que obtiene el resultado
//del comando pasado como argumento
void
getOutput (char *str, char *command)
{
  FILE *fp;
  char buffer[256];
  char *aux;

  //popen () invoca al shell mediante una tubería.
  //indicando el comando y el tipo de comunicación.
  fp = popen (command, "r");

  if (fp == NULL)
    {
      perror ("\n\tError en popen: getOutput (), prompt.c en línea 56 :");
      exit (-1);
    }

  if (fgets (buffer, sizeof (buffer), fp) != NULL)
    strcpy (str, buffer);

  //Eliminación del salto de línea concatenado
  //por la función fgets
  aux = strchr (str, '\n');
  if (aux != NULL)
    *aux = '\0';

  return;
}
