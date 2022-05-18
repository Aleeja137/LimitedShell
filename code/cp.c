#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int copyFile(int argc, char **argv){

    char buffer[1024];
    int files[2]; // files[0] is the original, files[1] is the copy
    ssize_t count;

    

    
    // Open the file for reading
    files[0] = open(argv[1], O_RDONLY);
    if (files[0] == -1)
    {
        fprintf(stderr,"cp error: unable to open original file, check path and/or permissions\n");
        exit(EXIT_FAILURE);
        return -1;
    }

    // Open the file for writting and creating if non existent. Also check the permissions for manipulating the file
    files[1] = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (files[1] == -1) 
    {
        fprintf(stderr,"cp error: unable to open target file, check path and/or permissions\n");
        exit(EXIT_FAILURE);
        return -1;
    }

    while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
    {
        write(files[1], buffer, count);
    }

    printf("File copied!\n");
    return 0;

}
int main(int argc, char **argv)
{
    // In the main method, we will just check if the input command is valid

    if (argc<3) // null / cp / cp path
    {
        fprintf(stderr,"cp error: too few arguments for function call\n");
        exit(EXIT_FAILURE);
    }

    else if (argc==3)  // cp path1 path2
    {
        copyFile(argc,argv);
        exit(EXIT_SUCCESS);
        return 0;
    }
    else
    {
        fprintf(stderr,"cp error: too many arguments for function call\n");
        exit(EXIT_FAILURE);
    }
}