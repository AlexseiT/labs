#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

struct Сonnect
{
    int node1;
    int node2;
    int weight;
};

class Parent 
{
    vector<int> parentNode;
public:
    Parent() {}
    Parent(int size)
    {
        parentNode.resize(size);
    }
    void Set(int node) 
    {
        parentNode[node] = node;
    }
    int Find(int node) 
    {
        return (node == parentNode[node] ? node : parentNode[node] = Find(parentNode[node]));
    }
    void Union(int node1, int node2)
    {
        if ((node1 = Find(node1)) == (node2 = Find(node2))) return;
        parentNode[node2] = node1;
    }
};
vector<string> Separate(string line, char divider)
{
    vector<string> result;
    int i = 0;
    string element;
    while (!(line[i] == '\n' || line[i] == 0))
    {
        if (line[i] == divider)
        {
            i++;
            result.push_back(element);
            element.clear();
            continue;
        }
        element.push_back(line[i]);
        i++;
    }
    result.push_back(element);
    return result;
}
int Check(Сonnect edges1, Сonnect edges2) 
{
    return edges1.weight < edges2.weight;
}

vector<Сonnect> Cruskal(vector<Сonnect> edges, int numberNodes) 
{
    Parent sets(numberNodes);

    sort(edges.begin(), edges.end(), Check);

    for (int i = 0; i < numberNodes; i++) 
    {
        sets.Set(i);
    }
    vector<Сonnect> result;
    int numberEdges = 0;
    for (int i = 0; i < edges.size(); i++) 
    {
        if (numberEdges == numberNodes - 1) break;
        Сonnect actual = edges[i];
        if (sets.Find(actual.node1) != sets.Find(actual.node2))
        {
            result.push_back(actual);
            sets.Union(actual.node1, actual.node2);
            numberEdges++;
        }
    }
    return result;
}

int main()
{
    ifstream file;
    file.open("fail.txt", ios::in);
    string txt;
    file >> txt;
    vector<string> sizeGraph = Separate(txt, 'x');
    int numberNodes = atoi(sizeGraph[0].c_str());
    int numberEdges = atoi(sizeGraph[1].c_str());
    vector<Сonnect> edges;
    for (int i = 0; i < numberEdges; i++) 
    {
        Сonnect edgeNew;
        file >> txt;
        edgeNew.node1 = atoi(txt.c_str()) - 1;
        file >> txt;
        edgeNew.node2 = atoi(txt.c_str()) - 1;
        file >> txt;
        edgeNew.weight = atoi(txt.c_str());
        if (edgeNew.node1 > numberNodes || edgeNew.node2 > numberNodes) 
        {
            cout << "ERROR: " << i + 1 << endl;
            return 0;
        }
        edges.push_back(edgeNew);
    }
    vector<Сonnect> result = Cruskal(edges, numberNodes);

    int weight = 0;
    cout << "Minimal Connected Graph:" << endl;
    for (int i = 0; i < result.size(); i++) 
    {
        cout << "(" 
            << result[i].node1 << "-" << result[i].node2
            << "),  weight = " << result[i].weight << endl;
        weight += result[i].weight;
    }
    cout << endl << "WEIGHT = " << weight << endl;
}