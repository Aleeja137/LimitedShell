// myShell0
//////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

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
      printf("Value of argument %d is %s\n",i,argv[i]);
   }
     

   char Path[MAX_CHARS];
   
   Path[0] = 0;
   strcat(Path,"/home/alejandro/Desktop/Universidad/IOS/LimitedShell/bin/");
   strcat(Path,argv[0]);
   
   printf("Executing %s\n",Path);
   int pid = fork();
   if (pid==0){
      if(execvp(Path,argv)>0)
      {
         exit(EXIT_SUCCESS);
      } else {
         printf("Unknown command %s\n",argv[0]);
      }
   } else {
      int child_status;
      waitpid(pid,&child_status,0);
   }

   // if (strcmp(argv[0],"ls")==0){

   //    int pid = fork();
   //    if (pid==0){
   //       execvp("/home/alejandro/Desktop/Universidad/IOS/LimitedShell/bin/ls",argv);
   //       exit(EXIT_SUCCESS);
   //    } else {
   //       int child_status;
   //       waitpid(pid,&child_status,0);
   //    }

   // } else if (strcmp(argv[0],"cat")==0)
   // {
      
   //    int pid = fork();
   //    if (pid==0){
   //       execvp("/home/alejandro/Desktop/Universidad/IOS/LimitedShell/bin/cat",argv);
   //       exit(EXIT_SUCCESS);
   //    } else {
   //       int child_status;
   //       waitpid(pid,&child_status,0);
   //    }
      

   // } else if (strcmp(argv[0],"link")==0)
   // {
   //    int pid = fork();
   //    if (pid==0){
   //       execvp("/home/alejandro/Desktop/Universidad/IOS/LimitedShell/bin/link",argv);
   //       exit(EXIT_SUCCESS);
   //    } else {
   //       int child_status;
   //       waitpid(pid,&child_status,0);
   //    }
      

   // } else if (strcmp(argv[0],"cp")==0)
   // {
   //    int pid = fork();
   //    if (pid==0){
   //       execvp("/home/alejandro/Desktop/Universidad/IOS/LimitedShell/bin/cp",argv);
   //       exit(EXIT_SUCCESS);
   //    } else {
   //       int child_status;
   //       waitpid(pid,&child_status,0);
   //    }
      
   // } else {
   //    printf("Invalid command %s\n",argv[0]);
   // }

   
   
}

main ()
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