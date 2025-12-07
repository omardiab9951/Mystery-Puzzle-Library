#pragma once
#include "Library.h"
#include <string>
#include <iostream>
using namespace std;

class Game {
private:
    Library* worldLibrary;    // المكتبة الرئيسية
    BookNode* currentBook;    // الكتاب اللي اللاعب واقف عنده دلوقتي
    
    // دوال مساعدة
    void printIntro();                    // ترحيب وشرح اللعبة
    void handleEntranceSelection();       // اللاعب يختار من فين يبدأ
    bool solvePuzzlesForCurrentBook();    // حل الألغاز
    void chooseNextPath();                // اختيار يمين أو شمال
    
public:
    Game(Library* lib);    // بناء اللعبة
    void run();            // تشغيل اللعبة
};
