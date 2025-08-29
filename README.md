# Parallel Command Executor

A C++ program that demonstrates parallel command execution using Unix fork() and execvp() system calls. The program runs multiple shell commands concurrently and waits for their completion.

## Features

- **Parallel Execution**: Runs multiple commands simultaneously using child processes
- **Real-time Output**: Displays process IDs and execution status in real-time
- **Error Handling**: Proper error handling for fork() and exec() failures
- **Process Monitoring**: Tracks and reports exit status of all child processes
- **Cross-platform**: Works on any Unix-like system (Linux, macOS, etc.)

## How It Works

1. **Process Creation**: Uses `fork()` to create child processes for each command
2. **Command Execution**: Uses `execvp()` to execute shell commands in child processes
3. **Argument Parsing**: Automatically splits command strings into executable arguments
4. **Process Management**: Parent process waits for all children to complete using `waitpid()`
5. **Status Reporting**: Provides detailed exit status for each process

## Code Structure

```cpp
main()
├── Creates vector of commands to execute
├── Forks child processes for each command
│   ├── Child: executes command using execvp()
│   └── Parent: tracks child PIDs
└── Waits for all children and reports results
```

## Usage

### Compilation

```bash
g++ -o parallel_executor parallel_executor.cpp
```

### Execution

```bash
./parallel_executor
```

### Example Output

```
Starting: ls -l (PID: 1234)
Launched process: 1234 for command: ls -l
Starting: pwd (PID: 1235)
Launched process: 1235 for command: pwd

Waiting for all commands to complete...
total 24
-rwxr-xr-x 1 user user 16856 Jan 22 12:00 parallel_executor
-rw-r--r-- 1 user user  1234 Jan 22 11:58 parallel_executor.cpp
/home/user/projects
Process 1234 exited with code: 0
Process 1235 exited with code: 0
All commands completed successfully!
```

## Customization

Modify the `commands` vector to execute different commands:

```cpp
std::vector<std::string> commands = {
    "find . -name '*.cpp'",
    "gcc --version",
    "date",
    "echo 'Hello from child process'"
};
```

## Error Handling

The program handles:
- Fork failures
- Exec failures
- Abnormal process termination
- Signal-based termination

## Dependencies

- C++11 or newer
- Unix-like operating system
- Standard C++ library
- Unix system headers (unistd.h, sys/wait.h)

## Limitations

- Windows not supported (uses Unix-specific system calls)
- Commands execute in parallel without synchronization
- No input/output redirection between processes
- Limited to system's maximum process limit

## Educational Value

This code demonstrates:
- Process creation with fork()
- Command execution with exec()
- Process monitoring with waitpid()
- Argument parsing for exec functions
- Basic shell command execution
- Parallel programming concepts

## License

Free to use for educational and personal projects.
