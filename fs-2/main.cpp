#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>


#define buf_size 5

int main(int argc, char** argv){
    if (argc<3){
        std::cerr << "file path isn't given" <<std::endl;
        exit(1);
    }
    char* path = argv[1];
    

    int fd = open(path,O_RDONLY);
    if(fd<0){
        std::cerr << strerror(errno)<<std::endl;
        exit(errno);
    }
    char buffer[buf_size +1 ];

    char* path2 = argv[2];
    
    int fd2 = open(path2,O_WRONLY | O_CREAT | O_TRUNC, S_IWUSR | S_IRGRP | S_IROTH);
    if(fd2<0){
        std::cerr << strerror(errno)<<std::endl;
        exit(errno);
    }

    while(true){
        int read_bytes = read(fd, buffer, buf_size);

        if(read_bytes<0){
            std::cerr << strerror(errno)<<std::endl;
            exit(errno);
        }
        if(read_bytes == 0){
            break;
        }
        buffer[read_bytes] = '\0';
            std::cout << buffer;
        
        int written_bytes = write(fd2, buffer, read_bytes);
        if(written_bytes<0){
            std::cerr << strerror(errno)<<std::endl;
            exit(errno);
        }
    }

    int close_f = close(fd);
    if(close_f<0){
        std::cerr << strerror(errno) << std::endl;
    }

    int close_f2 = close(fd2);
    if(close_f2<0){
        std::cerr << strerror(errno) << std::endl;
    }
    
    return 0;
}