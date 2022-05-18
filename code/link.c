#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int linkFiles(int argc, char* argv[]){

     // Link system call
    int l = link(argv[1], argv[2]);
  
    // Check result
    if (l == 0) {
        printf("Files linked\n");
        exit(EXIT_SUCCESS);
        return 0;
    } else {
        printf("link error: unable to link, check valid path to file and valid new name\n");
        exit(EXIT_FAILURE);
        return -1;
    }
  
    
}


int main(int argc, char* argv[])
{

    // In the main method, we will just check if the input command is valid

    int result=1;

    if (argc<1) //internal error, can ingore
    {
        printf("link error: too few arguments for function call\n");
        exit(EXIT_FAILURE);
    }

    else if (argc==1 && strcmp(argv[0],"link")!=0) //internal error, can ignore
    {
        printf("link error: caller name and executable name do not coincide\n");
        exit(EXIT_FAILURE);
    }

    else if (argc==1) //link
    {
        printf("link error: path to the file that will be linked not specified\n");
        exit(EXIT_FAILURE);
        
    }

    else if (argc==2)  //ls path1
    {
       printf("link error: name of the new link not specified\n");
        exit(EXIT_FAILURE);
    }
   
    else if (argc==3)  //ls path1 path2
    {
        linkFiles(argc,argv);
    }

    else
    {
        printf("link error: too many arguments for function call\n");
        exit(EXIT_FAILURE);
    }


   
}