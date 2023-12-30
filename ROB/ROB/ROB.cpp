#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Item 
{
    int weight;
    int price;
};
struct Backpack 
{
    Item item;
    int countItem;
};

vector<Item> FileOpen()
{
    vector<Item> itemsList;
    ifstream file;

    file.open("file.txt", ios::in);
    while (!file.eof())
    {
        Item item;
        file >> item.weight >> item.price;
        itemsList.push_back(item);
    }
    return itemsList;
}

vector<Backpack> Steal(int weightLimit, vector<Item> itemsList) 
{
    vector<vector<Backpack>> results(weightLimit);
    for (int i = 0; i < weightLimit; i++) 
    {
        for (int j = 0; j < itemsList.size(); j++) 
        {
            Backpack item;
            item.item = itemsList[j];
            item.countItem = 0;
            results[i].push_back(item);
        }
    }
    int* f = new int[weightLimit];
    for (int i = 0; i < weightLimit; i++) 
    {
        int max = 0;
        int maxj = 0;
        bool checkMaximumIndex = false;
        for (int j = 0; j < itemsList.size(); j++) 
        {
            int index = i - itemsList[j].weight;
            if (index >= 0) 
            {
                if (f[index] + itemsList[j].price > max) 
                {
                    max = f[index] + itemsList[j].price;
                    maxj = j;
                    checkMaximumIndex = true;
                }
            }
        }
        f[i] = max;
        if (checkMaximumIndex)
        {
            results[i] = results[i - itemsList[maxj].weight];
            results[i][maxj].countItem++;
        }
    }
    return results[weightLimit - 1];
}

void Modul(vector<Item> itemsList)
{
    int weightLimit;// M
    int resultPrice = 0;
    int resultWeight = 0;
    cout << "\t\tWeight limit" << endl;

    cin >> weightLimit;

    vector<Backpack> backpack = Steal(weightLimit + 1, itemsList);

    cout << "\t\tItems" << endl << endl;

    for (int i = 0; i < backpack.size(); i++)
    {

        cout << i + 1 << ") Weight = " << backpack[i].item.weight
            << "\tPrice = " << backpack[i].item.price
            << "\tNumber = " << backpack[i].countItem << endl;

        resultPrice += backpack[i].item.price * backpack[i].countItem;
        resultWeight += backpack[i].item.weight * backpack[i].countItem;
    }

    cout << endl << "\t\tResult" << endl << endl;

    cout << "Result price = " << resultPrice << endl;
    cout << "Result weight = " << resultWeight << endl;
}

int main()
{
    Modul(FileOpen());
}