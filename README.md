# Minishell

<p align="left">
  <strong>✨ 𝒜𝓈 𝒷𝑒𝒶𝓊𝓉𝒾𝒻𝓊𝓁 𝒶𝓈 𝒶 𝓈𝒽𝑒𝓁𝓁 ✨</strong>
</p>

## 📌 Overview

Minishell is a simple Unix shell implementation written in C. This project is part of the 42 curriculum and aims to deepen the understanding of process management, file descriptors, and system calls.

## Features

- Custom interactive prompt.
- Command execution via absolute, relative paths, or `$PATH` resolution.
- Handle input/output redirections (`<`, `>`, `<<`, `>>`).
- Implement pipes (`|`) for command chaining.
- Environment variable expansion (`$VAR` and `$?`).
- Built-in commands:
  - `echo` (with `-n` option)
  - `cd` (with relative/absolute paths)
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`).
- Command history support.

### Compilation

```bash
1. git clone https://github.com/novth17/42-minishell.git
2. cd 42-minishell
3. make
```

## Run

```bash
./minishell
```

## Example usage

```bash
🦒 >>> Giraffeshell>$ echo Hello World
Hello World

🦒 >>> Giraffeshell>$ export NAME=42
🦒 >>> Giraffeshell>$ echo $NAME
42

🦒 >>> Giraffeshell>$ ls | grep .c > out.txt
🦒 >>> Giraffeshell>$ cat < out.txt | wc -l
```

## 📚 Key Concepts Learned

- Process control: fork, execve, waitpid, pipe, dup2
- Terminal signals: sigaction, tcsetattr, tcgetattr
- Shell parsing and execution via Abstract Syntax Tree (AST)
- I/O redirection and FD manipulation
- Memory management in C
