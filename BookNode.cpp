#include "BookNode.h"

using namespace std;

// ═══════════════════════════════════════════════════════════════════
// DEFAULT CONSTRUCTOR (No parameters)
// ═══════════════════════════════════════════════════════════════════
BookNode::BookNode() {
    id = 0;
    type = INTERMEDIATE;         // Using enum value (no quotes needed)
    difficulty = EASY;           // Using enum value (no quotes needed)
    question = "";
    answer = "";
    next1 = nullptr;
    next2 = nullptr;
    visited = false;
    puzzleSolved = false;
}

// ═══════════════════════════════════════════════════════════════════
// PARAMETERIZED CONSTRUCTOR (With parameters)
// ═══════════════════════════════════════════════════════════════════
BookNode::BookNode(int bookId, BookType bookType, BookDifficulty bookDiff) {
    id = bookId;
    type = bookType;             // Assign enum value directly
    difficulty = bookDiff;       // Assign enum value directly
    question = "";
    answer = "";
    next1 = nullptr;
    next2 = nullptr;
    visited = false;
    puzzleSolved = false;
}

// ═══════════════════════════════════════════════════════════════════
// DISPLAY INFO FUNCTION
// Prints all book information to console
// ═══════════════════════════════════════════════════════════════════
void BookNode::displayInfo() {
    cout << "================================" << endl;
    cout << "Book ID: " << id << endl;
    cout << "Type: " << getTypeAsString() << endl;             // Convert enum to string
    cout << "Difficulty: " << getDifficultyAsString() << endl; // Convert enum to string
    cout << "Visited: " << (visited ? "Yes" : "No") << endl;
    cout << "Puzzle Solved: " << (puzzleSolved ? "Yes" : "No") << endl;
    
    if (question != "") {
        cout << "Question: " << question << endl;
    }
    
    cout << "Next1: " << (next1 != nullptr ? "Connected" : "None") << endl;
    cout << "Next2: " << (next2 != nullptr ? "Connected" : "None") << endl;
    cout << "================================" << endl;
}

// ═══════════════════════════════════════════════════════════════════
// HAS TWO PATHS FUNCTION
// Returns true if book has two paths (EASY book with next2)
// ═══════════════════════════════════════════════════════════════════
bool BookNode::hasTwoPaths() {
    // Compare enum values directly (no quotes needed)
    if (difficulty == EASY && next2 != nullptr) {
        return true;
    }
    return false;
}

// ═══════════════════════════════════════════════════════════════════
// GET TYPE AS STRING
// Converts BookType enum to string for display
// ═══════════════════════════════════════════════════════════════════
string BookNode::getTypeAsString() {
    // Switch statement to convert enum to string
    switch (type) {
        case ENTRANCE:
            return "ENTRANCE";
        case INTERMEDIATE:
            return "INTERMEDIATE";
        case FINAL:
            return "FINAL";
        default:
            return "UNKNOWN";
    }
}

// ═══════════════════════════════════════════════════════════════════
// GET DIFFICULTY AS STRING
// Converts BookDifficulty enum to string for display
// ═══════════════════════════════════════════════════════════════════
string BookNode::getDifficultyAsString() {
    // Switch statement to convert enum to string
    switch (difficulty) {
        case EASY:
            return "EASY";
        case HARD:
            return "HARD";
        default:
            return "UNKNOWN";
    }
}