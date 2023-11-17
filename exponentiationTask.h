#pragma once

#include "prototypes.h"

void startFindMinQuantityOfOperations() {
    int degree;

    while (true)
    {
        cout << "Enter a degree ";
        cin >> degree;

        if (degree <= 0) {
            cout << "Invalid input" << endl;
        }
        else
        {
            break;
        }
    }

    int* arrayDegree = new int[degree + 1] {};
    for (int i = 0; i < degree + 1; i++)
    {
        arrayDegree[i] = 0;
    }

    for (int i = 2; i <= degree; i++)
    {
        arrayDegree[i] = arrayDegree[i - 1] + 1;
        for (int j = 2; j <= i - 1; j++)
        {
            arrayDegree[i] = min(arrayDegree[i], arrayDegree[j] + arrayDegree[i - j] + 1);
            if (i % j == 0)
            {
                arrayDegree[i] = min(arrayDegree[i], arrayDegree[i / j] + j - 1);
            }
        }
    }

    cout << "\n| Degrees and Count of opearations |\n";
    for (int i = 2; i <= degree; i++)
    {
        cout << i << " " << arrayDegree[i] << " | ";
    }
    cout << endl;

    delete[] arrayDegree;
}