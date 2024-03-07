#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

bool isPrime(int num) {
  if (num < 2) {
    return false;
  }
  for (int i = 2; i * i <= num; ++i) {
    if (num % i == 0) {
      return false;
    }
  }
  return true;
}

int findMthPrime(int m) {
  if (m <= 0) {
    return -1; // Invalid input
  }

  int count = 0;
  for (int i = 2;; ++i) {
    if (isPrime(i)) {
      ++count;
    }
    if (count == m) {
      return i; // Return the m-th prime number
    }
  }
}

int main() {
  int pipefd[2]; // File descriptors for the pipe
  if (pipe(pipefd) < 0) {
    perror("pipe");
    return 1;
  }

  pid_t pid = fork();

  if (pid < 0) {
    perror("fork");
    return 1;
  }

  if (pid == 0) {     // Child process
    close(pipefd[1]); 
    int m;
    ssize_t bytes_read = read(pipefd[0], &m, sizeof(m));

    if (bytes_read < 0) {
      perror("read");
      std::cerr << "Error reading from the pipe" << std::endl;
      exit(1);
    }

    close(pipefd[0]); 

    // Calculate the m-th prime number
    int result = findMthPrime(m);

    if (result != -1) {
      std::cout << "Child process: " << m << "-th prime number is " << result
                << std::endl;
    } else {
      std::cerr << "Child process: Invalid input" << std::endl;
    }

    exit(0);        
  } else {  // Parent process
    close(pipefd[0]); 

    while (true) {
      int m;
      std::cout << "Enter an integer";
      if (!(std::cin >> m)) {
        std::cerr << "Invalid input" << std::endl;
        break;
      }

      if (m <= 0) {
        std::cerr << "Please enter a positive integer." << std::endl;
        continue;
      }

      ssize_t bytes_written = write(pipefd[1], &m, sizeof(m)); // Write m to the pipe

      if (bytes_written < 0) {
        perror("write");
        std::cerr << "Error writing to the pipe" << std::endl;
        break;
      }

      close(pipefd[1]); 

      int status;
      waitpid(pid, &status, 0); 

      if (status != 0) {
        std::cerr << "Error in child process" << std::endl;
        break;
      }
    }
  }

  return 0;
}