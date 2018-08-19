# Build Instructions:
make
By using the original Makefile (with gcc command included) in the repo, the instruction "make" (under the repo csc415-p2-jzhao11) can build the program and generate the executable file "fc".


# Run Instructions:
./fc
This instruction is also executed under csc415-p2-jzhao11, which runs the executable file "fc".


# What the Code Does:
The program's user interface will appear on the screen (terminal) to ask the user to enter the names (or file path if not in this repo) for input file (source file to copy from) and output file (destination file to copy to). The length of file name should be less than 128 characters.

If the input (source) file does not exist, the program will be aborted. If the output (destination) file does not exist, it will be created. Otherwise (the output file already exists), the program will also be aborted. If a file open error is detected, the error message will be printed out on the terminal.

Then the input file will be copied by repeatedly calling read() and write(). Technically, read() will read from the input file into the buffer, and write() will write from the buffer to the output file. After the file has been copied, both input and output file will be closed by using close(), and a success message will appear on the terminal to notify a normal end of program.


# Annotation of Strace Output of the Program
strace -c ./fc
This strace command will trace and list all the system calls used during the execution of "fc". The strace output is listed as follows.

strace output:
% time     seconds  usecs/call     calls    errors syscall
------ ----------- ----------- --------- --------- ----------------
  0.00    0.000000           0        16           read
  0.00    0.000000           0        16           write
  0.00    0.000000           0         4           open
  0.00    0.000000           0         4           close
  0.00    0.000000           0         1           execve
  0.00    0.000000           0         3         3 access
  0.00    0.000000           0         3           brk
  0.00    0.000000           0         1           munmap
  0.00    0.000000           0         3           mprotect
  0.00    0.000000           0         1         1 _llseek
  0.00    0.000000           0         6           mmap2
  0.00    0.000000           0         4           fstat64
  0.00    0.000000           0         1           set_thread_area
------ ----------- ----------- --------- --------- ----------------
100.00    0.000000                    63         4 total

As shown above, it is the strace output by copying a file with 151 bytes.
Even when we try to run a simple *.c file that has an empty main function (with no open or close or read calls in main), the execution will still open, read, and close something used for the runtime environment. Specifically, there are 2 open() calls, 2 close() calls, and 1 read() call. These can be counted by executing "strace ./fc" (without -c option) and the calling details are available in the output flow.
Since 151 / 13 = 11.6154, the while loop in filecopy.c will call write() for 12 times to write from the buffer to the destination file. And the while loop will call read() for (12 + 1 = 13) times to read from the source file to the buffer, where the 13th read() call has a return value that terminates the loop. Moreover, there are 4 printf() and 2 scanf(), which require 4 write() and 2 read() calls, respectively. In addition, there are also 2 open() and 2 close() calls in main() function.
As a result, there are 
1 + 13 + 2 = 16 read() calls, 
12 + 4 = 16 write() calls, 
2 + 2 = 4 open() calls, 
2 + 2 = 4 close() calls.
