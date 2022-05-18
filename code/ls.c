#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>



int read(char *path, int longVersion){


    DIR *dp;
    struct dirent *dirp;
    dp = opendir(path);

    if(dp){ //directory exists
        if (longVersion==1)
        {
            while ((dirp = readdir(dp)) != NULL){
                #if defined _DIRENT_HAVE_D_TYPE
                if (dirp->d_type==4)
                {
                    printf("%s d\n", dirp->d_name);
                } else if (dirp->d_type==8)
                {
                    printf("%s f\n", dirp->d_name);
                }
                #endif
            }
            closedir(dp);
            exit(EXIT_SUCCESS);
        } else if (longVersion==0)
        {
            while ((dirp = readdir(dp)) != NULL){
                printf("%s\n", dirp->d_name);
            }
            closedir(dp);
            exit(EXIT_SUCCESS);
        }
        return 1;
    } else { //directory does not exist
        printf("ls error: directory not found\n");
        exit(EXIT_FAILURE);
        return -1;
    }

}
int main(int argc, char **argv){

   int result=1;

    if (argc<1) //internal error, can ingore
    {
        printf("ls error: too few arguments for function call\n");
        exit(EXIT_FAILURE);
    }

    else if (argc==1 && strcmp(argv[0],"ls")!=0) //internal error, can ignore
    {
        printf("ls error: caller name and executable name do not coincide\n");
        exit(EXIT_FAILURE);
    }

    else if (argc==1) //ls
    {
        printf("ls error: directory path not specified\n");
        exit(EXIT_FAILURE);
        
    }

    else if (argc==2 && strcmp(argv[1],"-l")==0)  //ls -l
    {
        printf("ls error: directory path not specified\n");
        exit(EXIT_FAILURE);
    }
    
    else if (argc==2)  //ls path
    {
        result = read(argv[1],0);
    }
    

    else if (argc==3 && strcmp(argv[1],"-l")==0 && strcmp(argv[2],"-l")==0)  //ls -l -l
    {
        printf("ls error: repeated option '-l' and no directory path specified\n");
        exit(EXIT_FAILURE);
    }
    else if (argc==3 && strcmp(argv[1],"-l")==0 && strcmp(argv[2],"-l")!=0) //ls -l path
    {
        result = read(argv[2],1);
    }
    else if (argc==3 && strcmp(argv[1],"-l")!=0 && strcmp(argv[2],"-l")==0) //ls path -l
    {
        result = read(argv[1],1);
    }
    

    if(result<0){
        exit(EXIT_FAILURE);
    }
}