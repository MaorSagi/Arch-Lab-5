# Arch-Lab-5
I/O Redirection and Pipes

Task 1 
In this task, you will make your shell work like a real command interpreter
Use the waitpid call, in order to implement the wait.
Invoke waitpid when you're required, and only when you're required. For example: "cat myshell.c &" will not wait for the cat process to end (cat in this case runs in the background), but "cat myshell.c" will (cat runs in the foreground).

$ ./myshell 
/home/admin/caspl182/lab5/task1$:cat
hello
hello
/home/admin/caspl182/lab5/task1$:     <------------pay attention: here 'Enter' is pressed
/home/admin/caspl182/lab5/task1$:
/home/admin/caspl182/lab5/task1$:quit
$ 

Task 1c
Redirection
Add standard input/output redirection capabilities to your shell (e.g. "cat < in.txt > out.txt"). 

example:
$ ./myshell 
/home/admin/caspl182/lab5/task1$:
/home/admin/caspl182/lab5/task1$:cat < in.txt > out.txt
open failed: No such file or directory
/home/admin/caspl182/lab5/task1$:echo "some input" > in.txt
/home/admin/caspl182/lab5/task1$:cat in.txt
"some input"
/home/admin/caspl182/lab5/task1$:ls -l
total 64
-rwxrwxr-x 1 admin admin    13 Apr 29 05:51 in.txt
-rw------- 1 admin admin  3898 Apr 29 02:01 line_parser.c
-rw------- 1 admin admin  1218 Apr 29 02:01 line_parser.h
-rw-rw-r-- 1 admin admin 10072 Apr 29 05:27 line_parser.o
-rw-r--r-- 1 admin admin   298 Apr 29 05:27 Makefile
-rwxrwxr-x 1 admin admin 19498 Apr 29 05:47 myshell
-rw-rw-r-- 1 admin admin  1968 Apr 29 05:47 myshell.c
-rw-rw-r-- 1 admin admin  8952 Apr 29 05:47 myshell.o
-rwxrwxr-x 1 admin admin     0 Apr 29 05:51 out.txt
/home/admin/caspl182/lab5/task1$:rm out.txt
/home/admin/caspl182/lab5/task1$:ls -l
total 64
-rwxrwxr-x 1 admin admin    13 Apr 29 05:51 in.txt
-rw------- 1 admin admin  3898 Apr 29 02:01 line_parser.c
-rw------- 1 admin admin  1218 Apr 29 02:01 line_parser.h
-rw-rw-r-- 1 admin admin 10072 Apr 29 05:27 line_parser.o
-rw-r--r-- 1 admin admin   298 Apr 29 05:27 Makefile
-rwxrwxr-x 1 admin admin 19498 Apr 29 05:47 myshell
-rw-rw-r-- 1 admin admin  1968 Apr 29 05:47 myshell.c
-rw-rw-r-- 1 admin admin  8952 Apr 29 05:47 myshell.o
/home/admin/caspl182/lab5/task1$:cat < in.txt > out.txt
/home/admin/caspl182/lab5/task1$:ls -l
total 68
-rwxrwxr-x 1 admin admin    13 Apr 29 05:51 in.txt
-rw------- 1 admin admin  3898 Apr 29 02:01 line_parser.c
-rw------- 1 admin admin  1218 Apr 29 02:01 line_parser.h
-rw-rw-r-- 1 admin admin 10072 Apr 29 05:27 line_parser.o
-rw-r--r-- 1 admin admin   298 Apr 29 05:27 Makefile
-rwxrwxr-x 1 admin admin 19498 Apr 29 05:47 myshell
-rw-rw-r-- 1 admin admin  1968 Apr 29 05:47 myshell.c
-rw-rw-r-- 1 admin admin  8952 Apr 29 05:47 myshell.o
-rwxrwxr-x 1 admin admin    13 Apr 29 05:52 out.txt
/home/admin/caspl182/lab5/task1$:cat out.txt
"some input"
/home/admin/caspl182/lab5/task1$:quit
$ 

Task 2: Pipes

Write a short program called mypipeline which creates a pipeline of 2 child processes. 

Task 3

Go back to your shell and add support to a single pipe. Your shell must be able now to run commands like: ls|wc -l which basically counts the number of files/directories under the current working dir, and cat < makefile|wc -l>out1 which basically counts the number of lines you have in the makefile and writes it to a file called out1.
