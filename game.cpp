#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <set>

using namespace std;

// ============================================================
// PART 1: BASIC STRUCTURES
// ============================================================

// Clue structure - each clue has a problem and solution
struct Clue {
    string problem;    // The question
    string solution;   // The correct answer
};

// Book structure - each book is a node in the linked list
struct Book {
    // Basic book information
    int bookID;              // Book number
    string bookType;         // Book type: ENTRANCE, INTERMEDIATE, FINAL
    string difficulty;       // Difficulty: EASY or HARD (for intermediate books only)

    // Pointers for game paths
    Book* next1;             // First path (or the only path for hard books)
    Book* next2;             // Second path (for easy books only)

    // Clues associated with the book
    Clue clue1;              // First clue (or the only clue for hard books)
    Clue clue2;              // Second clue (for easy books only)

    // Book status
    bool visited;            // Has the book been visited?
    bool cleared;            // Have the book's clues been successfully solved?

    // Administrative pointer for temporary linking during library creation
    Book* nextInList;        // Pointer to next book in temporary list

    // Constructor - initialize book with default values
    Book(int id, string type, string diff = "NONE") {
        bookID = id;
        bookType = type;
        difficulty = diff;
        next1 = nullptr;
        next2 = nullptr;
        visited = false;
        cleared = false;
        nextInList = nullptr;
    }
};

// ============================================================
// PART 2: LINKED LIST MANAGER
// ============================================================

// Linked list to manage books during creation only
struct BookList {
    Book* head;    // Pointer to first book in list
    Book* tail;    // Pointer to last book in list
    int count;     // Number of books in list

    // Constructor
    BookList() {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    // Add book at end of list
    void addBook(Book* book) {
        if (head == nullptr) {
            // List is empty - book becomes first and last
            head = book;
            tail = book;
        }
        else {
            // Link new book to last book
            tail->nextInList = book;
            tail = book;
        }
        book->nextInList = nullptr;
        count++;
    }

    // Get book at specific position
    Book* getBookAt(int position) {
        // Verify position is valid
        if (position < 0 || position >= count) {
            return nullptr;
        }

        // Traverse list until reaching desired position
        Book* current = head;
        for (int i = 0; i < position; i++) {
            current = current->nextInList;
        }
        return current;
    }

    // Shuffle list randomly
    void shuffleBooks() {
        if (count <= 1) return;  // If one book or less, nothing to shuffle

        // Use Fisher-Yates shuffle algorithm
        for (int i = count - 1; i > 0; i--) {
            // Choose random position
            int randomPosition = rand() % (i + 1);

            // Get both books
            Book* book1 = getBookAt(i);
            Book* book2 = getBookAt(randomPosition);

            // Swap book contents (not pointers)
            if (book1 != nullptr && book2 != nullptr && book1 != book2) {
                swap(book1->bookID, book2->bookID);
                swap(book1->bookType, book2->bookType);
                swap(book1->difficulty, book2->difficulty);
                swap(book1->next1, book2->next1);
                swap(book1->next2, book2->next2);
                swap(book1->clue1, book2->clue1);
                swap(book1->clue2, book2->clue2);
                swap(book1->visited, book2->visited);
                swap(book1->cleared, book2->cleared);
            }
        }
    }
};

// ============================================================
// PART 3: CLUE DATABASE
// ============================================================

struct ClueDatabase {
    // Easy clues
    Clue easyClues[8];
    int easyCount;
    int easyIndex;

    // Hard clues
    Clue hardClues[6];
    int hardCount;
    int hardIndex;

    // Final clues - very hard!
    Clue finalClues[2];
    int finalCount;

