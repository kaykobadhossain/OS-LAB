#include <iostream>
#include <unistd.h>   // fork(), sleep(), getpid()
#include <sys/types.h> // pid_t
#include <sys/wait.h> // waitpid()
#include <csignal>    // kill(), SIGTERM

int main() {
    pid_t check = fork();

    if (check > 0) { // প্যারেন্ট প্রসেস
        pid_t parent_id = getpid();
        std::cout << "Parent ID: " << parent_id << std::endl;

        // ৫ সেকেন্ড অপেক্ষা
        sleep(5);

        // চাইল্ড প্রসেস টার্মিনেট করা
        if (kill(check, SIGTERM) == -1) {
            std::cout << "Failed to terminate child!\n";
        } else {
            std::cout << "Child terminated.\n";
        }

        // চাইল্ড প্রসেস শেষ হওয়ার অপেক্ষা
        int status;
        waitpid(check, &status, 0);
        if (WIFEXITED(status)) {
            std::cout << "Child exit code: " << WEXITSTATUS(status) << "\n";
        }
    } else if (check == 0) { // চাইল্ড প্রসেস
        pid_t child_id = getpid();
        std::cout << "Child ID: " << child_id << std::endl;
        
        // চাইল্ড প্রসেসকে কিছুক্ষণ চলতে দেওয়ার জন্য অপেক্ষা
        sleep(10); // উদাহরণস্বরূপ, চাইল্ড ১০ সেকেন্ড চলবে
    } else { // ফর্ক ফেল করলে
        std::cerr << "Fork failed" << std::endl;
        return 1;
    }

    return 0;
}