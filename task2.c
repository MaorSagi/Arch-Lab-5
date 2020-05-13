#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main (int argc, char *argv[]){

  int fd[2];
  int status;
  pid_t pid1,pid2;
  pipe(fd);
  
  const char* process1[] ={"ls","-l",0};
  const char* process2[] ={"tail","-n","2",0};
  
  if((pid1 = fork()) == -1){
   perror("Error: fork");  
   exit(1);
  }
  else if(pid1==0){
      //child1 process
      close(STDOUT_FILENO);
      dup(fd[1]);
      close(fd[1]);
      execvp(process1[0],(char *const*)process1);
      perror("Error: execvp");
      exit(1);
  }
  
  else close(fd[1]);
  
  if((pid2 = fork())==-1){
   perror("Error: fork");  
   exit(1);
  }
  
  else if(pid2==0){
      //child2 process
      close(STDIN_FILENO);
      dup(fd[0]);
      close(fd[0]);
      execvp(process2[0],(char *const*)process2);
      perror("Error: execvp");
      exit(1);
  }
  
  else close(fd[0]);
  
  
  waitpid(pid1, &status, 0);
  waitpid(pid2, &status, 0);
  exit(0);
    
  

  return 0;

}

