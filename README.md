# ✅ C++ To-Do List Manager

A simple, file-persistent console application for managing tasks — built in C++ with no external dependencies.

---

## Features

- **Add** tasks with a title and description
- **View** all tasks in a formatted table
- **Read** full details of a specific task by ID
- **Update** title, description, or toggle status (Pending ↔ Done)
- **Delete** tasks by ID
- **Persistent storage** — tasks are saved to `tasks.txt` and reloaded on every run

---

## Getting Started

### Prerequisites

- A C++ compiler supporting C++11 or later (e.g. `g++`, `clang++`, MSVC)

### Compile

```bash
g++ -o todo todo.cpp
```

### Run

```bash
# Linux / macOS
./todo

# Windows
todo.exe
```

---

## Usage

When you launch the app, you'll see a menu:

```
------------------------------------------------------------
         ✅  C++ To-Do List Manager
------------------------------------------------------------

  1. View All Tasks
  2. Add Task
  3. Read Task (by ID)
  4. Update Task
  5. Delete Task
  6. Exit

  Choose an option:
```

### 1 — View All Tasks

Displays a table of all tasks with their ID, title, description, and status.

### 2 — Add Task

Prompts you for a title and description. New tasks are automatically assigned an ID and start with the status **Pending**.

### 3 — Read Task (by ID)

Enter a task ID to see its full details — useful when titles or descriptions are long.

### 4 — Update Task

Enter a task ID, then optionally change the title, description, or toggle the status between **Pending** and **Done**. Press Enter on any field to keep the current value.

### 5 — Delete Task

Enter a task ID to permanently remove it. Deleted IDs are not reused.

### 6 — Exit

Quits the program. All changes are already saved — no confirmation needed.

---

## Data Storage

Tasks are saved to a plain-text file called `tasks.txt` in the same directory as the executable. The file is created automatically on first use.

Example `tasks.txt` content:

```
1
Buy groceries
Milk, eggs, and bread
Pending
---
2
Read C++ book
Chapters 4 and 5
Done
---
```

> You can back up or copy this file to transfer your task list between machines.

---

## Project Structure

```
.
├── todo.cpp       # Full source code (single file)
├── tasks.txt      # Auto-generated task data (created on first run)
└── README.md      # This file
```

---

## Building on Windows (MinGW)

If you're using MinGW on Windows:

```bash
g++ -o todo.exe todo.cpp
todo.exe
```

---

## License

This project is free to use and modify for personal or educational purposes.
