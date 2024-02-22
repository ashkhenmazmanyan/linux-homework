#include "shared_array.h"
#include <iostream>
#include <cstring>

shared_array::shared_array(std::string& name, size_t size) : size(size), name(name) {
    fd = shm_open(name.c_str(), O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        std::cerr << "Error creating shared memory" << std::endl;
    }

    ftruncate(fd, (size + 1) * sizeof(char)); 
    size_t total_size = (size + 1) * sizeof(char);
    size_t pages = (total_size + KB_4 - 1) / KB_4;
    total_size = pages * KB_4;

    data = reinterpret_cast<char*>(mmap(nullptr, total_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
    semaphore = reinterpret_cast<sem_t*>(data + size);
    sem_init(semaphore, 1, 1); 
}

shared_array::~shared_array() {
    munmap(data, (size + 1) * sizeof(char));
    close(fd);
    shm_unlink(name.c_str());
    sem_destroy(semaphore);
}

char& shared_array::operator[](size_t index) {
    return data[index];
}

sem_t* shared_array::getSemaphore() {
    return semaphore;
}
