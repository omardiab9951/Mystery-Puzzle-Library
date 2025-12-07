#include "Game.h"
#include <limits> // لاستخدام numeric_limits لتنظيف الإدخال

// Constructor: نربط اللعبة بالمكتبة التي أنشأها Member 2
Game::Game(Library* lib) {
    worldLibrary = lib;
    currentBook = nullptr;
}

// دالة مساعدة لتحويل النصوص لحروف صغيرة لتسهيل المقارنة
// ملاحظة: المفترض Member 4 يعملها في Utils، لكن سأضعها هنا مؤقتاً لتعمل اللعبة معك
string Game::toLowerCase(string str) {
    string result = "";
    for (char c : str) {
        result += tolower(c);
    }
    return result;
}

// مقدمة اللعبة
void Game::printIntro() {
    cout << "\n*************************************************" << endl;
    cout << "* WELCOME TO THE MYSTERY LIBRARY      *" << endl;
    cout << "* You must find the FINAL BOOK to escape!    *" << endl;
    cout << "*************************************************\n" << endl;
}

// اختيار كتاب البداية من المصفوفة التي جهزها Member 2
void Game::handleEntranceSelection() {
    BookNode** entrances = worldLibrary->getEntrances(); // نحصل على مصفوفة المداخل

    cout << "You stand before 4 mystical gates. Which one will you enter?" << endl;
    for (int i = 0; i < 4; i++) {
        cout << " " << (i + 1) << ". Entrance Gate " << (i + 1);
        if (entrances[i] != nullptr) {
            // عرض الصعوبة إذا أردت (اختياري)
            // cout << " (" << entrances[i]->getDifficultyAsString() << ")";
        }
        cout << endl;
    }

    int choice = 0;
    while (true) {
        cout << "Choose (1-4): ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 4) {
            cin.clear(); // تنظيف حالة الخطأ
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // تجاهل الإدخال الخاطئ
            cout << "Invalid choice. Please try again." << endl;
        } else {
            // ضبط الكتاب الحالي ليكون هو المدخل المختار
            // (choice - 1) لأن المصفوفة تبدأ من 0
            currentBook = entrances[choice - 1];
            cout << "\nYou entered the library through Gate " << choice << "...\n" << endl;
            break;
        }
    }
    // تنظيف الإدخال لما بعد ذلك
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}

// محرك حل الألغاز
bool Game::solvePuzzlesForCurrentBook() {
    currentBook->displayInfo(); // عرض معلومات الكتاب (للتوضيح للاعب)
    
    int cluesCount = currentBook->getClueCount();
    
    if (cluesCount == 0) {
        cout << "This book has no puzzles. Moving forward..." << endl;
        return true;
    }

    for (int i = 0; i < cluesCount; i++) {
        Clue c = currentBook->getClue(i);
        string playerAnswer;
        
        while (true) {
            cout << "\n--- Puzzle " << (i + 1) << " ---" << endl;
            cout << "Riddle: " << c.problem << endl;
            cout << "Your Answer: ";
            
            // نستخدم getline لقراءة جمل كاملة (لو الإجابة أكثر من كلمة)
            getline(cin, playerAnswer);

            // مقارنة الإجابة (تجاهل حالة الأحرف)
            if (toLowerCase(playerAnswer) == toLowerCase(c.solution)) {
                cout << "Correct! The magical glyphs glow green." << endl;
                break; // نخرج من اللوب ونذهب للغز التالي
            } else {
                cout << "Incorrect. The book remains sealed. Try again." << endl;
            }
        }
    }
    
    // بعد حل جميع الألغاز في الكتاب
    currentBook->puzzleSolved = true;
    currentBook->visited = true;
    return true;
}

// منطق الانتقال للكتاب التالي (Linked List Traversal)
void Game::chooseNextPath() {
    // إذا وصلنا للكتاب النهائي
    if (currentBook->type == FINAL) {
        return; // لا يوجد انتقال بعد النهاية
    }

    // الحالة الأولى: الكتاب صعب أو له مسار واحد فقط
    if (!currentBook->hasTwoPaths()) {
        if (currentBook->next1 != nullptr) {
            cout << "The path moves strictly forward. Following the magical trail..." << endl;
            currentBook = currentBook->next1; // تحريك المؤشر
        } else {
            cout << "Error: Dead End! (This shouldn't happen in a valid library)." << endl;
            // هنا ممكن ننهي اللعبة أو نعيد اللاعب
        }
    } 
    // الحالة الثانية: الكتاب سهل وله مساران (تفرع)
    else {
        cout << "\nThe path splits! You see two floating books ahead." << endl;
        cout << "1. Go Left (Path A)" << endl;
        cout << "2. Go Right (Path B)" << endl;
        
        int choice = 0;
        while (true) {
            cout << "Which path do you take? (1 or 2): ";
            cin >> choice;

            if (cin.fail() || (choice != 1 && choice != 2)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Focus! The magic requires a clear choice (1 or 2)." << endl;
            } else {
                break;
            }
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // تنظيف

        // تحريك المؤشر بناءً على الاختيار
        if (choice == 1) {
            currentBook = currentBook->next1;
        } else {
            currentBook = currentBook->next2;
        }
    }
    cout << "\n-------------------------------------------------\n" << endl;
}

// حلقة اللعب الرئيسية (Main Loop)
void Game::run() {
    printIntro();
    handleEntranceSelection();

    // اللوب يستمر طالما لم نصل للكتاب الأخير
    while (currentBook != nullptr) {
        
        // 1. حل الألغاز في الكتاب الحالي
        if (solvePuzzlesForCurrentBook()) {
            
            // التحقق من الفوز
            if (currentBook->type == FINAL) {
                cout << "\n*************************************************" << endl;
                cout << "* CONGRATULATIONS! You solved the Final Mystery!*" << endl;
                cout << "* The Library sets you free.           *" << endl;
                cout << "*************************************************" << endl;
                break; // إنهاء اللعبة
            }

            // 2. الانتقال للكتاب التالي
            chooseNextPath();
        }
    }
}
