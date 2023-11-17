#pragma once

#include "prototypes.h"

vector<vector<bool>> createBoolMatrix(string str1, string str2) {
    vector<vector<bool>> boolMatrix(str2.size(), vector<bool>(str1.size(), 0));
    for (int i = 0; i < str2.size(); i++)
    {
        for (int j = 0; j < str1.size(); j++)
        {
            if (str2[i] == str1[j]) {
                boolMatrix[i][j] = true;
            }
            else {
                boolMatrix[i][j] = false;
            }
        }
    }

    return boolMatrix;
}

vector<vector<int>> copyMatrix(vector<vector<bool>> matrix) {
    vector<vector<int>> newMatrix(matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));

    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 1; j <= matrix[i].size(); j++)
        {
            newMatrix[i][j] = (int)matrix[i][j - 1];
        }
    }

    return newMatrix;
}

vector<vector<int>> calculateMatrix(vector<vector<int>> matrix, vector<vector<bool>> boolMatrix) {
    for (int i = matrix.size() - 2; i > 0; i--)
    {
        for (int j = 1; j < matrix[i].size(); j++)
        {
            if (boolMatrix[i][j - 1])
            {
                matrix[i][j] = matrix[i + 1][j - 1] + 1;
            }
            else
            {
                matrix[i][j] = max(matrix[i + 1][j], matrix[i][j - 1]);
            }
        }
    }

    for (int i = 1; i < matrix[0].size(); i++)
    {
        if (boolMatrix[0][i - 1])
        {
            matrix[0][i] = matrix[1][i - 1] + 1;
        }
        else
        {
            matrix[0][i] = max(matrix[1][i], matrix[0][i - 1]);
        }
    }

    return matrix;
}

vector<pair<int, int>> findAll—hainIndexes(vector<vector<int>> intMatrix, vector<vector<bool>> boolMatrix) {
    vector<pair<int, int>> startMaxIndex;

    int maxElem = intMatrix[0][0];
    for (int i = 0; i < intMatrix.size(); i++)
    {
        for (int j = 0; j < intMatrix[i].size(); j++)
        {
            if (intMatrix[i][j] > maxElem)
            {
                maxElem = intMatrix[i][j];
            }
        }
    }

    for (int i = intMatrix.size() - 2; i > 0; i--)
    {
        for (int j = 1; j < intMatrix[i].size(); j++)
        {
            if (intMatrix[i][j] == maxElem && boolMatrix[i][j - 1])
            {
                startMaxIndex.push_back(make_pair(i, j - 1));
            }
        }
    }

    for (int i = 1; i < intMatrix[0].size(); i++) {
        if (boolMatrix[0][i - 1] && intMatrix[0][i] == maxElem) {
            startMaxIndex.push_back(make_pair(0, i - 1));
        }
    }

    return startMaxIndex;
}

string findMaxChain(vector<pair<int, int>> coordinates, vector<vector<bool>> matrix, string str) {
    vector<string> results;

    for (pair<int, int> c : coordinates)
    {
        int vert = c.first;
        int hor = c.second;
        string temp = "";

        for (int i = vert; i <= matrix.size() - 1 && hor >= 0; i++)
        {
            if (matrix[i][hor])
            {
                temp += str[i];
            }
            hor--;
        }
        results.push_back(temp);
    }

    string maxStr = results[0];
    int maxLen = results[0].size();
    for (int i = 0; i < results.size(); i++)
    {
        if (results[i].size() > maxLen)
        {
            maxLen = results[i].size();
            maxStr = results[i];
        }
    }
    reverse(maxStr.begin(), maxStr.end());

    return maxStr;
}

void startAlgorithmNeedlemanWunsch() {
    string str1, str2;
    cout << "Enter first string from characters A, G, C, T without spaces (horizontally string) ";
    cin >> str1;
    cout << endl;
    cout << "Enter second string from characters A, G, C, T without spaces (vertically string) ";
    cin >> str2;
    cout << endl;

    vector<vector<bool>> boolMatrix = createBoolMatrix(str1, str2);
    printMatrix(boolMatrix);

    vector<vector<int>> intMatrix = copyMatrix(boolMatrix);

    intMatrix = calculateMatrix(intMatrix, boolMatrix);
    printMatrix(intMatrix);

    vector<pair<int, int>> coordinates = findAll—hainIndexes(intMatrix, boolMatrix);

    string resultString = findMaxChain(coordinates, boolMatrix, str2);

    cout << "Chain with max lenght " << resultString << endl;
}
