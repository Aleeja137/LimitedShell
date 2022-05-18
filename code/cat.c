#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#define BUFFER_SIZE 50


int display(int argc, char **argv){
    int   file, Temp;
    char  buffer[BUFFER_SIZE];
    int   read_size;


    file = open(argv[1], O_RDONLY);
    if (file == -1)
        {
        fprintf(stderr, "Error: %s: file not found\n", argv[1]);
        exit(EXIT_FAILURE);
        return (-1);
        }
    while ((read_size = read(file, buffer, BUFFER_SIZE)) > 0)
        Temp = write(1, &buffer, read_size);
        Temp = write(1,"\n",2);

    close(file);
    exit(EXIT_SUCCESS);
    return (0);

}


int main(int argc, char **argv)
{
    // In the main method, we will just check if the input command is valid

     if (argc<1) // internal error, can ingore
    {
        printf("cat error: too few arguments for function call\n");
        exit(EXIT_FAILURE);
    }

    else if (argc==1 && strcmp(argv[0],"cat")!=0) // internal error, can ignore
    {
        printf("cat error: caller name and executable name do not coincide\n");
        exit(EXIT_FAILURE);
    }

    else if (argc==1) // cat
    {
        printf("cat error: file path not specified\n");
        exit(EXIT_FAILURE);
        
    }

    else if (argc==2) // cat path
    {
        //printf("Displaying the contents of %s",argv[1]);
        display(argc,argv);
        exit(EXIT_SUCCESS);
        return (0);
    }

    else if (argc==3) // cat path otherPath
    {
        //printf("Copying the contents of %s to %s",argv[1],argv[2]);
        freopen(argv[2], "a+", stdout); 
        display(argc,argv);
        exit(EXIT_SUCCESS);
        return (0);
    }

    else
    {
        printf("ls error: too many arguments for function call\n");
        exit(EXIT_FAILURE);
    }
    
    
}