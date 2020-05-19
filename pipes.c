#include "headers/pipes.h"
#include "headers/words.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main (void)
{
  char buffer[256];
  char **group;
  char ***pipedArgs;

  fgets (buffer, sizeof (buffer), stdin);

  pipedArgs = getPipedArgs (buffer);

  exit (0);
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
      in = malloc ((sizeof (char) * strlen (group[i])) + 2);
      in = strcpy (in, group[i]);
      in[strlen (in)] = ' ';
      in[strlen (in) + 1] = ' ';

      group[i] = in;

      i++;
    }

  return group;
}
