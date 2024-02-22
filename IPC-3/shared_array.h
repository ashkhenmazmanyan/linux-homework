#ifndef SHARED_ARRAY_H
#define SHARED_ARRAY_H

#include <iostream>
#include <fcntl.h>
#include <string>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <semaphore.h>

#define KB_4 4096

class shared_array {
private:
    std::string name;
    int fd;
    size_t size;
    char* data;
    sem_t* semaphore;

public:
    shared_array(std::string& name, size_t size);

    ~shared_array();

    char& operator[](size_t index);

    sem_t* getSemaphore(); // Getter for semaphore
};

#endif
