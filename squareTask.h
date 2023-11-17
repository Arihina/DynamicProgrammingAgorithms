#pragma once

#include "prototypes.h"

vector<pair<int, int>> findVisitedNodesInSquare(vector<vector<int>> pathMatrix, vector<vector<int>> matrix) {
    vector<pair<int, int>> visitedNodes;

    int row = pathMatrix.size() - 1, column = 0;

    visitedNodes.push_back(make_pair(row, column));

    while (row > 0 || column < pathMatrix.size() - 1)
    {
        if (row == 0)
        {
            column++;
        }
        else if (column == pathMatrix.size() - 1)
        {
            row--;
        }
        else
        {
            if (matrix[row * 2 - 1][column] < matrix[row * 2][column])
            {
                row--;
            }
            else
            {
                column++;
            }
        }
        visitedNodes.push_back(make_pair(row, column));
    }

    return visitedNodes;
}

vector<vector<int>> calculatePathMatrix(vector<vector<int>> matrix) {
    vector<vector<int>> pathMatrix(ceil(matrix.size() / 2.), vector<int>(ceil(matrix.size() / 2.), 0));

    for (int j = pathMatrix.size() - 2; j >= 0; j--)
    {
        pathMatrix[0][j] = pathMatrix[0][j + 1] + matrix[0][j];
    }

    for (int i = 1; i < pathMatrix.size(); i++)
    {
        pathMatrix[i][matrix[1].size() - 1] = pathMatrix[i - 1][matrix[1].size() - 1] + matrix[i * 2 - 1][matrix[1].size() - 1];
    }

    for (int i = 1; i < pathMatrix.size(); i++)
    {
        for (int j = pathMatrix.size() - 2; j >= 0; j--)
        {
            pathMatrix[i][j] = min(pathMatrix[i][j + 1] + matrix[i * 2][j],
                pathMatrix[i - 1][j] + matrix[i * 2 - 1][j]);
        }
    }

    return pathMatrix;
}

vector<vector<int>> fillRandomMatrix(int size) {
    vector<vector<int>> matrix;

    for (int i = 0; i < size; i++)
    {
        vector<int> temp;
        for (int j = 0; j < size / 2 + 1; j++)
        {
            temp.push_back(rand() % 9 + 1);
        }
        matrix.push_back(temp);
    }

    for (int i = 0; i < size; i += 2)
    {
        matrix[i].pop_back();
    }

    return matrix;
}

vector<vector<int>> readMatrixFromFile(string fileName, int size) {
    vector<vector<int>> matrix;
    ifstream fin;
    string line;

    fin.open(fileName);

    for (int i = 0; i < size; i++)
    {
        getline(fin, line);
        stringstream fileString(line);
        vector<int> temp;
        string num;

        while (fileString >> num)
        {
            temp.push_back(stoi(num));
        }
        matrix.push_back(temp);
    }

    fin.close();

    return matrix;
}

void startFindMinPathInSquare() {
    cout << "Enter size of start matrix ";
    int size;
    cin >> size;
    cout << endl;
    vector<vector<int>> matrix = fillRandomMatrix(size);
    cout << "Start matrix" << endl;
    printMatrix(matrix);

    vector<vector<int>> pathMatrix = calculatePathMatrix(matrix);
    cout << "Path matrix " << endl;
    printMatrix(pathMatrix);

    cout << "Min path " << pathMatrix[pathMatrix.size() - 1][0] << endl;

    vector<pair<int, int>> nodes = findVisitedNodesInSquare(pathMatrix, matrix);
    cout << "Visited nodes " << endl;
    for (int i = 0; i < nodes.size(); i++)
    {
        cout << nodes[i].first << " " << nodes[i].second << endl;
    }
}
