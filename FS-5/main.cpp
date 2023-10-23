#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "File Path Not Given" << std::endl;
        return 1;
    }

    char* path = argv[1];

    int fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd < 0) {
        std::cerr << "Error opening the file: " << strerror(errno) << std::endl;
        return 1;
    }

    int fd1 = dup(fd);
    int fd2 = dup(fd);

    
    dup2(fd1, 1); 
    dup2(fd2, 2); 

    std::cout << "first line" << std::endl;
    std::cerr << "second line" << std::endl;


    close(fd);
    close(fd1);
    close(fd2);

    return 0;
}