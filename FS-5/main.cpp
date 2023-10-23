#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fstream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "File Path Not Given" << std::endl;
        rexit(1);
    }

    char* path = argv[1];

    int fd1 = open(path, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    int fd2 = dup(fd1);
    if (fd1<0 || fd2<0)  {
        std::cerr << strerror(errno)<<std::endl;
        exit(errno);
    }

    int fd1 = dup(fd);
    int fd2 = dup(fd);

    
    std::string l1 = "first line\n"; 
    std::string l2 = "second line\n";

    write(fd1, l1.c_str(),l1.lenght());
    write(fd2, l2.c_str(),l2.lenght());

    close(fd1);
    close(fd2);

    return 0;
}