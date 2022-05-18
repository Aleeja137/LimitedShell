#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    DIR *dp;
    struct dirent *dirp;

    if (argc != 2) {
        fprintf(stderr, "Usage: ./program directory_name\n");
        exit(EXIT_FAILURE);
    }

    dp = opendir(argv[1]);

    while ((dirp = readdir(dp)) != NULL){
        #if defined _DIRENT_HAVE_D_TYPE
        if (dirp->d_type==4)
        {
            printf("File name: %s\nFile type: folder\nFile d_reclen: %d\n", dirp->d_name,dirp->d_reclen);
        } else if (dirp->d_type==8)
        {
            printf("File name: %s\nFile type: File\nFile d_reclen: %d\n", dirp->d_name,dirp->d_reclen);
        }
        #endif
    }
    closedir(dp);
    exit(EXIT_SUCCESS);
}

