#include <iostream>
#include <unistd.h>   // fork(), execvp(), sleep()
#include <sys/wait.h> // waitpid()
#include <csignal>    // kill(), SIGTERM

int main() {
    pid_t pid1, pid2; // দুটি চাইল্ড প্রসেসের জন্য PID

    // প্রথম চাইল্ড প্রসেস: YouTube ওপেন
    pid1 = fork();
    if (pid1 == -1) {
        std::cout << "Fork failed for YouTube!\n";
        return 1;
    } else if (pid1 == 0) {
        // চাইল্ড প্রসেস: YouTube ওপেন
        char *command[] = {(char *)"google-chrome", (char *)"https://www.youtube.com", NULL};
        execvp(command[0], command);
        std::cout << "Exec failed for YouTube!\n";
        return 1;
    }

    // দ্বিতীয় চাইল্ড প্রসেস: Wikipedia ওপেন
    pid2 = fork();
    if (pid2 == -1) {
        std::cout << "Fork failed for Wikipedia!\n";
        return 1;
    } else if (pid2 == 0) {
        // চাইল্ড প্রসেস: Wikipedia ওপেন
        char *command[] = {(char *)"google-chrome", (char *)"https://www.wikipedia.org", NULL};
        execvp(command[0], command);
        std::cout << "Exec failed for Wikipedia!\n";
        return 1;
    }

    // প্যারেন্ট প্রসেস
    std::cout << "YouTube opened. PID: " << pid1 << "\n";
    std::cout << "Wikipedia opened. PID: " << pid2 << "\n";

    // ৫ সেকেন্ড অপেক্ষা
    sleep(5);

    // প্রথম প্রসেস (YouTube) টার্মিনেট
    if (kill(pid1, SIGTERM) == -1) {
        std::cout << "Failed to terminate YouTube!\n";
    } else {
        std::cout << "YouTube terminated.\n";
    }

    // দ্বিতীয় প্রসেস (Wikipedia) টার্মিনেট
    if (kill(pid2, SIGTERM) == -1) {
        std::cout << "Failed to terminate Wikipedia!\n";
    } else {
        std::cout << "Wikipedia terminated.\n";
    }

    // দুটি প্রসেস শেষ হওয়ার অপেক্ষা
    int status;
    waitpid(pid1, &status, 0);
    if (WIFEXITED(status)) {
        std::cout << "YouTube exit code: " << WEXITSTATUS(status) << "\n";
    }

    waitpid(pid2, &status, 0);
    if (WIFEXITED(status)) {
        std::cout << "Wikipedia exit code: " << WEXITSTATUS(status) << "\n";
    }

    return 0;
}