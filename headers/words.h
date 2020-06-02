#ifndef WORDS_H_
#define WORDS_H_

int checkRedirection (char *);
char **getArgs (char *);
char ***getGroupSet (char **, int);
void getInOut (char **, char **, char *, char *);
char ***getPipedArgs (char *, int *);
char **getStrGroup (char *, int);
int numPipes (char *);
char *trimLeadingSpace (char *str);
void trimTrailingSpace (char *str);

int checkEgg (int, char *);
void lovely ();
void painkiller ();
void redemption ();
void redemption2 ();
void tuscany ();

#endif
