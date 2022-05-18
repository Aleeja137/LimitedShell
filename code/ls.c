#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>  
#include <time.h>

#define MAX_CHARS 200



int readDirectory(char *path, int longVersion){


    DIR *dp;             // Contains the directory
    struct dirent *dirp; // Contaions the directory entries
    char Path[MAX_CHARS]; // Contains the path of the direc tory entries
    struct stat Stat;     // Contains the info about the directory entries for the -l option
    int Tmp;

    dp = opendir(path);  

    if(dp){ //directory exists
        if (longVersion==1)
        {   
            while (1)  { // We iterate the directory entries
                dirp = readdir(dp);
                if (dirp == 0) break;  // No more entries, break

                // Ignore '.' and '..' files
                if (strcmp(dirp->d_name,".") != 0 &&
                    strcmp(dirp->d_name,"..") != 0)  {
                    
                    // Get (build) the path for stat
                    Path[0] = 0;
                    strcat(Path,path);
                    strcat(Path,"/");
                    strcat(Path,dirp->d_name);

                    // Call stat    
                    Tmp = stat(Path,&Stat); 

                    //Prepare last modified time from seconds from epoch to human readable
                    time_t rawtime = Stat.st_atime;
                    struct tm  ts;
                    char       bufTime[80];

                    // Format time, "ddd yyyy-mm-dd hh:mm:ss zzz"
                    ts = *localtime(&rawtime);
                    strftime(bufTime, sizeof(bufTime), "%a %Y-%m-%d %H:%M:%S %Z", &ts);

                    // Print the information
                    printf("Name: %s - Size (bytes): %ld - Last modified: %s ",dirp->d_name,Stat.st_size,bufTime);
                    if (S_ISDIR(Stat.st_mode)) printf("*");
                    printf("\n");
                }
            }
        } else if (longVersion==0) // No -l option, just print the names
        {
           while (1)  { // We iterate the directory entries
                dirp = readdir(dp);
                if (dirp == 0) break;  // No more entries, break
                
                // Ignore '.' and '..' files
                if (strcmp(dirp->d_name,".") != 0 &&
                    strcmp(dirp->d_name,"..") != 0)  {
                    printf("%s\n", dirp->d_name);
                }
            }
        }
        closedir(dp);
        exit(EXIT_SUCCESS);
        return 1;
    } else { //directory does not exist
        printf("ls error: directory not found\n");
        exit(EXIT_FAILURE);
        return -1;
    }

}
int main(int argc, char **argv){


    // In the main method, we will just check if the input command is valid

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
    

    if(result<0){  // Invalid path
        exit(EXIT_FAILURE);
    }
}