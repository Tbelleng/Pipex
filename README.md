# Pipex

Pipex is a program that simulates the behavior of the shell pipe (`|`) in Unix-like systems. It takes two commands as input and redirects the output of the first command as input to the second command, just like the shell pipe.

## Table of Contents
- [Features](#features)
- [Prerequisites](#prerequisites)
- [Installation](#installation)
- [Usage](#usage)
- [Examples](#examples)

## Features
- Simulates the behavior of the shell pipe (`|`) with two commands.
- Supports input and output redirection.
- Works on Unix-like systems.

## Prerequisites
Before you begin, ensure you have met the following requirements:
- Your system should be running a Unix-like operating system (e.g., Linux or macOS).
- You should have a C compiler (e.g., GCC) installed on your system.

## Installation
1. Clone the repository:
   ```shell
   git clone https://github.com/YourUsername/YourRepoName.git
   
## Usage

```./pipex file1 cmd1 cmd2 file2```

    file1: Input file whose content will be passed as input to cmd1.
    cmd1: The first command to run.
    cmd2: The second command to run.
    file2: Output file where the result will be stored.

## Examples

# Example 1: Using a simple pipe
./pipex infile "ls -l" "grep keyword" outfile

# Example 2: Redirecting input/output
./pipex infile "cat" "sort -r" > outfile

# Example 3: Using command substitution
./pipex infile "$(cat filelist)" "grep pattern" outfile

