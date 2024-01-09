**Shell Implementation Readme**

This implementation focuses on building a UNIX shell. The goal is to understand and implement components of a shell, gaining familiarity with UNIX library calls and the UNIX process model.

The shell aims to handle complex command pipelines similar to: `$ cat words.txt | grep cat | sed s/cat/dog/ > doggerel.txt`, enabling users to manipulate text data effectively.

### Part 1 - Command Execution
Implemented basic command execution by referencing the `exec(3)` function. Users can run single commands, such as `ls` or `grep cat words.txt`, within the shell.

### Part 2 - I/O Redirection
Extended the shell to handle input and output redirection using the `<` and `>` characters. Implemented functionalities to redirect command output to files, enabling commands like `ls > a.txt` or `sort -r < a.txt`.

### Part 3 - Pipes
Implemented piping functionality (`|`) to direct the output of one command as input to another. Utilized system calls like `fork(2)`, `pipe(2)`, `dup2(2)`, `close(2)`, and `wait(2)` to establish communication between commands, enabling full command pipelines like `cat words.txt | grep cat | sed s/cat/dog/ > doggerel.txt`.

### Part 4 - Summary Questions
1. **Successive Command Execution:** Implemented a series of commands (`cd`, `find`, `ls`) regardless of previous command success. Another method considered is using `&&` to execute subsequent commands only upon previous command success.

2. **Subshell Implementation:** For subshells, implemented using `(` and `)`, allowing complex command execution like `echo "-$(sed 's/cat/lion/g' a.txt)" > hello.txt`.

### Conclusion
This shell implementation progressively handles command execution, I/O redirection, piping, and complex command sequences, aiming to simulate basic shell functionalities. Each part of the assignment enhances understanding and application of UNIX system calls and process management within a shell environment.