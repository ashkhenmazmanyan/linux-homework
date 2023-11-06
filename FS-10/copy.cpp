#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <fstream>


#define BUFF_SIZE 350

int main(int argc, char* argv[]) {

    if(argc < 3) {
        std::cerr << "FILE PATHS ARE NOT GIVEN" << std::endl;
        exit(1);
    }

    //file paths
    char* source_path = argv[1]; 
    char* dest_path = argv[2]; 

    //open source file
    int source_file = open(source_path, O_RDONLY);

    if(source_file < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    //open dest file
    int dest_file = open(dest_path, O_WRONLY);

    if(dest_file < 0) {
        std::cerr << strerror(errno) << std::endl;
        exit(errno);
    }

    //buffer
    char* buffer = new char[BUFF_SIZE];
    
    size_t data_read, total_data_copied = 0;
    while(true){

        //pordzum enq kardanq
        data_read = read(source_file, buffer, BUFF_SIZE);

        //if kardalu ban chka
        if(data_read < 0) {
            std::cerr << strerror(errno) << std::endl;
            exit(errno);
        }

        //if kardacinq prcanq
        if(data_read == 0) {
            break;
        }

        //hima destum grum enq kardacacy
        write(dest_file, buffer, data_read);
        total_data_copied = total_data_copied + data_read;
    }
    //pakenq
    close(source_file);
    close(dest_file);


    std::cout << "TOTAL BYTES COPIED" << total_data_copied << "BYTES" << std::endl;

    off_t sourceFSize = lseek(source_file, 0, SEEK_END);
    off_t destFSize = lseek(dest_file, 0, SEEK_END);
    off_t holesSize = sourceFSize - destFSize;

    std::cout << "TOTAL BYTES OF HOLES" <<  holesSize << "BYTES" << std::endl;


    return 0;
}

