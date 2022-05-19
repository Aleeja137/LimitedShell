//read from manual.txt with lseek and wait for close (q)
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


#define first_bytes 149;
#define ls_bytes 749;
#define cat_bytes 589;
#define cp_bytes 578;
#define link_bytes 515;
#define line_bytes 129;
#define BUFFER_SIZE 1


void writeManual(int b_offset, int b_write)
{

    int   read_size, Temp;
    char  buffer[BUFFER_SIZE];

    int count = 0;
    int file = open("/home/alejandro/Desktop/Universidad/IOS/LimitedShell/documentation/manuals.txt",O_RDONLY); 

    if( file < 0)
    {
        fprintf(stderr,"Could not open manual file\n");
        exit(EXIT_FAILURE);
    }

    lseek(file,b_offset,SEEK_SET);

    while( count < b_write )
    {
        read_size = read(file, buffer, BUFFER_SIZE);
        count++;
        Temp = write(1, &buffer, read_size);
    } 
    Temp = write(1,"\n",2);
    close(file);

}
  
int main(int argc, char **argv)
{   

    char input[100];

    int offset = 0;
    int lenght = 0;

    if(argc==1){
        lenght = 149;       
    } else if (argc == 2 && strcmp(argv[1],"ls")==0){
        offset = 149+129;
        lenght = 749;
    } else if (argc == 2 && strcmp(argv[1],"cat")==0){
        offset = 2*129 + 149 + 749;
        lenght = 589;
    } else if (argc == 2 && strcmp(argv[1],"cp")==0){
        offset = 3*129 + 149 + 749 + 589;
        lenght = 578;
    } else if (argc == 2 && strcmp(argv[1],"link")==0){
        offset = 4*129 + 149 + 749 + 589 + 578;
        lenght = 478;
    } else {
        printf("man error: too many arguments\n");
        exit(EXIT_FAILURE);
        return -1;
    }

    writeManual(offset,lenght);
    gets(input);
    while (strcmp(input,"q")!=0)
    {
        gets(input);
    }
    exit(EXIT_SUCCESS);

    

    return 0;
}