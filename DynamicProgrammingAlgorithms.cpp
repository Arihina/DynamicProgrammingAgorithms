#include <map>

#include "prototypes.h"
#include "triangleTask.h"
#include "exponentiationTask.h"
#include "bioAlgorithmTask.h"
#include "backpackTask.h"
#include "squareTask.h"

using namespace std;

typedef void(*func)();

void main()
{
    map<char, func> functions {
        {'1', startFindMaxPathInTriangle},
        {'2', startFindMinQuantityOfOperations},
        {'3', startAlgorithmNeedlemanWunsch},
        {'4', startSolveTaskAboutBackpack},
        {'5', startFindMinPathInSquare}
    };

    char userInput;
    while (true) {

        cout << "Select a function" << endl;
        cout << "Find max path in triangle - 1" << endl;
        cout << "Find min quantity of operations for exponentiation  - 2 " << endl;
        cout << "Algorithm Needleman Wunsch - 3" << endl;
        cout << "Solve task about backpack - 4" << endl;
        cout << "Find min path in Square - 5" << endl;
        cout << "Exit - 0" << endl;

        cin >> userInput;
        cout << endl;

        if (userInput == '0')
        {
            cout << "Exit" << endl;
            break;
        }
        else if (userInput != '1' && userInput != '2' && userInput != '3' && userInput != '4' && userInput != '5')
        {
            cout << "Invalid input" << endl;
            cout << endl;
            continue;
        }

        try
        {
            functions[userInput]();
            cout << endl;
        }
        catch (const std::exception& ex)
        {
            cout << ex.what() << endl;
        }
    }
}
