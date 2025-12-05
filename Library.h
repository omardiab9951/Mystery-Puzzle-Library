#pragma once
#include "BookNode.h"
#include <vector>
using namespace std;
class Library {
private:
	BookNode* entrances[4]; //storage for entrances books
	vector<BookNode*> intermediateBooks; //Stores Pointers.
	BookNode* finalBook; //storage for final book

	//Private Helper Functions
	void generateEntranceBooks();
	void generateIntermediateBooks();
	void generateFinalBook();
	void connectBooks();
	void deleteAllBooks();

public:
	Library();
	~Library(); 

	BookNode** getEntrances();
	BookNode* getFinalBook();

	//Optional:
	void printLibraryStructure();  // Debug: print all connections
	bool isValid();                // Check if library was built correctly
	int getIntermediateCount();  // Get number of intermediate books


};

