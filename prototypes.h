#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

template<typename T> void printMatrix(vector<vector<T>>);

vector<vector<int>> fillRandomTriangle(int);
vector<vector<int>> readTriangle(string, int);
template<typename T> void printTriangle(vector<vector<T>>);
vector<vector<int>> copyTriangle(vector<vector<int>>);
void calcTriangle(vector<vector<int>>&, vector<vector<int>>&);
pair<vector<pair<int, int>>, int> findVisitedNodesInTriangle(vector<vector<int>>&, vector<vector<int>>&);
void startFindMaxPathInTriangle();

void startFindMinQuantityOfOperations();

vector<vector<bool>> createBoolMatrix(string, string);
vector<vector<int>> copyMatrix(vector<vector<bool>>);
vector<vector<int>> calculateMatrix(vector<vector<int>>);
vector<pair<int, int>> findAll—hainIndexes(vector<vector<int>>, vector<vector<bool>>);
string findMaxChain(vector<pair<int, int>>, vector<vector<bool>>, string);
void startAlgorithmNeedlemanWunsch();

vector<vector<int>> calculateBackpackMatrix(vector<int>&, vector<int>&, int, int);
template<typename T> void printVector(vector<T>);
vector<int> readVectorFromFile(string, int);
void startSolveTaskAboutBackpack();

vector<pair<int, int>> findVisitedNodesInSquare(vector<vector<int>>, vector<vector<int>>);
vector<vector<int>> calculatePathMatrix(vector<vector<int>>);
vector<vector<int>> fillRandomMatrix(int);
vector<vector<int>> readMatrixFromFile(string, int);
void startFindMinPathInSquare();


template<typename T> void printMatrix(vector<vector<T>> matrix) {
    for (int i = 0; i < matrix.size(); i++)
    {
        for (int j = 0; j < matrix[i].size(); j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}