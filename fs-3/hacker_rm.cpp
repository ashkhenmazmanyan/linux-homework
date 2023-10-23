#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#define buf_size 5

int main(int argc, char** argv){
    if (argc<2){
        std::cerr << "file path isn't given" <<std::endl;
        exit(1);
    }
    char* path = argv[1];
    
    int fd = open(path,O_RDONLY);
    if(fd<0){
        std::cerr << strerror(errno)<<std::endl;
        exit(errno);
    }

    char buffer[buf_size +1];

    for(int i = 0; i< buf_size; ++i){
        buffer[i] = '\0';
    }

    off_t file_size = lseek(fd, 0, SEEK_END);
    if(file_size < 0){
        std::cerr << strerror(errno)<<std::endl;
        exit(errno);
        close(fd);
    }

    off_t bytes_left = file_size;
    while(bytes_left >0){
        size_t bytes_to_write = std::min(static_cast<size_t>(bytes_left), buf_size);
        ssize_t bytes_written = write(fd, buffer, bytes_to_write);
        if(bytes_written < 0){
            std::cerr << strerror(errno)<<std::endl;
            exit(errno);
            close(fd);
        }
        bytes_left = bytes_left - bytes_written;
    }

        close(fd);

        if(unlink(path) <0){
            std::cerr << stderror(errno) << std::endl;
        }

        std::cout << path <<std::endl;

        return 0;
}