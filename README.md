<div align="center">

<img src="https://img.shields.io/badge/Domain-Data%20Structures%20%26%20Algorithms-2E4057?style=for-the-badge" />
<img src="https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" />
<img src="https://img.shields.io/badge/Type-Group%20Project-8A2BE2?style=for-the-badge" />
<img src="https://img.shields.io/badge/Course-DSA-228B22?style=for-the-badge" />

# 🔍 Mystery Puzzle Library
### A C++ Puzzle Game Built on Core Data Structures

*A mystery-themed puzzle game that puts Linked Lists, Stacks, and Queues to work — demonstrating data structures through interactive gameplay rather than textbook exercises.*

[![Author](https://img.shields.io/badge/Omar%20Diab-Game%20Logic%20%26%20DS%20Implementation-0A66C2?style=flat-square&logo=linkedin)](https://www.linkedin.com/in/omar9951)
[![GitHub](https://img.shields.io/badge/GitHub-omardiab9951-181717?style=flat-square&logo=github)](https://github.com/omardiab9951)

</div>

---

## 🔍 Overview

Mystery Puzzle Library is a **C++ console puzzle game** developed as a Data Structures & Algorithms course group project at **ElSewedy University of Technology — Polytechnic of Egypt**.

Rather than demonstrating data structures in isolation, this project embeds them directly into the mechanics of a playable puzzle game — making the role of each structure visible and meaningful. Players navigate through a series of mystery puzzles where the underlying game logic is powered by **Linked Lists**, **Stacks**, and **Queues**, applied to manage game state, puzzle sequencing, and player progression.

---

## 🧩 Gameplay

The player enters a mystery puzzle library and works through a collection of puzzles to escape or progress. Each puzzle presents a challenge that must be solved before the next one unlocks. The game tracks player state, manages puzzle order, and handles move history — all driven by the data structures underneath.

---

## 🏗️ Data Structures Used

| Structure | Role in the Game |
|---|---|
| **Linked List** | Stores and traverses the puzzle library — each puzzle is a node linked to the next |
| **Stack** | Manages move history — enables undo functionality and tracks the player's path |
| **Queue** | Controls puzzle sequencing — puzzles are enqueued and dequeued as the player progresses |

---

## 🧠 DSA Concepts Demonstrated

This project puts the following Data Structures & Algorithms fundamentals into practice:

- **Linked List traversal** — navigating a dynamically linked chain of puzzle nodes
- **Stack (LIFO)** — push/pop operations for move tracking and backtracking
- **Queue (FIFO)** — enqueue/dequeue operations for ordered puzzle progression
- **Dynamic memory management** — manual allocation and deallocation in C++
- **Pointer manipulation** — direct use of pointers for node linking and traversal
- **Game state management** — maintaining and updating player progress across structures

---

## 🚀 Getting Started

### Prerequisites
- A C++ compiler: **g++**, **MinGW**, or any C++11-compatible compiler
- Terminal / Command Prompt

### Compile & Run

```bash
# Clone the repository
git clone https://github.com/omardiab9951/Mystery-Puzzle-Library.git
cd Mystery-Puzzle-Library

# Compile
g++ game.cpp -o mystery_puzzle

# Run
./mystery_puzzle         # Linux / macOS
mystery_puzzle.exe       # Windows
```

---

## 📁 Repository Structure

```
Mystery-Puzzle-Library/
│
├── game.cpp              — Full game source code (logic + DS implementation)
└── Technical Report.pdf  — Project report & technical documentation
```

---

## 📄 Technical Report

The full project specification, data structure design decisions, and technical documentation are included in the repository:

📎 [`Technical Report.pdf`](./Technical%20Report.pdf)

---

## 👥 Team & Roles

This is a group project developed collaboratively as part of the Data Structures & Algorithms course.

| Contributor | Role |
|---|---|
| **Omar Diab** | Game logic & core data structure implementation |
| *Team Members* | Puzzle design · Testing · Documentation |

---

## 👤 Author (Omar Diab)

**Data Science & AI Student — ElSewedy University of Technology, Polytechnic of Egypt**

[![LinkedIn](https://img.shields.io/badge/LinkedIn-omar9951-0A66C2?style=flat-square&logo=linkedin)](https://www.linkedin.com/in/omar9951)
[![GitHub](https://img.shields.io/badge/GitHub-omardiab9951-181717?style=flat-square&logo=github)](https://github.com/omardiab9951)
[![Email](https://img.shields.io/badge/Email-omarkamaldiab9951@gmail.com-EA4335?style=flat-square&logo=gmail)](mailto:omarkamaldiab9951@gmail.com)

---

## 📄 License

This project is open-source and available under the [MIT License](LICENSE).

---

<div align="center">

*Not just studying data structures — building with them.*

⭐ If this project helped you, consider giving it a star!

</div>
