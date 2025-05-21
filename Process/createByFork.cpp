#include <iostream>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t check = fork();

    if (check > 0) { // parent process
        pid_t parent_id = getpid();
        std::cout << "Parent ID: " << parent_id << std::endl;
    } else if (check == 0) { // child process
        pid_t child_id = getpid();
        std::cout << "Child ID: " << child_id << std::endl;
    } else { // fork failed
        std::cerr << "Fork failed" << std::endl;
        return 1;
    }

    return 0;
}