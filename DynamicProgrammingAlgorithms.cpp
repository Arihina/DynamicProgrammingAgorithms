#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
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
vector<pair<int, int>> findAllСhainIndexes(vector<vector<int>>, vector<vector<bool>>);
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


void main()
{
    startFindMaxPathInTriangle();
    startFindMinQuantityOfOperations();
    startAlgorithmNeedlemanWunsch();
    startSolveTaskAboutBackpack();
    startFindMinPathInSquare();
}


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
        for (int j = 1; j < i+2; j++)
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


vector<vector<bool>> createBoolMatrix(string str1, string str2) {
    vector<vector<bool>> boolMatrix (str2.size(), vector<bool>(str1.size(), 0));
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
    vector<vector<int>> newMatrix (matrix.size() + 1, vector<int>(matrix[0].size() + 1, 0));

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
        for (int j = 1; j  < matrix[i].size(); j++)
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

vector<pair<int, int>> findAllСhainIndexes(vector<vector<int>> intMatrix, vector<vector<bool>> boolMatrix) {
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

    for (pair<int, int> c: coordinates)
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

    vector<pair<int, int>> coordinates = findAllСhainIndexes(intMatrix, boolMatrix);

    string resultString = findMaxChain(coordinates, boolMatrix, str2);

    cout << "Chain with max lenght " << resultString << endl;
}


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

    for (int i = 0; i < size; i+=2)
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