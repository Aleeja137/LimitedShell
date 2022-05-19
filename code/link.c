#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int linkFiles(int argc, char* argv[],int doLink){

    if(doLink==0) //We want to link
    {
        // Link system call
        int l = link(argv[1], argv[2]);
    
        // Check result
        if (l == 0) {
            printf("Files linked\n");
            exit(EXIT_SUCCESS);
            return 0;
        } else {
            fprintf(stderr,"link error: unable to link, check valid path to file and valid new name\n");
            exit(EXIT_FAILURE);
            return -1;
        }
    } else { //We want to unlink

        // Unlink system call
        int l = unlink(argv[0]);
    
        // Check result
        if (l == 0) {
            printf("Files unlinked\n");
            exit(EXIT_SUCCESS);
            return 0;
        } else {
            fprintf(stderr,"link error: unable to unlink, check valid path to file and valid new name\n");
            exit(EXIT_FAILURE);
            return -1;
        }
    }
    
  
    
}


int main(int argc, char* argv[])
{

    // In the main method, we will just check if the input command is valid

    int result=1;

    if (argc<1) //internal error, can ingore
    {
        fprintf(stderr,"link error: too few arguments for function call, see man link for help\n");
        exit(EXIT_FAILURE);
    }

    else if (argc==1 && strcmp(argv[0],"link")!=0) //internal error, can ignore
    {
        fprintf(stderr,"link error: caller name and executable name do not coincide\n");
        exit(EXIT_FAILURE);
    }

    else if (argc==1) //link
    {
        fprintf(stderr,"link error: path to the file that will be linked not specified\n");
        exit(EXIT_FAILURE);
        
    }

    else if (argc==2 && strcmp(argv[1],"-u")==0)  //link -u
    {
        fprintf(stderr,"link error: path of file not specified\n");
        exit(EXIT_FAILURE);
    }

    else if (argc==2 && strcmp(argv[1],"-u")!=0)  //link path1
    {
        fprintf(stderr,"link error: name of the new link not specified\n");
        exit(EXIT_FAILURE);
    }
   
    
    else if (argc==3 && strcmp(argv[1],"-u")!=0 && strcmp(argv[2],"-u")!=0)  //link path1 path2
    {
        linkFiles(argc,argv,0);
        exit(EXIT_SUCCESS);
        return 0;
    }

    else if (argc==3 && strcmp(argv[1],"-u")==0 && strcmp(argv[2],"-u")==0)  //link -u -u
    {
        fprintf(stderr,"link error: double option -u and path the file not specified\n");
        exit(EXIT_FAILURE);
    }

    else if (argc==3 && (strcmp(argv[1],"-u")==0))  //link -u path1 
    {
        linkFiles(argc,&argv[2],1);
        exit(EXIT_SUCCESS);
        return 0;
    }

    else if (argc==3 && (strcmp(argv[2],"-u")==0))  //link path1 -u
    {
        linkFiles(argc,&argv[1],1);
        exit(EXIT_SUCCESS);
        return 0;
    }

    else
    {
        fprintf(stderr,"link error: too many arguments for function call, see man link for help\n");
        exit(EXIT_FAILURE);
    }


   
}