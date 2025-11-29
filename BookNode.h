#ifndef BOOKNODE_H
#define BOOKNODE_H

#include <string>
#include <iostream>

using namespace std;

// ═══════════════════════════════════════════════════════════════════
// ENUMS (Fixed types for book properties)
// ═══════════════════════════════════════════════════════════════════

// Book Type Enum
// The book can be one of 3 types
enum BookType {
    ENTRANCE,      // Starting book (4 books to choose from)
    INTERMEDIATE,  // Middle books (main part of the library)
    FINAL          // The final book (goal)
};

// Book Difficulty Enum
// Determines how many paths the book has
enum BookDifficulty {
    EASY,    // Has 2 paths (next1 and next2) - player chooses
    HARD     // Has 1 path (next1 only) - player is forced
};

// ═══════════════════════════════════════════════════════════════════
// BOOKNODE STRUCT
// Represents a single book in the library
// ═══════════════════════════════════════════════════════════════════

struct BookNode {
    // ═══════════════════════════════════════
    // BASIC DATA
    // ═══════════════════════════════════════
    int id;                      // Book ID number (example: 101, 102, 103...)
    BookType type;               // Book type (ENTRANCE, INTERMEDIATE, or FINAL)
    BookDifficulty difficulty;   // Book difficulty (EASY or HARD)
    
    // ═══════════════════════════════════════
    // PUZZLE DATA
    // ═══════════════════════════════════════
    string question;             // The question/puzzle
    string answer;               // The correct answer
    
    // ═══════════════════════════════════════
    // POINTERS (Paths to next books)
    // ═══════════════════════════════════════
    BookNode* next1;             // First path (exists in all books)
    BookNode* next2;             // Second path (exists only in EASY books)
    
    // ═══════════════════════════════════════
    // BOOK STATE
    // ═══════════════════════════════════════
    bool visited;                // Has the player visited this book?
    bool puzzleSolved;           // Has the player solved the puzzle?
    
    // ═══════════════════════════════════════
    // CONSTRUCTORS
    // ═══════════════════════════════════════
    BookNode();                                                      // Default constructor
    BookNode(int bookId, BookType bookType, BookDifficulty bookDiff); // Constructor with parameters
    
    // ═══════════════════════════════════════
    // HELPER FUNCTIONS
    // ═══════════════════════════════════════
    void displayInfo();          // Display book information
    bool hasTwoPaths();          // Does the book have two paths?
    
    // Convert enums to strings (for display)
    string getTypeAsString();         // Convert BookType to string
    string getDifficultyAsString();   // Convert BookDifficulty to string
};

#endif