#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>  

#define MAX_CHARS 200



int readDirectory(char *path, int longVersion){


    DIR *dp;
    struct dirent *dirp;
    dp = opendir(path);
    char Path[MAX_CHARS];
    int Tmp;
    struct stat Stat;

    if(dp){ //directory exists
        if (longVersion==1)
        {   
            while (1)  {
                dirp = readdir(dp);
                if (dirp == 0) break;  /* reached end of directory entries */
                /* process file (other than . and ..) */
                if (strcmp(dirp->d_name,".") != 0 &&
                    strcmp(dirp->d_name,"..") != 0)  {
                    /* print file name */
                    printf("%s",dirp->d_name);
                    /* build full path name of the file, for stat() */
                    Path[0] = 0;
                    strcat(Path,path);
                    strcat(Path,"/");
                    strcat(Path,dirp->d_name);
                        Tmp = stat(Path,&Stat); 
                        /* Stat now contains lots of info about the file,
                            e.g. its size, though we are not interested in
                            most of that info here */
                        if (S_ISDIR(Stat.st_mode)) printf("*");
                        printf("\n");
                }
            }
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
        result = readDirectory(argv[1],0);
    }
    

    else if (argc==3 && strcmp(argv[1],"-l")==0 && strcmp(argv[2],"-l")==0)  //ls -l -l
    {
        printf("ls error: repeated option '-l' and no directory path specified\n");
        exit(EXIT_FAILURE);
    }
    else if (argc==3 && strcmp(argv[1],"-l")==0 && strcmp(argv[2],"-l")!=0) //ls -l path
    {
        result = readDirectory(argv[2],1);
    }
    else if (argc==3 && strcmp(argv[1],"-l")!=0 && strcmp(argv[2],"-l")==0) //ls path -l
    {
        result = readDirectory(argv[1],1);
    }
    

    if(result<0){
        exit(EXIT_FAILURE);
    }
}