//read from manual.txt with lseek and wait for close (q)
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>

#define first_bytes 149;
#define ls_bytes 594;
#define cat_bytes 488;
#define cp_bytes 576;
#define link_bytes 515;
#define line_bytes 129;


void writeManual(int b_offset, int b_write)
{

    int   read_size;
    char *buf[600];



    int count = 0, ch;
    FILE *fp;

    fp = fopen("/home/alejandro/Desktop/Universidad/IOS/LimitedShell/documentation/manuals.txt","r"); 

    if( fp == NULL )
    {
        printf("Could not open manual file\n");
        exit(EXIT_FAILURE);
    }

    while( ( ch = fgetc(fp) ) != EOF && count < b_write)
    {
        //buf[count++] = ch; // make Buffer global variable
        count++;
        printf("%c",ch);
    } 
    printf("\n");
    fclose(fp);

    // // add offset from start to b_offset
    // int file = open("/home/alejandro/Desktop/Universidad/IOS/LimitedShell/documentation/manuals.txt",O_RDONLY);
    // lseek(file,b_offset,SEEK_SET);
    // //write only b_wrtie bytes in console and exit

    // while ((read_size = read(file, buf, BUFFER_SIZE)) > 0)
    //     write(1, &buffer, read_size);

    // close(file);
}
  
// Driver code
int main(int argc, char **argv)
{   

    char input[100];

    int offset = 0;
    int lenght = 0;

    if(argc==1){
        lenght = first_bytes;       
    } else if (argc == 2 && strcmp(argv[1],"ls")==0){
        offset = 0*line_bytes + first_bytes;
        lenght = ls_bytes;
    } else if (argc == 2 && strcmp(argv[1],"cat")==0){
        offset = 1*line_bytes + first_bytes + ls_bytes;
        lenght = cat_bytes;
    } else if (argc == 2 && strcmp(argv[1],"cp")==0){
        offset = 2*line_bytes + first_bytes + ls_bytes + cat_bytes;
        lenght = cp_bytes;
    } else if (argc == 2 && strcmp(argv[1],"link")==0){
        offset = 3*line_bytes + first_bytes + ls_bytes + cat_bytes + cp_bytes;
        lenght = link_bytes;
    } else {
        printf("man error: too many arguments\n");
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