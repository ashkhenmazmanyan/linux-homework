#include "shared_array.cpp"
#include <iostream>
#include <unistd.h>

int main() {
    shared_array arr("arr_name", 5);
    int i = 0;
    while(true){
        i %= 5;
        sem_wait(arr.getSemaphore()); //spasenq semaphorin
        arr[i] = i;
        std::cout << "process_2 " << arr[i] << std::endl;
        sem_post(arr.getSemaphore()); //azatenq semaphorin
        sleep(1);
        i++;
    }    
    return 0;
}