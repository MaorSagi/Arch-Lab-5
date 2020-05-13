#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "line_parser.h"


void execute(cmd_line *line){
    pid_t pid;
    int status,stream1,stream2;
    if((pid = fork()) == -1){
        perror("Error: fork");
        exit(1);
    }
    else if(pid ==0){
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
    execute(parsed);
    free_cmd_lines(parsed);
    }
    
    getcwd(buf,PATH_MAX);
    printf("%s%c ",buf,'$');
    fgets(input,2048,stdin);
}
  

  return 0;

}

