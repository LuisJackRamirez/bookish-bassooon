#ifndef WORDS_H_
#define WORDS_H_

int checkRedirection (char *);
char **getArgs (char *);
void getInOut (char **, char **, char *, char *);
int numPipes (char *);
char *trimLeadingSpace (char *str);
void trimTrailingSpace (char *str);

#endif
