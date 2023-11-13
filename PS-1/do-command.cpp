#include <iostream>
#include <chrono>
#include <cstring>
#include <cstdlib>
#include <sys/wait.h>
#include <unistd.h>

void do_command(char** argv) {
    // start time
    auto start_time = std::chrono::high_resolution_clock::now();

    // new process
    int pid = fork();

    if (pid < 0) {
        std::cerr << "Error creating child process." << std::endl;
        exit(1);
    } else if (pid == 0) {
        // child process, exec enq anum
        execvp(argv[0], argv);

        std::cerr << "Error executing command: " << strerror(errno) << std::endl;
        exit(errno);
    } else {
        // parent process
        int status;

        // child status
        while (waitpid(pid, &status, 0) < 0) {
            if (errno != EINTR) {
                std::cerr << "Error waiting for child process: " << strerror(errno) << std::endl;
                exit(errno);
            }
        }

        // end time
        auto end_time = std::chrono::high_resolution_clock::now();
        // duration
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);

        std::cout << "Command exited with status: " << WEXITSTATUS(status) << std::endl;
        std::cout << "Duration: " << duration.count() << " milliseconds" << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " command [args...]" << std::endl;
        exit(1);
    }

    do_command(argv + 1);

    return 0;
}