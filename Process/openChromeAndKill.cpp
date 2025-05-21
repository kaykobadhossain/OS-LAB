#include <iostream>
#include <unistd.h>   // fork(), execvp(), sleep()
#include <sys/wait.h> // waitpid()
#include <csignal>    // kill(), SIGTERM

int main() {
    pid_t pid = fork(); // নতুন প্রসেস তৈরি

    if (pid == -1) {
        std::cout << "Fork failed!\n";
        return 1;
    } else if (pid == 0) {
        // চাইল্ড প্রসেস: Chrome চালানো
        char *command[] = {(char *)"google-chrome", NULL};
        execvp(command[0], command);
        std::cout << "Exec failed!\n";
        return 1;
    } else {
        // প্যারেন্ট প্রসেস
        std::cout << "Chrome opened. PID: " << pid << "\n";

        // ৫ সেকেন্ড অপেক্ষা
        sleep(5);

        // প্রসেস টার্মিনেট
        if (kill(pid, SIGTERM) == -1) {
            std::cout << "Failed to terminate Chrome!\n";
        } else {
            std::cout << "Chrome terminated.\n";
        }

        // প্রসেস শেষ হওয়ার অপেক্ষা
        int status;
        waitpid(pid, &status, 0);
        if (WIFEXITED(status)) {
            std::cout << "Exit code: " << WEXITSTATUS(status) << "\n";
        }
    }

    return 0;
}