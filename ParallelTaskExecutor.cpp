#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <vector>
#include <string>
#include <sstream>

int main() {
    std::vector<std::string> commands = {
        "ls -l",
        "pwd",
        "whoami"
    };
    
    std::vector<pid_t> child_pids;
    
    for (const auto& command : commands) {
        pid_t pid = fork();
        
        if (pid == 0) {
            // Дочерний процесс
            std::cout << "Starting: " << command << " (PID: " << getpid() << ")" << std::endl;
            std::flush(std::cout);
            
            // Разбиваем команду на аргументы
            std::vector<std::string> args;
            std::istringstream iss(command);
            std::string token;
            while (iss >> token) {
                args.push_back(token);
            }
            
            // Подготавливаем аргументы для execvp
            std::vector<char*> exec_args;
            for (auto& arg : args) {
                exec_args.push_back(arg.data());
            }
            exec_args.push_back(nullptr);
            
            // Запускаем команду
            execvp(exec_args[0], exec_args.data());
            
            // Если дошли сюда - ошибка exec
            std::cerr << "ERROR: Failed to execute: " << command << std::endl;
            exit(1);
            
        } else if (pid > 0) {
            // Родительский процесс
            child_pids.push_back(pid);
            std::cout << "Launched process: " << pid << " for command: " << command << std::endl;
            
        } else {
            std::cerr << "ERROR: Fork failed for command: " << command << std::endl;
        }
    }
    
    std::cout << "\nWaiting for all commands to complete..." << std::endl;
    
    for (pid_t pid : child_pids) {
        int status;
        waitpid(pid, &status, 0);
        
        if (WIFEXITED(status)) {
            std::cout << "Process " << pid << " exited with code: " << WEXITSTATUS(status) << std::endl;
        } else if (WIFSIGNALED(status)) {
            std::cout << "Process " << pid << " killed by signal: " << WTERMSIG(status) << std::endl;
        } else {
            std::cerr << "Process " << pid << " terminated abnormally" << std::endl;
        }
    }
    
    std::cout << "All commands completed successfully!" << std::endl;
    return 0;
}