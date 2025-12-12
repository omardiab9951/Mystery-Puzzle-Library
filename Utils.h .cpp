


#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <random>


struct Puzzle {
    std::string riddle;
    std::string answer;
    std::string category;
};


std::string trimString(const std::string& str);
std::string toLower(const std::string& str);
std::string sanitizeInput(const std::string& input);


std::vector<Puzzle> loadPuzzles(const std::string& filename);


int getRandomInt(int min, int max);
void shuffleVector(std::vector<Puzzle>& vec);


bool isValidPuzzle(const Puzzle& puzzle);

void printColored(const std::string& text, const std::string& color); 
#endif 