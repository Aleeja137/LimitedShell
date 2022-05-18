#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int copyFile(int argc, char **argv){

}
int main(int argc, char **argv)
{
    char buffer[1024];
    int files[2];
    ssize_t count;

    /* Check for insufficient parameters */
    if (argc < 3)
        return -1;
    files[0] = open(argv[1], O_RDONLY);
    if (files[0] == -1) /* Check if file opened */
        return -1;
    files[1] = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    if (files[1] == -1) /* Check if file opened (permissions problems ...) */
    {
        close(files[0]);
        return -1;
    }

    while ((count = read(files[0], buffer, sizeof(buffer))) != 0)
        write(files[1], buffer, count);

    return 0;
}