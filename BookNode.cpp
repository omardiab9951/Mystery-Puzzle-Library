#include "BookNode.h"

using namespace std;

// ═══════════════════════════════════════════════════════════════════
// DEFAULT CONSTRUCTOR (No parameters)
// ═══════════════════════════════════════════════════════════════════
BookNode::BookNode() {
    id = 0;
    type = INTERMEDIATE;         // Using enum value (no quotes needed)
    difficulty = EASY;           // Using enum value (no quotes needed)
    clues = nullptr;             // Initialize clue array pointer
    clueCount = 0;               // No clues initially
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
    clues = nullptr;             // Initialize clue array pointer
    clueCount = 0;               // No clues initially
    next1 = nullptr;
    next2 = nullptr;
    visited = false;
    puzzleSolved = false;
}

// ═══════════════════════════════════════════════════════════════════
// DESTRUCTOR
// Frees dynamically allocated clue array
// ═══════════════════════════════════════════════════════════════════
BookNode::~BookNode() {
    if (clues != nullptr) {
        delete[] clues;          // Free the clue array
        clues = nullptr;
    }
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
    
    // Display all clues
    if (clueCount > 0) {
        cout << "Clues:" << endl;
        for (int i = 0; i < clueCount; i++) {
            cout << "  Clue " << (i + 1) << ": " << clues[i].problem << endl;
        }
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

// ═══════════════════════════════════════════════════════════════════
// SET CLUES
// Allocates memory for the clue array based on book type/difficulty
// ═══════════════════════════════════════════════════════════════════
void BookNode::setClues(int count) {
    // Free old clues if they exist
    if (clues != nullptr) {
        delete[] clues;
    }
    
    clueCount = count;
    clues = new Clue[count];     // Allocate new array
    
    // Initialize with empty strings
    for (int i = 0; i < count; i++) {
        clues[i].problem = "";
        clues[i].solution = "";
    }
}

// ═══════════════════════════════════════════════════════════════════
// SET CLUE
// Sets a specific clue's problem and solution
// ═══════════════════════════════════════════════════════════════════
void BookNode::setClue(int index, string problem, string solution) {
    if (index >= 0 && index < clueCount) {
        clues[index].problem = problem;
        clues[index].solution = solution;
    }
}

// ═══════════════════════════════════════════════════════════════════
// GET CLUE
// Returns a specific clue by index
// ═══════════════════════════════════════════════════════════════════
Clue BookNode::getClue(int index) const {
    if (index >= 0 && index < clueCount) {
        return clues[index];
    }
    // Return empty clue if index is invalid
    Clue emptyClue;
    emptyClue.problem = "";
    emptyClue.solution = "";
    return emptyClue;
}

// ═══════════════════════════════════════════════════════════════════
// GET CLUE COUNT
// Returns the number of clues in this book
// ═══════════════════════════════════════════════════════════════════
int BookNode::getClueCount() const {
    return clueCount;
}
