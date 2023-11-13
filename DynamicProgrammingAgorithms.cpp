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
pair<vector<pair<int, int>>, int> findVisitedNodes(vector<vector<int>>&, vector<vector<int>>&);
void startFindMaxPathInTriangle();

void findQuantityOfOperations();


void main()
{
    findQuantityOfOperations();
}


vector<vector<int>> readTriangle(string fileName, int depth) {
    vector<vector<int>> trangle;
    ifstream fin;
    string line;

    fin.open(fileName);

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

pair<vector<pair<int, int>>, int> findVisitedNodes(vector<vector<int>>& originalTriangle, vector<vector<int>>& newTriangle) {
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
    pair<vector<pair<int, int>>, int> result = findVisitedNodes(triangle, newTriangle);

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


void findQuantityOfOperations() {
    int degree;

    while (true)
    {
        cout << "Enter a degree ";
        cin >> degree;
        cout << endl;

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

    for (int i = 2; i <= degree; i++)
    {
        cout << arrayDegree[i] << " ";
    }

    delete[] arrayDegree;
}