#include "Utils.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <random>
#include <utility>


std::string trimString(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\f\v");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r\f\v");
    return str.substr(first, (last - first + 1));
}


std::string toLower(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}


std::string sanitizeInput(const std::string& input) {
    return toLower(trimString(input));
}

std::vector<Puzzle> loadPuzzles(const std::string& filename) {
    std::vector<Puzzle> puzzles;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open puzzles file: " << filename << std::endl;
        return puzzles;
    }
    std::string line, currentCategory;
    while (std::getline(file, line)) {
        line = trimString(line);
        if (line.empty()) continue;
        if (line[0] == '[' && line.back() == ']') {
            currentCategory = line.substr(1, line.size() - 2);
            continue;
        }
        size_t riddlePos = line.find("Riddle: ");
        size_t answerPos = line.find(" | Answer: ");
        if (riddlePos != std::string::npos && answerPos != std::string::npos) {
            std::string riddle = trimString(line.substr(riddlePos + 8, answerPos - (riddlePos + 8)));
            std::string answer = trimString(line.substr(answerPos + 11));
            puzzles.push_back({riddle, answer, currentCategory});
        }
    }
    file.close();
    return puzzles;
}


int getRandomInt(int min, int max) {
    static std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}


void shuffleVector(std::vector<Puzzle>& vec) {
    static std::mt19937 gen(std::random_device{}());
    std::shuffle(vec.begin(), vec.end(), gen);
}


bool isValidPuzzle(const Puzzle& puzzle) {
    return !puzzle.riddle.empty() && !puzzle.answer.empty();
}


void printColored(const std::string& text, const std::string& color) {
    std::string code;
    if (color == "red") code = "\033[31m";
    else if (color == "green") code = "\033[32m";
    else if (color == "yellow") code = "\033[33m";
    else code = "\033[0m"; // Reset
    std::cout << code << text << "\033[0m";
}