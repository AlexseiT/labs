#include <iostream>
#include <fstream>
#include <vector>
#include <limits.h>
using namespace std;
int ch = 0;
bool s = false;
struct WayNodes 
{
    int* weight;
    int* graph;
};
const int maximum = pow(10, 9);//INT_MAX
int** set(int** matrix, int numberNodes)
{
    int** result = new int* [numberNodes];
    for (int i = 0; i < numberNodes; i++)
    {
        result[i] = new int[numberNodes];
        for (int j = 0; j < numberNodes; j++)
        {
            if (matrix[i][j] != 0 && matrix[i][j] != maximum) result[i][j] = matrix[i][j] + ch;
        }
    }
    return result;
}
WayNodes Ford_Bellman_Func(int** C, int numberNodes, int node) 
{
    int* D = new int[numberNodes];
    int* nD = new int[numberNodes];
    int* neighbours = new int[numberNodes];
    int* n_neighbours = new int[numberNodes];
    int** S = new int*[numberNodes];
    WayNodes result;
    for (int i = 0; i < numberNodes; i++) 
    {
        D[i] = maximum;
        nD[i] = maximum;
        neighbours[i] = i;
        n_neighbours[i] = i;
        S[i] = new int[numberNodes];
        for (int j = 0; j < numberNodes; j++)
        {
            S[i][j] = 0;
            S[i][node] = 1;
        }
    }
    D[node] = 0;
    nD[node] = 0;
    for (int i = 0; i < numberNodes; i++) 
    {
        bool check = true;                        
        for (int j = 0; j < numberNodes; j++) 
        {           
            for (int k = 0; k < numberNodes; k++) 
            {
                //S[k][node] = 1;
                if (D[k] + C[k][j] < D[j])
                {

                    //S[k][j] = 1;
                    //S[j][k] = 1;
                    //S[neighbours[j]][k] = 0;

                    D[j] = D[k] + C[k][j];
                    neighbours[j] = k;

                    check = false;
                }
            }
        }
        if (check)
        {
            break;
        }
    }
    cout << endl;
    cout << endl;
    cout << endl;
    for (int i = 0; i < numberNodes; i++)
    {
        cout << D[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < numberNodes; i++)
    {
        cout << neighbours[i] << " ";
    }
    cout << endl;
    //MINUS    
    
    bool check = true;
    int minus = -1;
    for (int j = 0; j < numberNodes; j++) 
    {  
        for (int k = 0; k < numberNodes; k++) 
        {
            if (D[k] + C[k][j] < D[j])
            {
                check = false;
                minus = k;
            }
        }
    }
    vector<int> way;
    
    if (!check)
    {
        {
            int** nC = set(C, numberNodes);
            int neighbour = minus;
            for (int i = 0; i < numberNodes; i++)
            {
                neighbour = neighbours[neighbour];
            }
            vector<int> way;
            int checkNeighbour = neighbour;
            do
            {
                way.insert(way.begin(), checkNeighbour);

                checkNeighbour = neighbours[checkNeighbour];

            } while (checkNeighbour != neighbour);
            way.insert(way.begin(), neighbour);
            cout << "MINUS: ";
            for (int j = 0; j < way.size(); j++)
            {
                cout << way[j];
                if (j < way.size() - 1) cout << " => ";
            }
            cout << "\n";
        }

        // второй проход
        for (int i = 0; i < numberNodes; i++)
        {
            D[i] = maximum;
            nD[i] = maximum;
            neighbours[i] = i;
        }

        D[node] = 0;
        nD[node] = 0;

        for (int i = 0; i < numberNodes; i++)
        {
            bool check = true;
            for (int j = 0; j < numberNodes; j++)
            {
                for (int k = 0; k < numberNodes; k++)
                {
                    if (D[k] + C[k][j] < D[j] && S[k][j] != 1)
                    {
                        S[j][k] = 1;
                        D[j] = D[k] + C[k][j];
                        neighbours[j] = k;
                        check = false;
                    }
                    
                }

            }
            if (check)
            {
                break;
            }
        }
        result.weight = D;
        result.graph = neighbours;
        return result;
    }
    

    //neighbours[3] = node;
    result.weight = D;
    result.graph = neighbours;
    return result;
}
WayNodes Deicstra_Func(int** C, int numberNodes, int node)
{
    int* D = new int[numberNodes];
    bool* S = new bool[numberNodes];
    int* neighbours = new int[numberNodes];
    WayNodes result;
    for (int i = 0; i < numberNodes; i++)
    {
        if (i == node) D[i] = 0;
        else D[i] = maximum;
        S[i] = false;
        neighbours[i] = i;
    }
    while(true) 
    {

        int tempNode = 0;
        int minimum = maximum;

        bool checkNode = false;

        for (int i = 0; i < numberNodes; i++)
        {
            if (D[i] < minimum && !S[i])
            {
                minimum = D[i];
                tempNode = i;
                checkNode = true;
            }
        }

        if (!checkNode) break;
        for (int i = 0; i < numberNodes; i++)
        {
            //MINUS
            if (C[tempNode][i] < 0) 
            {
                delete[] D;
                delete[] S;
                delete[] neighbours;
                result.weight = result.graph = NULL;
                return result;
            }

            if (C[tempNode][i] < maximum && !S[i])
            {
                int v = i;
                int newD = C[tempNode][v] + D[tempNode];
                if (newD < D[v])
                {
                    D[v] = newD;
                    neighbours[v] = tempNode;
                }
            }
        } 
        S[tempNode] = true;
    }
    delete[] S;
    result.weight = D;
    result.graph = neighbours;
    return result;
}

void Delete_Way(WayNodes way) 
{
    delete[] way.weight;
    delete[] way.graph;
}

void Delete_Graph(int** adjacency_matrix, int vertices) 
{
    for (int i = 0; i < vertices; i++) 
    {
        delete[] adjacency_matrix[i];
    }
    delete[] adjacency_matrix;
}

void Find(int** matrix, int numberNodes)
{
    ch = matrix[0][0];
    for (int i = 0; i < numberNodes; i++)
    {
        for (int j = 0; j < numberNodes; j++)
        {
            if (matrix[i][j] < ch) ch = matrix[i][j];
        }
    }
    ch;
    ch *= -1;
}
void Modul(int** matrix, int numberNodes)
{
    Find(matrix, numberNodes);
    std::cout << "\n";
    int node;
    cin >> node;
    std::cout << "\n";
    WayNodes wayF = Ford_Bellman_Func(matrix, numberNodes, node);
    if (wayF.graph != NULL) 
    {
        cout << "\tFord Bellman:\n" << endl;

        for (int i = 0; i < numberNodes; i++) 
        {
            if (i == node) continue;
            int k = i;
            vector<int> way;
            do 
            {
                way.insert(way.begin(), k);
                k = wayF.graph[k];
            } while (k != wayF.graph[k]);

            way.insert(way.begin(), node);
            for (int j = 0; j < way.size(); j++)
            {
                cout << way[j];
                if (j < way.size() - 1) cout << " ";
            }
            if (s == true)
            {
                //wayF.weight[i] = wayF.weight[i] + ch - 1;
            }
            cout << "\t\tweight: " << wayF.weight[i] << endl;
        }
        cout << endl;
        Delete_Way(wayF);
    }

    WayNodes wayD = Deicstra_Func(matrix, numberNodes, node);
    if (wayD.graph != NULL)
    {
        cout << "\tDeicstra:\n" << endl;
        for (int i = 0; i < numberNodes; i++) 
        {
            if (i == node) continue;
            int k = i;
            vector<int> way;
            do {
                way.insert(way.begin(), k);
                k = wayD.graph[k];
            } while (k != node);
            way.insert(way.begin(), node);
            for (int j = 0; j < way.size(); j++)
            {
                cout << way[j];
                if (j < way.size() - 1) cout << " ";
            }
            cout << "\t\tweight: " << wayD.weight[i]<< endl;
        }
        Delete_Way(wayD);
    }

    Delete_Graph(matrix, numberNodes);
}

int main()
{
    ifstream file;
    file.open("text.txt", ios::in);

    string fileContents;
    file >> fileContents;

    int numberNodes = atoi(fileContents.c_str());
    int** matrix = new int* [numberNodes];
    std::cout << "  ";
    for (int i = 0; i < numberNodes; i++)
    {
        std::cout << i << " ";
    }
    std::cout << "\n";
    std::cout << "  ";
    for (int i = 0; i < numberNodes; i++)
    {
        std::cout << "--";
    }
    std::cout << "\n";
    for (int i = 0; i < numberNodes; i++) 
    {
        matrix[i] = new int[numberNodes];
        std::cout << i << "|";
        for (int j = 0; j < numberNodes; j++) 
        {
            file >> fileContents;
            if (fileContents == "NULL")
            {
                matrix[i][j] = maximum;
                std::cout << "- ";
            }
            else
            {
                matrix[i][j] = atoi(fileContents.c_str());
                std::cout << matrix[i][j] << " ";
            }
            
        }
        std::cout <<  "\n";
    }
    Modul(matrix, numberNodes);
}