    // Constructor - initialize clues
    ClueDatabase() {
        // Initialize counters
        easyCount = 8;
        hardCount = 6;
        finalCount = 2;
        easyIndex = 0;
        hardIndex = 0;

        // Fill easy clues
        easyClues[0] = { "What has keys but no locks?", "keyboard" };
        easyClues[1] = { "What gets wetter as it dries?", "towel" };
        easyClues[2] = { "What has a head and tail but no body?", "coin" };
        easyClues[3] = { "What can travel around the world while staying in a corner?", "stamp" };
        easyClues[4] = { "What has hands but cannot clap?", "clock" };
        easyClues[5] = { "What comes once in a minute, twice in a moment, but never in a thousand years?", "m" };
        easyClues[6] = { "What belongs to you but others use it more?", "name" };
        easyClues[7] = { "What has cities but no houses?", "map" };

        // Fill hard clues
        hardClues[0] = { "I speak without a mouth and hear without ears. I have no body but come alive with wind. What am I?", "echo" };
        hardClues[1] = { "The more you take, the more you leave behind. What are they?", "footsteps" };
        hardClues[2] = { "What can run but never walks, has a mouth but never talks?", "river" };
        hardClues[3] = { "I have branches but no fruit, trunk or leaves. What am I?", "bank" };
        hardClues[4] = { "What breaks yet never falls, and what falls yet never breaks?", "day" };
        hardClues[5] = { "Forward I am heavy, backward I am not. What am I?", "ton" };

        // Fill final clues - the hardest!
        finalClues[0] = { "I am the beginning of eternity, the end of time and space. I am essential to creation, and I surround every place. What am I?", "e" };
        finalClues[1] = { "What walks on four legs in the morning, two legs at noon, and three legs in the evening?", "human" };

        // Shuffle clues randomly
        shuffleEasyClues();
        shuffleHardClues();
    }

    // Shuffle easy clues
    void shuffleEasyClues() {
        for (int i = easyCount - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(easyClues[i], easyClues[j]);
        }
    }

    // Shuffle hard clues
    void shuffleHardClues() {
        for (int i = hardCount - 1; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(hardClues[i], hardClues[j]);
        }
    }

    // Get next easy clue
    Clue getNextEasyClue() {
        Clue clue = easyClues[easyIndex % easyCount];
        easyIndex++;
        return clue;
    }

    // Get next hard clue
    Clue getNextHardClue() {
        Clue clue = hardClues[hardIndex % hardCount];
        hardIndex++;
        return clue;
    }

