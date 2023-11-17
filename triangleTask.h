#pragma once

#include "prototypes.h"

vector<vector<int>> readTriangle(string fileName, int depth) {
    vector<vector<int>> trangle;
    ifstream fin;
    string line;

    fin.open(fileName);

    for (int i = 0; i < depth; i++)
    {
        getline(fin, line);
        stringstream fileString(line);
        vector<int> temp;
        string num;

        while (fileString >> num)
        {
            temp.push_back(stoi(num));
        }
        trangle.push_back(temp);
    }

    fin.close();

    return trangle;
}

vector<vector<int>> fillRandomTriangle(int depth) {
    vector<vector<int>> trangle;

    for (int i = 0; i < depth; i++)
    {
        vector<int> temp;
        for (int j = 1; j < i + 2; j++)
        {
            temp.push_back(rand() % 100);
        }
        trangle.push_back(temp);
    }

    return trangle;
}

template<typename T> void printTriangle(vector<vector<T>> triangle) {
    for (int i = 0; i < triangle.size(); i++)
    {
        for (int j = 0; j < triangle[i].size(); j++)
        {
            cout << triangle[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

vector<vector<int>> copyTriangle(vector<vector<int>> originalTriangle) {
    vector<vector<int>> newTriangle(originalTriangle.size());

    for (int i = 0; i < originalTriangle.size(); i++)
    {
        newTriangle[i].push_back(0);
    }

    for (int i = 0; i < originalTriangle.size(); i++)
    {
        for (int j = 0; j < originalTriangle[i].size(); j++)
        {
            newTriangle[i].push_back(originalTriangle[i][j]);
        }
    }

    return newTriangle;
}

void calcTriangle(vector<vector<int>>& triangle, vector<vector<int>>& newTriangle) {
    for (int i = 1; i < triangle.size(); i++)
    {
        newTriangle[i][newTriangle[i].size() - 1] += newTriangle[i - 1][newTriangle[i - 1].size() - 1];
    }

    for (int i = 1; i < triangle.size(); i++)
    {
        for (int j = 1; j < triangle[i].size(); j++)
        {
            newTriangle[i][j] += max(newTriangle[i - 1][j - 1], newTriangle[i - 1][j]);
        }
    }
}

pair<vector<pair<int, int>>, int> findVisitedNodesInTriangle(vector<vector<int>>& originalTriangle, vector<vector<int>>& newTriangle) {
    vector<pair<int, int>> visitedNodes;

    int finalMaxIndex, finalMaxElem = newTriangle[newTriangle.size() - 1][0];
    for (int i = 0; i < newTriangle[newTriangle.size() - 1].size(); i++)
    {
        if (finalMaxElem <= newTriangle[newTriangle.size() - 1][i]) {
            finalMaxElem = newTriangle[newTriangle.size() - 1][i];
            finalMaxIndex = i;
        }
    }

    visitedNodes.push_back(make_pair(newTriangle.size() - 1, finalMaxIndex - 1));

    int elemForSearch;
    for (int i = originalTriangle.size() - 1; i > 1; i--)
    {
        elemForSearch = newTriangle[i][finalMaxIndex] - originalTriangle[i][finalMaxIndex - 1];
        for (int j = 1; j < originalTriangle[i - 1].size(); j++)
        {
            if (newTriangle[i - 1][j] == elemForSearch)
            {
                finalMaxIndex = j;
                break;
            }
        }
        visitedNodes.push_back(make_pair(i - 1, finalMaxIndex - 1));
    }

    visitedNodes.push_back(make_pair(0, 0));
    reverse(visitedNodes.begin(), visitedNodes.end());

    return make_pair(visitedNodes, finalMaxElem);
}

void startFindMaxPathInTriangle() {
    int depth;
    cout << "Enter a depth of the triangle ";
    cin >> depth;
    cout << endl;

    vector<vector<int>> triangle = fillRandomTriangle(depth);
    printTriangle(triangle);

    vector<vector<int>> newTriangle = copyTriangle(triangle);
    calcTriangle(triangle, newTriangle);

    printTriangle(newTriangle);
    pair<vector<pair<int, int>>, int> result = findVisitedNodesInTriangle(triangle, newTriangle);

    vector<pair<int, int>> firstAnswerElem = result.first;
    int secondAnswerElem = result.second;

    cout << "Visited nodes" << endl;
    for (int i = 0; i < firstAnswerElem.size(); i++)
    {
        cout << firstAnswerElem[i].first << ";" << firstAnswerElem[i].second << " ";
    }
    cout << "\nMax sum of load " << result.second << endl;
    cout << endl;
}