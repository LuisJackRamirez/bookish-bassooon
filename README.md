# bookish-bassooon
Shell terminal made in C

TODO:

* ~VERY IMPORTANT: Handle code error. Should go back to the terminal if anything wrong happens (e.g. more)~. This is probably done, more tests are in order.
* Redirection : 
  * Add support for multiple redirection. Should improve the experience, but will be treated as optional.
  * Move input redirection to only one function (check pipes.c), to reduce code.
* Code format :
  * ~Remove commented code WITH CAUTION.~ Done
* Pipes :
  * Small memory issue with pipes.c: Uninitialized memory. Doesn't cause any known issues, no memory leak.
* Shell presentation. All of this is optional.
  * Finish special shell prompts. Extra commands that greet the user. 
    * hello: greets the current user.
    * info: info about the project. Don't think it would be wise to put my real name here, haha. Probably should use GitHub username.
    * ~If the calendar gets summoned, concat "What a day, what a lovely day!" at the end.~ Sadly this will not be implemented yet.
