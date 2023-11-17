#pragma once

#include "prototypes.h"

void reverseTraversal(vector<vector<int>> matrix, vector<int>& items, vector<int> itemsWeights, int i, int j) {
    if (matrix[i][j] == 0)
    {
        return;
    }

    if (matrix[i - 1][j] == matrix[i][j])
    {
        reverseTraversal(matrix, items, itemsWeights, i - 1, j);
    }
    else
    {
        reverseTraversal(matrix, items, itemsWeights, i - 1, j - itemsWeights[i - 1]);
        items.push_back(i);
    }
}

vector<vector<int>> calculateBackpackMatrix(vector<int>& itemsWeights, vector<int>& itemsPrices, int countItems, int maxWeight) {
    vector<vector<int>> matrix(countItems + 1, vector<int>(maxWeight + 1, 0));

    for (int i = 0; i <= countItems; i++)
    {
        for (int j = 0; j <= maxWeight; j++)
        {
            if (i == 0 || j == 0)
            {
                matrix[i][j] = 0;
            }
            else
            {
                if (j >= itemsWeights[i - 1])
                {
                    matrix[i][j] = max(matrix[i - 1][j],
                        matrix[i - 1][j - itemsWeights[i - 1]] + itemsPrices[i - 1]);
                }
                else
                {
                    matrix[i][j] = matrix[i - 1][j];
                }
            }
        }
    }

    return matrix;
}

template<typename T> void printVector(vector<T> vect) {
    for (int i = 0; i < vect.size(); i++)
    {
        cout << vect[i] << " ";
    }
    cout << endl;
}

vector<int> readVectorFromConsole(int size) {
    vector<int> vect;

    for (int i = 0; i < size; i++)
    {
        cout << "Enter a num ";
        int num;
        cin >> num;
        vect.push_back(num);
    }

    return vect;
}

vector<int> readVectorFromFile(string fileName, int size) {
    ifstream fin;
    string line;
    vector<int> vect;

    fin.open(fileName);

    for (int i = 0; i < size; i++)
    {
        int num;
        fin >> num;
        vect.push_back(num);
    }

    fin.close();

    return vect;
}

void startSolveTaskAboutBackpack() {
    int maxWeight, coutItems;
    cout << "Enter a max weight for backpack ";
    cin >> maxWeight;

    cout << "Enter a count of items ";
    cin >> coutItems;

    cout << "Enter a prices of items " << endl;
    vector<int> itemsPrices = readVectorFromConsole(coutItems);
    cout << "Enter a weights of items " << endl;
    vector<int> itemsWeights = readVectorFromConsole(coutItems);

    cout << "Price of items" << endl;
    printVector(itemsPrices);
    cout << "Weight of items" << endl;
    printVector(itemsWeights);

    vector<vector<int>> matrix = calculateBackpackMatrix(itemsWeights, itemsPrices, coutItems, maxWeight);
    printMatrix(matrix);

    int maxUtility = matrix[matrix.size() - 1][matrix[matrix.size() - 1].size() - 1];
    cout << "Max utility of backpack " << maxUtility << endl;

    vector<int> items;
    reverseTraversal(matrix, items, itemsWeights, coutItems, maxWeight);
    cout << "Items from backpack " << endl;
    printVector(items);
}