    // Get final clue
    Clue getFinalClue(int index) {
        return finalClues[index % finalCount];
    }
};

// ============================================================
// PART 4: HELPER FUNCTIONS
// ============================================================

// Create new book
Book* createNewBook(int id, string type, string difficulty = "NONE") {
    return new Book(id, type, difficulty);
}

// Display book information
void showBook(Book* book) {
    cout << "\n+========================================================+" << endl;
    cout << "|            BOOK #" << book->bookID;
    if (book->bookID < 10) cout << "  ";
    else if (book->bookID < 100) cout << " ";
    cout << "                                    |" << endl;
    cout << "+========================================================+" << endl;
    cout << "|  Type: " << book->bookType;

    // Add spaces for alignment
    int spaces = 48 - book->bookType.length();
    for (int i = 0; i < spaces; i++) cout << " ";
    cout << "|" << endl;

    // Display difficulty for intermediate books
    if (book->bookType == "INTERMEDIATE") {
        cout << "|  Difficulty: " << book->difficulty;
        spaces = 36 - book->difficulty.length();
        for (int i = 0; i < spaces; i++) cout << " ";
        cout << "|" << endl;
    }

    // Display book status
    if (book->cleared) {
        cout << "|  Status: [CLEARED]                                      |" << endl;
    }
    else if (book->visited) {
        cout << "|  Status: [VISITED]                                      |" << endl;
    }

    cout << "+========================================================+" << endl;
}

// Solve specific clue
bool solveClue(Book* currentBook, int clueNumber) {
    // Select appropriate clue
    Clue* selectedClue;
    if (clueNumber == 1) {
        selectedClue = &currentBook->clue1;
    }
    else {
        selectedClue = &currentBook->clue2;
    }

    // Display clue
    cout << "\n[?] RIDDLE: " << selectedClue->problem << endl;
    cout << "Your answer: ";

    // Read player's answer
    string playerAnswer;
    getline(cin, playerAnswer);

    // Convert answer and solution to lowercase for comparison
    string correctAnswer = selectedClue->solution;
    transform(playerAnswer.begin(), playerAnswer.end(), playerAnswer.begin(), ::tolower);
    transform(correctAnswer.begin(), correctAnswer.end(), correctAnswer.begin(), ::tolower);

    // Check answer
    if (playerAnswer == correctAnswer) {
        cout << "[+] Correct! The book reveals its secrets..." << endl;
        return true;
    }
    else {
        cout << "[-] Incorrect. The correct answer was: " << selectedClue->solution << endl;
        return false;
    }
}

// ============================================================
// PART 5: LIBRARY GENERATION
// ============================================================

// Assign clues to books
void assignCluesToBooks(BookList& bookList, ClueDatabase& clueDB, Book* final1, Book* final2) {
    // Start from first book in list
    Book* currentBook = bookList.head;

    // Go through all books
    while (currentBook != nullptr) {
        if (currentBook->difficulty == "EASY") {
            // Easy books need two clues
            currentBook->clue1 = clueDB.getNextEasyClue();
            currentBook->clue2 = clueDB.getNextEasyClue();
        }
        else {
            // Hard books need one clue
            currentBook->clue1 = clueDB.getNextHardClue();
        }

        // Move to next book
        currentBook = currentBook->nextInList;
    }

    // Add final clues to final books
    final1->clue1 = clueDB.getFinalClue(0);
    final2->clue1 = clueDB.getFinalClue(1);
}

// Connect books randomly
void connectBooks(BookList& bookList, Book* entrances[], Book* final1, Book* final2) {
    // Ensure books exist
    if (bookList.count == 0) return;

    // Step 1: Connect entrance books to first intermediate books
    Book* current = bookList.head;
    for (int i = 0; i < 4; i++) {
        if (current != nullptr) {
            entrances[i]->next1 = current;
            if (i < 3) {
                current = current->nextInList;
            }
        }
    }

    // Step 2: Connect intermediate books to each other
    current = bookList.head;
    int position = 0;
    int totalBooks = bookList.count;

    while (current != nullptr) {
        // Get next books
        Book* nextBook = current->nextInList;
        Book* nextNextBook = nullptr;
        if (nextBook != nullptr) {
            nextNextBook = nextBook->nextInList;
        }

        if (current->difficulty == "EASY") {
            // Easy books have two paths
            if (position < totalBooks - 3) {
                // Middle of list: connect to next two books
                current->next1 = nextBook;
                current->next2 = nextNextBook;
            }
            else if (position < totalBooks - 1) {
                // Near end: one path to next book, one path to final
                current->next1 = nextBook;
                current->next2 = (rand() % 2 == 0) ? final1 : final2;
            }
            else {
                // Last book: both paths to finals
                current->next1 = final1;
                current->next2 = final2;
            }
        }
        else {
            // Hard books have one path
            if (position < totalBooks - 1) {
                current->next1 = nextBook;
            }
            else {
                current->next1 = (rand() % 2 == 0) ? final1 : final2;
            }
        }

        // Move to next book
        current = current->nextInList;
        position++;
    }
}

// Build complete library
void buildLibrary(Book* entrances[], Book*& final1, Book*& final2) {
    cout << "\n=== GENERATING MYSTERY LIBRARY ===" << endl;

    // Create 4 entrance books
    cout << "\nCreating entrance books..." << endl;
    for (int i = 0; i < 4; i++) {
        entrances[i] = createNewBook(i + 1, "ENTRANCE");
        cout << "  [+] Entrance Book #" << (i + 1) << endl;
    }

    // Create 2 final books
    cout << "\nCreating final books..." << endl;
    final1 = createNewBook(100, "FINAL");
    final2 = createNewBook(101, "FINAL");
    cout << "  [+] Final Book #100 (The Ancient Tome)" << endl;
    cout << "  [+] Final Book #101 (The Forbidden Scroll)" << endl;

    // Create random number of intermediate books (8-15)
    int numberOfBooks = 8 + rand() % 8;
    cout << "\nGenerating " << numberOfBooks << " intermediate books..." << endl;

    // Create temporary list for books
    BookList intermediateBooks;
    ClueDatabase clueDatabase;

    for (int i = 0; i < numberOfBooks; i++) {
        // Choose random difficulty
        string difficulty = (rand() % 2 == 0) ? "EASY" : "HARD";

        // Create book and add to list
        Book* newBook = createNewBook(10 + i, "INTERMEDIATE", difficulty);
        intermediateBooks.addBook(newBook);
        cout << "  [+] Book #" << (10 + i) << " - " << difficulty << endl;
    }

    // Assign clues to books (including final books)
    cout << "\nAssigning riddles to books..." << endl;
    assignCluesToBooks(intermediateBooks, clueDatabase, final1, final2);

    // Shuffle books randomly
    cout << "Shuffling books for random connections..." << endl;
    intermediateBooks.shuffleBooks();

    // Connect books
    cout << "Connecting books..." << endl;
    connectBooks(intermediateBooks, entrances, final1, final2);

    cout << "\n=== LIBRARY GENERATION COMPLETE ===" << endl << endl;
}

// ============================================================
// PART 6: GAME PLAY
// ============================================================

void startGame(Book* entrances[]) {
    // Display welcome message
    cout << "\n+===========================================================+" << endl;
    cout << "|     WELCOME TO THE MYSTERY LIBRARY PUZZLE GAME           |" << endl;
    cout << "+===========================================================+" << endl;
    cout << "\nYou stand before four ancient entrance books." << endl;
    cout << "Each leads to a different path through the library." << endl;
    cout << "Solve the riddles to progress. Reach a final book to win!" << endl;

    // Choose entrance book
    cout << "\n[>] Choose your starting book (1-4): ";
    int choice;
    cin >> choice;
    cin.ignore();

    // Verify choice is valid
    while (choice < 1 || choice > 4) {
        cout << "Invalid choice. Choose 1-4: ";
        cin >> choice;
        cin.ignore();
    }

    // Start from chosen book
    Book* currentBook = entrances[choice - 1];
    currentBook->visited = true;
    int stepsCount = 0;

    // Navigate through books
    while (currentBook != nullptr) {
        stepsCount++;
        showBook(currentBook);

        // Check if final book is reached
        if (currentBook->bookType == "FINAL") {
            cout << "\n*** YOU'VE REACHED THE FINAL BOOK! ***" << endl;
            if (currentBook->bookID == 100) {
                cout << "This is the Ancient Tome - the ultimate test awaits!" << endl;
            }
            else {
                cout << "This is the Forbidden Scroll - prepare for the ultimate challenge!" << endl;
            }

            cout << "\n[!] To unlock its secrets, you must solve the FINAL RIDDLE!" << endl;
            cout << "This is your last challenge. Good luck!" << endl;

            // Solve final clue
            bool solvedFinal = solveClue(currentBook, 1);

            if (solvedFinal) {
                // Victory!
                currentBook->cleared = true;
                cout << "\n+========================================================+" << endl;
                cout << "|           *** CONGRATULATIONS! ***                     |" << endl;
                cout << "+========================================================+" << endl;
                cout << "\nYou've unlocked the ";
                if (currentBook->bookID == 100) {
                    cout << "Ancient Tome!" << endl;
                }
                else {
                    cout << "Forbidden Scroll!" << endl;
                }
                cout << "You completed the mystery in " << stepsCount << " steps!" << endl;

                // Ending message
                if (currentBook->bookID == 100) {
                    cout << "\n[*] The Ancient Tome reveals the secret of eternal wisdom..." << endl;
                    cout << "You discover the formula for infinite knowledge!" << endl;
                    cout << "The library acknowledges you as a true Master of Riddles!" << endl;
                }
                else {
                    cout << "\n[*] The Forbidden Scroll grants you forbidden knowledge..." << endl;
                    cout << "You learn the dark arts of the ancient librarians!" << endl;
                    cout << "The shadows bow before your intellectual prowess!" << endl;
                }
            }
            else {
                // Defeat
                cout << "\n[X] You failed the final riddle. The book remains locked forever." << endl;
                cout << "You were so close to victory... GAME OVER." << endl;
            }
            break;
        }

        // Handle entrance books
        if (currentBook->bookType == "ENTRANCE") {
            cout << "\nThis entrance book guides you forward..." << endl;
            cout << "Press Enter to continue...";
            cin.get();
            currentBook = currentBook->next1;
            if (currentBook != nullptr) {
                currentBook->visited = true;
            }
            continue;
        }

        // Handle intermediate books
        if (currentBook->bookType == "INTERMEDIATE") {
            if (currentBook->difficulty == "EASY") {
                // Easy books: two clues and two paths
                cout << "\nThis book offers two paths. Choose wisely!" << endl;

                // Display available paths
                cout << "\nAvailable paths:" << endl;
                if (currentBook->next1 != nullptr) {
                    cout << "  1) Path 1 (leads to Book #" << currentBook->next1->bookID << ")" << endl;
                }
                if (currentBook->next2 != nullptr) {
                    cout << "  2) Path 2 (leads to Book #" << currentBook->next2->bookID << ")" << endl;
                }

                // Choose path
                cout << "\n[>] Which path will you take? (1 or 2): ";
                int pathChoice;
                cin >> pathChoice;
                cin.ignore();

                // Verify choice is valid
                while (pathChoice != 1 && pathChoice != 2) {
                    cout << "Invalid choice. Choose 1 or 2: ";
                    cin >> pathChoice;
                    cin.ignore();
                }

                // Solve clue for chosen path
                cout << "\n[!] To proceed on Path " << pathChoice << ", solve this riddle:" << endl;
                bool solved = solveClue(currentBook, pathChoice);

                if (!solved) {
                    cout << "\n[X] You failed the riddle. The path remains closed. GAME OVER." << endl;
                    break;
                }

                // Move to next book
                currentBook->cleared = true;
                if (pathChoice == 1) {
                    currentBook = currentBook->next1;
                }
                else {
                    currentBook = currentBook->next2;
                }

            }
            else {
                // Hard books: one clue and one path
                cout << "\nThis book blocks your way with a difficult riddle." << endl;
                bool solved = solveClue(currentBook, 1);

                if (!solved) {
                    cout << "\n[X] You failed the riddle. GAME OVER." << endl;
                    break;
                }

                currentBook->cleared = true;
                cout << "\nThe path opens before you..." << endl;
                cout << "Press Enter to continue...";
                cin.get();
                currentBook = currentBook->next1;
            }

            // Update visit status
            if (currentBook != nullptr) {
                currentBook->visited = true;
            }
        }
    }

    cout << "\n=== GAME COMPLETE ===" << endl;
}

// ============================================================
// PART 7: MEMORY MANAGEMENT
// ============================================================

// Delete books recursively
void deleteBookRecursive(Book* book, set<Book*>& deletedBooks) {
    // Stop if pointer is null or book already deleted
    if (book == nullptr || deletedBooks.count(book) > 0) {
        return;
    }

    // Add book to deleted list
    deletedBooks.insert(book);

    // Delete connected books first
    deleteBookRecursive(book->next1, deletedBooks);
    deleteBookRecursive(book->next2, deletedBooks);

    // Delete current book
    delete book;
}

// Delete entire library
void cleanupLibrary(Book* entrances[], int count) {
    set<Book*> deletedBooks;

    // Delete all books starting from entrance books
    for (int i = 0; i < count; i++) {
        deleteBookRecursive(entrances[i], deletedBooks);
    }

    cout << "\n[!] Library memory cleaned. " << deletedBooks.size() << " books deleted." << endl;
}

// ============================================================
// PART 8: MAIN FUNCTION
// ============================================================

int main() {
    // Initialize random number generator
    srand(static_cast<unsigned>(time(0)));

    // Create array for entrance books
    Book* entranceBooks[4];

    // Create variables for final books
    Book* finalBook1 = nullptr;
    Book* finalBook2 = nullptr;

    // Build library
    buildLibrary(entranceBooks, finalBook1, finalBook2);

    // Start game
    startGame(entranceBooks);

    // Clean up memory
    cleanupLibrary(entranceBooks, 4);

    return 0;
}
