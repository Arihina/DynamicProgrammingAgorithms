#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

vector<vector<int>> fillRandomTriangle(int);
vector<vector<int>> readTriangle(string, int);
void printTriangle(vector<vector<int>>);
vector<vector<int>> copyTriangle(vector<vector<int>>);
void calcTriangle(vector<vector<int>>&, vector<vector<int>>&);
pair<vector<int>, int> findVisitedNodes(vector<vector<int>>&, vector<vector<int>>&);

void main()
{
    vector<vector<int>> triangle = fillRandomTriangle(5);
    printTriangle(triangle);
    vector<vector<int>> newTriangle = copyTriangle(triangle);
    calcTriangle(triangle, newTriangle);
    printTriangle(newTriangle);
    pair<vector<int>, int> result = findVisitedNodes(triangle, newTriangle);
    cout << "Visited nodes" << endl;
    for (int i = 0; i < result.first.size(); i++)
    {
        cout << result.first[i] << " ";
    }
    cout << "\nMax sum of load " << result.second << endl;
}

vector<vector<int>> readTriangle(string fileName, int depth) {
    vector<vector<int>> trangle;
    ifstream fin;
    string line;

    fin.open("triangle.txt");

    for (int i = 0; i < depth; i++)
    {
        vector<int> temp;
        string buff;
        getline(fin, line);
        for (int j = 0;  j < line.length(); j++)
        {
            if (line[j] != ' ')
            {
                buff += line[j];
            }
            else 
            {
                temp.push_back(stoi(buff));
                buff = "";
            }
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
        for (int j = 1; j < i+2; j++)
        {
            temp.push_back(rand() % 100);
        }
        trangle.push_back(temp);
    }

    return trangle;
}

void printTriangle(vector<vector<int>> triangle) {
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

pair<vector<int>, int> findVisitedNodes(vector<vector<int>>& originalTriangle, vector<vector<int>>& newTriangle) {
    vector<int> visitedNodes;

    int finalMaxIndex, finalMaxElem = newTriangle[newTriangle.size() - 1][0];
    for (int i = 0; i < newTriangle[newTriangle.size() - 1].size(); i++)
    {
        if (finalMaxElem <= newTriangle[newTriangle.size() - 1][i]) {
            finalMaxElem = newTriangle[newTriangle.size() - 1][i];
            finalMaxIndex = i;
        }
    }

    visitedNodes.push_back(finalMaxIndex - 1);

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
        visitedNodes.push_back(finalMaxIndex - 1);
    }

    visitedNodes.push_back(0);
    reverse(visitedNodes.begin(), visitedNodes.end());

    return make_pair(visitedNodes, finalMaxElem);
}