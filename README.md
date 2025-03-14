# Minishell
**As beautiful as a shell**

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


## Very useful links:

- [Hive dashboard forum post](https://dashboard.hive.fi/topics/101/messages?cursus_id=21)
- [Git repo: zelhajou](https://github.com/zelhajou/ft_unix_minishell)
- [Git repo: madebypixel02](https://gitlab.com/madebypixel02/minishell)
- [Minishell architecture flowchart picture](https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J)

## Memory arena knowledge:
https://www.rfleury.com/p/untangling-lifetimes-the-arena-allocator
https://m.youtube.com/watch?v=3IAlJSIjvH0
https://m.youtube.com/watch?v=TZ5a3gCCZYo
https://m.youtube.com/watch?v=hI9aN8ZG4vg
https://nullprogram.com/blog/2023/09/27/
https://m.youtube.com/watch?v=UYLHA_Ey8Ys

## Maybe useful stuff:

- [GNU Bash Manual](https://www.gnu.org/software/bash/manual/bash.html)
- [Git repo: charMstr](https://github.com/charMstr/minishell)
- [42 Minishell Functions](https://42-cursus.gitbook.io/guide/rank-03/minishell/functions) #brief explanation of all allowed functions

## Example File Structure:

- [tjensen42/42-minishell](https://github.com/tjensen42/42-minishell/tree/main/)

## Git usage:

### git fetch:

Downloads changes from the remote (new commits, branches, etc.) but doesn’t merge them into your local branch. Great for checking what's new without affecting your local work.

### git pull:

Does fetch + merge in one step — it downloads changes and immediately merges them into your current branch. If there are conflicts, you'll have to resolve them before proceeding.

### git merge:

Add changes from main to your branch. For example before pull request.
From main branch to your own branch: `git merge main`

### creating branch command flow:

git checkout main  
git pull  
git checkout -b branch-name
