# bookish-bassooon
Shell terminal made in C

TODO:

* Replace dup2 with close -> dup. This is vital.
* Redirection : 
  * Add support for multiple redirection. Should improve the experience, but will be treated as optional.
  * Move input redirection to only one function (check pipes.c), to reduce code.
  * ~Redirection and pipes.~ Done as of 28/05/20
* Code format:
  * Add comments (in Spanish) to facilitate comprehension for all .c files.
  * Errors should be standarized. Each line of error should indicate:
    * perror ("Error in [function], [file name] at [line number] : ");
  * Remove commented code WITH CAUTION.
* Pipes :
  * Small memory issue with pipes.c: Uninitialized memory. Doesn't cause any known issues, no memory leak.
* Shell presentation. All of this is optional.
  * Finish special shell prompts. Extra commands that greet the user. 
    * hello: greets the current user.
    * info: info about the project. Don't think it would be wise to put my real name here, haha. Probably should use GitHub username.
    * painkiller: Pre-chorus and chorus of "One Shot at Glory", by Judas Priest.
    * tuscany: Quiet verse after Petrucci's solo of "The Count of Tuscany", by Dream Theater.
    * redemption: "People don't forget. Nothing is forgiven", line by John Marston 
    * redemption2: "We're thieves, in a world that don't want us no more", line by Arthur Morgan.
    * If the calendar gets summoned, concat "What a day, what a lovely day!" at the end.
  * Clear the shell, for a cleaner look.
