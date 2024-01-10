## Instruction 

The traditional UNIX tail utility can print out lines from the end of a file. If the number of lines is not given (i.e tail FILE), tail would print out the last 10 lines of its input. We can also specify the number of lines to be printed by calling tail -NUM FILE, for example tail -2 README to print the last 2 lines of the file README.

Here we write a tail program for xv6. If a filename is provided on the command line, then tail should open it, read and print the last NUM lines (no extra blank lines), and then close it. If no filename is provided, tail should read from standard input.

Some usage of tail commands:
- tail README
- tail -2 README
- grep the README | tail