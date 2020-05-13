#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "line_parser.h"
void execute(cmd_line *line);
void execute_pipes(cmd_line *line);
void child(cmd_line *line){
    int stream1,stream2;
      if(line->input_redirect != NULL || line->output_redirect != NULL){
        if(line->input_redirect != NULL){
          if((stream1 = open(line->input_redirect,O_RDONLY,0))==-1){
          perror("Error: open");
          exit(1);
        }
        dup2(stream1,0);
        }
        if(line->output_redirect != NULL){
            if((stream2 = open(line->output_redirect,O_RDWR | O_CREAT ,0644))==-1){
            perror("Error: open");
            exit(1);
            }
        dup2(stream2,1);
        }
        
    
    }
    int ret = execvp(line->arguments[0],line->arguments);
     if(ret ==-1){
        perror("Error: execvp");
        exit(1);
    }
    if(line->input_redirect != NULL || line->output_redirect != NULL){
        if(line->input_redirect != NULL){
          close(stream1);
        }
        if(line->output_redirect != NULL){
          close(stream2);
        }
    }
}
void execute_pipes(cmd_line *line){
  int fd[2],status;
  pid_t pid1,pid2;
  pipe(fd);

  if((pid1 = fork()) == -1){
   perror("Error: fork");  
   exit(1);
  }
  else if(pid1==0){
      //child1 process
      close(STDOUT_FILENO);
      dup(fd[1]);
      close(fd[1]);
      //execvp(line->arguments[0],line->arguments);
      child(line);
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
      //execvp((line->next)->arguments[0],(line->next)->arguments);
      child(line->next);
  }
  
  else close(fd[0]);
  
  
  waitpid(pid1, &status, 0);
  waitpid(pid2, &status, 0);
  
}

void execute(cmd_line *line){
    pid_t pid;
    int status;
    if((pid = fork()) == -1){
        perror("Error: fork");
        exit(1);
    }
    else if(pid ==0){
        child(line);
   
    }
    else if(line->blocking == 1){
            waitpid(pid,&status,0);
        }   
}

int main (int argc, char *argv[]){
  char input[2048];
  char buf[PATH_MAX];
  getcwd(buf,PATH_MAX);
  printf("%s%c ",buf,'$');
  fgets(input,2048,stdin);
  
  while(strcmp(input,"quit\n")!=0){
    if(input[0]=='\n'||input[0]=='\t'||input[0]==' '){
      strncpy(input,input+1,strlen(input)-1);
       getcwd(buf,PATH_MAX);
    printf("%s%c ",buf,'$');
    fgets(input,2048,stdin);
      continue;
    }
    if(strcmp(input,"")!=0){
        cmd_line* parsed;
        parsed=parse_cmd_lines(input);
        if(parsed->next!=NULL){
            execute_pipes(parsed);
        }
        else{
        execute(parsed);
        }
        free_cmd_lines(parsed);
    }
    
    getcwd(buf,PATH_MAX);
    printf("%s%c ",buf,'$');
    fgets(input,2048,stdin);
}
  

  return 0;

}

