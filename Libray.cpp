#include "Library.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

Library::Library() {
    finalBook = nullptr;
    for (int i = 0; i < 4; i++) {
        entrances[i] = nullptr;
    }

    srand(time(0));

    generateEntranceBooks();
    generateIntermediateBooks();
    generateFinalBook();
    connectBooks();
}


Library::~Library() {
    for (int i = 0; i < 4; i++) {
        if (entrances[i] != nullptr) {
            delete entrances[i];
            entrances[i] = nullptr;
        }
    }

    for (int i = 0; i < intermediateBooks.size(); i++) {
        if (intermediateBooks[i] != nullptr) {
            delete intermediateBooks[i];
        }
    }
    intermediateBooks.clear();

    if (finalBook != nullptr) {
        delete finalBook;
        finalBook = nullptr;
    }
}

void Library::generateEntranceBooks() {
    string titles[4] = { "Ancient Tome", "Dusty Scroll", "Leather Journal", "Stone Tablet" };
    string puzzles[4] = {
        "I speak without a mouth and hear without ears. What am I?",
        "What has keys but no locks?",
        "What can travel around the world while staying in a corner?",
        "I have cities but no houses, forests but no trees. What am I?"
    };
    string answers[4] = { "echo", "piano", "stamp", "map" };

    for (int i = 0; i < 4; i++) {
        BookNode* newBook = new BookNode();
        newBook->type = ENTRANCE;
        newBook->title = titles[i];
        newBook->puzzle = puzzles[i];
        newBook->answer = answers[i];
        newBook->next1 = nullptr;
        newBook->next2 = nullptr;

        entrances[i] = newBook;
    }
}

void Library::generateIntermediateBooks() {
    int numBooks = rand() % 6 + 10;  

    string puzzles[15] = {
        "What gets wetter the more it dries?",
        "What has hands but cannot clap?",
        "What has a head and tail but no body?",
        "What runs but never walks?",
        "What has many teeth but cannot bite?",
        "What can fill a room but takes no space?",
        "What goes up but never comes down?",
        "What has one eye but cannot see?",
        "What has legs but doesn't walk?",
        "What breaks but never falls?",
        "What falls but never breaks?",
        "The more you take, the more you leave behind. What am I?",
        "What belongs to you but others use it more?",
        "What comes once in a minute, twice in a moment, but never in a thousand years?",
        "What can you catch but never throw?"
    };

    string answers[15] = {
        "towel", "clock", "coin", "water", "comb",
        "light", "age", "needle", "table", "day",
        "night", "footsteps", "name", "m", "cold"
    };

    for (int i = 0; i < numBooks; i++) {
        BookNode* newBook = new BookNode();

        // Randomly assign EASY or HARD
        if (rand() % 2 == 0) {
            newBook->type = EASY;
        }
        else {
            newBook->type = HARD;
        }

        newBook->title = "Mysterious Volume " + to_string(i + 1);
        newBook->puzzle = puzzles[i];
        newBook->answer = answers[i];
        newBook->next1 = nullptr;
        newBook->next2 = nullptr;

        intermediateBooks.push_back(newBook);
    }
}

void Library::generateFinalBook() {
    BookNode* newBook = new BookNode();
    newBook->type = FINAL;
    newBook->title = "The Ultimate Mystery";
    newBook->puzzle = "What is the beginning of eternity, the end of time and space, the beginning of every end, and the end of every place?";
    newBook->answer = "e";
    newBook->next1 = nullptr;
    newBook->next2 = nullptr;

    finalBook = newBook;
}

void Library::connectBooks() {
    int totalIntermediate = intermediateBooks.size();

    for (int i = 0; i < 4; i++) {
        int randomIndex = rand() % 5; 
        if (randomIndex >= totalIntermediate) {
            randomIndex = 0;
        }
        entrances[i]->next1 = intermediateBooks[randomIndex];
    }

    for (int i = 0; i < totalIntermediate - 3; i++) {
        BookNode* currentBook = intermediateBooks[i];

        int range = totalIntermediate - i - 1;
        if (range <= 0) range = 1;
        int randomNext = i + 1 + (rand() % range);

        if (randomNext >= totalIntermediate) {
            randomNext = totalIntermediate - 1;
        }

        currentBook->next1 = intermediateBooks[randomNext];

        if (currentBook->type == EASY) {
            int randomNext2 = i + 1 + (rand() % range);
            if (randomNext2 >= totalIntermediate) {
                randomNext2 = totalIntermediate - 1;
            }
            if (randomNext2 == randomNext && randomNext2 > i + 1) {
                randomNext2--;
            }
            currentBook->next2 = intermediateBooks[randomNext2];
        }
    }

    int startLast = totalIntermediate - 3;
    if (startLast < 0) startLast = 0;

    for (int i = startLast; i < totalIntermediate; i++) {
        BookNode* currentBook = intermediateBooks[i];
        currentBook->next1 = finalBook;

        if (currentBook->type == EASY) {
            currentBook->next2 = finalBook;
        }
    }
}

void Library::deleteAllBooks() {}

BookNode** Library::getEntrances() {
    return entrances;
}

BookNode* Library::getFinalBook() {
    return finalBook;
}

int Library::getIntermediateCount() {
    return intermediateBooks.size();
}

void Library::printLibraryStructure() {
    cout << "\n LIBRARY STRUCTURE: " << endl;

    cout << "\nENTRANCES:" << endl;
    for (int i = 0; i < 4; i++) {
        cout << "  [" << i << "] " << entrances[i]->title << endl;
        if (entrances[i]->next1 != nullptr) {
            cout << "      -> " << entrances[i]->next1->title << endl;
        }
    }

    cout << "\nINTERMEDIATE BOOKS: (" << intermediateBooks.size() << " total)" << endl;
    for (int i = 0; i < intermediateBooks.size(); i++) {
        BookNode* book = intermediateBooks[i];
        cout << "  [" << i << "] " << book->title;

        if (book->type == EASY) {
            cout << " (EASY)" << endl;
        }
        else {
            cout << " (HARD)" << endl;
        }

        if (book->next1 != nullptr) {
            cout << "      next1-> " << book->next1->title << endl;
        }
        if (book->next2 != nullptr) {
            cout << "      next2-> " << book->next2->title << endl;
        }
    }

    cout << "\nFINAL BOOK:" << endl;
    cout << "  " << finalBook->title << endl;
}

bool Library::isValid() {
    for (int i = 0; i < 4; i++) {
        if (entrances[i] == nullptr) {
            return false;
        }
        if (entrances[i]->next1 == nullptr) {
            return false;
        }
    }

    if (finalBook == nullptr) {
        return false;
    }

    for (int i = 0; i < intermediateBooks.size(); i++) {
        BookNode* book = intermediateBooks[i];

        if (book == nullptr) {
            return false;
        }

        if (book->next1 == nullptr) {
            return false;
        }

        if (book->type == EASY && book->next2 == nullptr) {
            return false;
        }
    }

    return true;
}