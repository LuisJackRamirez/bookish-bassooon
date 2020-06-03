# bookish-bassooon
Shell terminal made in C

TODO:

* VERY IMPORTANT: Handle code error. Should go back to the terminal if anything wrong happens (e.g. more)
* ~~Replace dup2 with close -> dup. This is vital.~~ I think this is done.
* Redirection : 
  * Add support for multiple redirection. Should improve the experience, but will be treated as optional.
  * Move input redirection to only one function (check pipes.c), to reduce code.
* Code format:
  * Add comments (in Spanish) to facilitate comprehension for all .c files.
  * Errors should be standarized. Each line of error should indicate:
    * perror ("Error in [operation], [function], [file name] at [line number] : ");
  * Remove commented code WITH CAUTION.
* Pipes :
  * Small memory issue with pipes.c: Uninitialized memory. Doesn't cause any known issues, no memory leak.
* Shell presentation. All of this is optional.
  * Finish special shell prompts. Extra commands that greet the user. 
    * hello: greets the current user.
    * info: info about the project. Don't think it would be wise to put my real name here, haha. Probably should use GitHub username.
    * If the calendar gets summoned, concat "What a day, what a lovely day!" at the end.
  * ~Clear the shell, for a cleaner look.~ Done, thanks to the shell script.
