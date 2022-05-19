// myShell0
//////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <unistd.h>

#define error(a) {perror(a); exit(1);};
#define MAXLINE 200
#define MAXARGS 20

#define MAX_CHARS 200

/////////// reading commands:

int read_args(int* argcp, char* args[], int max, int* eofp)
{
   static char cmd[MAXLINE];
   char* cmdp;
   int ret,i;

   *argcp = 0;
   *eofp = 0;
   i=0;
   while ((ret=read(0,cmd+i,1)) == 1) {
      if (cmd[i]=='\n') break;  // correct line
      i++;
      if (i>=MAXLINE) {
         ret=-2;        // line too long
         break;
      }
   }
   switch (ret)
   {
     case 1 : cmd[i+1]='\0';    // correct reading 
              break;
     case 0 : *eofp = 1;        // end of file
              return 0;
              break;
     case -1 : *argcp = -1;     // reading failure
              fprintf(stderr,"Reading failure \n");
              return 0;
              break;
     case -2 : *argcp = -1;     // line too long
              fprintf(stderr,"Line too long -- removed command\n");
              return 0;
              break;
   }
   // Analyzing the line
   cmdp= cmd;
   for (i=0; i<max; i++) {  /* to show every argument */
      if ((args[i]= strtok(cmdp, " \t\n")) == (char*)NULL) break;
      cmdp= NULL;
   }
   if (i >= max) {
      fprintf(stderr,"Too many arguments -- removed command\n");
      return 0;
   }
   *argcp= i;
   return 1;
}

///////////////////////////////////////

int execute(int argc, char *argv[])
{  
   
   for (size_t i = 0; i < argc; i++)
   {
      printf("Value of argument %ld is %s\n",i,argv[i]);
   }

   //Detects the appearance of the '|' character, and saves the position (only one appearance is accepted and saved)
   int hayPipe = -1;
   for (int i = 0; i < argc; i++)
   {
      if (strcmp(argv[i],"|")==0 && hayPipe==-1){
         hayPipe=i;
      }
   }

   if (hayPipe==0 || hayPipe==(argc-1))
   {
      fprintf(stderr,"Incorrect use of pipe: cannot go in first or last position\n");
      return -1;
   }
   else if(hayPipe==-1) // There is no pipe, create child for executing and wait for child to finish
   {
      char Path[MAX_CHARS];
      
      Path[0] = 0;
      strcat(Path,"/home/alejandro/Desktop/Universidad/IOS/LimitedShell/bin/");
      strcat(Path,argv[0]);
      
      printf("Executing %s\n",Path);
      pid_t cpid;
      int pid = fork();
      if (pid==-1){
         fprintf(stderr,"Fatal error forking, exiting\n");
         exit(EXIT_FAILURE);
      }
      else if (pid==0){
         if(execvp(Path,argv)>0)
         {
            exit(EXIT_SUCCESS);
         } else {
            printf("Unknown command %s\n",argv[0]);
            exit(EXIT_FAILURE);
         }
      } else {
         cpid = wait(NULL);
      }
   }
   else // There is a pipe, one child per execution (max of 2 and without arguments allowed)
   {
      // Check that the right side of the pipe has no parameters
      if(hayPipe!=argc-2){
         fprintf(stderr,"Incorrect use of pipe: right side command does not allow any arguments or options\n");
         return -1;
      }
      //TODO Eliminar esto
      printf("There is a pipe in position %d\n",hayPipe);

      // Prepare the path of the commands
      char Path[MAX_CHARS];
      char Path2[MAX_CHARS];
      
      Path[0] = 0;
      Path2[0] = 0;
      strcat(Path,"/home/alejandro/Desktop/Universidad/IOS/LimitedShell/bin/");
      strcat(Path2,"/home/alejandro/Desktop/Universidad/IOS/LimitedShell/bin/");
      strcat(Path,argv[0]);
      strcat(Path2,argv[hayPipe+1]);

      // Prepare the pipes
      int pipes[2];
      pipe(pipes);
      pid_t pid = fork();

      if (pid==-1){
         fprintf(stderr,"Fatal error forking, exiting\n");
         exit(EXIT_FAILURE);
      }
      else if (pid==0) // Child 1
      {
         // Don't fully understand this but lets try
         close(pipes[1]); 
         dup2(pipes[0],0); 
         
         // Execute command
         if(execvp(Path2,&argv[hayPipe+1])>0)
         {
            exit(EXIT_SUCCESS);
         } else {
            printf("Unknown command %s\n",argv[0]);
            exit(EXIT_FAILURE);
         }
      } 
      else // Parent (level 1)
      {
         pid_t wpid;
         int status = 0;
         pid_t pid2 = fork(); // Fork again so that the parent waits and returns to the loop


         if (pid==-1){
            fprintf(stderr,"Fatal error forking, exiting\n");
            exit(EXIT_FAILURE);
         }
         else if (pid==0) // Child 2
         {
            close(pipes[0]);
            dup2(pipes[1],1);

            // I take all the parameters since the first command until '|'
            char *parameters[argc-2];
            memcpy(parameters,argv, sizeof(parameters));

            // Execute command
            if(execvp(Path2,parameters)>0)
            {
               exit(EXIT_SUCCESS);
            } else {
               printf("Unknown command %s\n",argv[0]);
               exit(EXIT_FAILURE);
            }
         } else { // Parent (level2)
            while ((wpid = wait(&status)) > 0); // Wait for all childs
         }

         

      }

   }
   
   

   

}

int main ()
{
   char * Prompt = "myShell0> ";
   int eof= 0;
   int argc;
   char *args[MAXARGS];

   while (1) {
      write(0,Prompt, strlen(Prompt));
      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0) {
         //TODO que al leer exit acabe
         execute(argc, args);
      }
      if (eof) exit(0);
   }
}