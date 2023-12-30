#pragma once
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <iomanip>

using namespace std;

class Index
{
public:
    int i;
    int j;
    bool find = false;
};

class Transportation
{
public:
    int price;
    int supply = 0;
    bool status = true;
    bool fictitiousA = false;
    bool fictitiousB = false;
    bool statusWay = false;
};

class TransportTask
{
private:
    int sumReserves;
    int sumNeeds;
    int Z = 0;
    int diffReservesNeeds;

public:
    vector<vector<Transportation>> transportationMatrix;
    vector<int> reserves;
    vector<int> needs;

    bool CheckSolution()
    {
        CalculateCheckSum();
        if (sumReserves + sumReserves == 0) return true;
        return false;
    }
    bool —losedType()
    {
        if (diffReservesNeeds > 0) return true;
        return false;
    }
    bool Check—losed()
    {
        CalculateDifferenceReservesNeeds();
        if (diffReservesNeeds == 0) return true;
        return false;
    }
    int GetZ()
    {
        return Z;
    }
    int CalculateCostTransportation()
    {
        for (int i = 0; i < transportationMatrix.size(); ++i)
        {
            for (int j = 0; j < transportationMatrix[0].size(); ++j)
            {
                if (transportationMatrix[i][j].status) Z += transportationMatrix[i][j].price * transportationMatrix[i][j].supply;
            }
        }
        return Z;
    }
    Index FindMinimumFreePrice()
    {
        Index index;
        int minimumPrice = numeric_limits<int>::max();
        for (int i = 0; i < transportationMatrix.size(); ++i)
        {
            for (int j = 0; j < transportationMatrix[0].size(); ++j)
            {
                if (transportationMatrix[i][j].status && 
                    !transportationMatrix[i][j].fictitiousA && 
                    !transportationMatrix[i][j].fictitiousB && 
                    transportationMatrix[i][j].supply == 0 && 
                    transportationMatrix[i][j].price < minimumPrice)
                {
                    index.i = i;
                    index.j = j;
                    index.find = true;
                    minimumPrice = transportationMatrix[i][j].price;
                }
            }
        }
        if (index.find)
        {
            return index;
        }
        else
        {
            for (int i = 0; i < transportationMatrix.size(); ++i)
            {
                for (int j = 0; j < transportationMatrix[0].size(); ++j)
                {
                    if (transportationMatrix[i][j].status && 
                        (transportationMatrix[i][j].fictitiousA || transportationMatrix[i][j].fictitiousB) && 
                        transportationMatrix[i][j].supply == 0 && 
                        transportationMatrix[i][j].price < minimumPrice)
                    {
                        index.i = i;
                        index.j = j;
                        minimumPrice = transportationMatrix[i][j].price;
                    }
                }
            }
            return index;
        }
    }
    void RefreshStatus()
    {
        for (int j = 0; j < needs.size(); ++j)
        {
            if (needs[j] == 0)
            {
                for (int i = 0; i < transportationMatrix.size(); ++i)
                {
                    if (transportationMatrix[i][j].supply == 0) 
                        transportationMatrix[i][j].status = false;
                }
            }
        }

        for (int i = 0; i < reserves.size(); ++i)
        {
            if (reserves[i] == 0)
            {
                for (int j = 0; j < transportationMatrix[0].size(); ++j)
                {
                    if (transportationMatrix[i][j].supply == 0) 
                        transportationMatrix[i][j].status = false;
                }
            }
        }

    }
    void CreateWay()
    {
        for (int i = 0; i < transportationMatrix.size()-1; ++i)
        {
            for (int j = 0; j < transportationMatrix[0].size()-1; ++j)
            {
                if (transportationMatrix[i][j].status)
                {
                    if (transportationMatrix[i + 1][j + 1].status && !transportationMatrix[i + 1][j + 1].statusWay)
                    {
                        transportationMatrix[i+1][j].status = true;

                        transportationMatrix[i + 1][j + 1].statusWay = true;
                        transportationMatrix[i][j].statusWay = true;
                        transportationMatrix[i+1][j].statusWay = true;
                    }
                }
            }
        }

        for (int i = 1; i < transportationMatrix.size(); ++i)
        {
            for (int j = 1; j < transportationMatrix[0].size()-1; ++j)
            {
                if (transportationMatrix[i][j].status)
                {
                    if (transportationMatrix[i - 1][j + 1].status && !transportationMatrix[i - 1][j + 1].statusWay)
                    {
                        transportationMatrix[i - 1][j].status = true;

                        transportationMatrix[i - 1][j + 1].statusWay = true;
                        transportationMatrix[i][j].statusWay = true;
                        transportationMatrix[i - 1][j].statusWay = true;
                    }
                }
            }
        }


    }
    void AddFictitiousSupplier()
    {
        vector<Transportation> lineMatrix;
        int countCustomer = transportationMatrix[0].size();
        for (int i = 0; i < countCustomer; ++i)
        {
            Transportation elementMatrix;
            elementMatrix.price = 0;
            elementMatrix.fictitiousA = true;
            lineMatrix.push_back(elementMatrix);
        }
        transportationMatrix.push_back(lineMatrix);
        reserves.push_back(abs(diffReservesNeeds));
    }
    void AddFictitiousCustomer()
    {
        vector<Transportation> lineMatrix;
        int countSupplier = transportationMatrix.size();
        for (int i = 0; i < countSupplier; ++i)
        {
            Transportation elementMatrix;
            elementMatrix.price = 0;
            elementMatrix.fictitiousB = true;
            transportationMatrix[i].push_back(elementMatrix);
        }

        needs.push_back(abs(diffReservesNeeds));
    }
    void CalculateCheckSum()
    {
        sumReserves = accumulate(reserves.begin(), reserves.end(), 0);
        sumNeeds = accumulate(needs.begin(), needs.end(), 0);
    }

    int CalculateDifferenceReservesNeeds()
    {
        CalculateCheckSum();
        diffReservesNeeds = sumNeeds - sumReserves;
        return diffReservesNeeds;
    }
    void PrintTask()
    {
        for (int i = 0; i < needs.size() + 2; ++i)
        {
            cout << "_______________";
        }
        cout << "\n";
        cout << "A/B         ";
        for (int i = 0; i < needs.size(); ++i)
        {
            cout << "B" << i + 1 << setw(19);
        }
        cout << "\n";
        for (int i = 0; i < needs.size() + 2; ++i)
        {
            cout << "_______________";
        }
        cout << "\n";
        for (int i = 0; i < transportationMatrix.size(); ++i)
        {
            cout << "A" << i + 1 << "   ";
            for (int j = 0; j < transportationMatrix[0].size(); ++j)
            {
                if (transportationMatrix[i][j].status == true)
                    cout << "|" << setw(11) << transportationMatrix[i][j].price << "(" << setw(3) << transportationMatrix[i][j].supply << ")  ";
                else
                    cout << "|" << setw(18) << "---     ";
            }
            cout << "|";
            cout << reserves[i];
            cout << "\n";
        }
        for (int i = 0; i < needs.size() + 2; ++i)
        {
            cout << "_______________";
        }
        cout << "\n";
        cout << "             ";
        for (int i = 0; i < needs.size(); ++i)
        {
            cout << needs[i];
            cout << setw(19);
        }
        cout << "\n";
        for (int i = 0; i < needs.size() + 2; ++i)
        {
            cout << "_______________";
        }
        cout << "\n";
        cout << "\n\n\n";
    }
    void ReadFileFillTask(string filename = "task.conf")
    {
        std::string line;
        std::ifstream file(filename);
        vector<vector<int>> matrix;
        bool checkLine = false;
        while (getline(file, line))
        {
            vector<int> lineMatrix;
            while (line.size() > 0)
            {
                int endSubstr = line.find(' ');
                int elementMatrix = stoi(line.substr(0, endSubstr));
                lineMatrix.push_back(elementMatrix);
                line.erase(0, endSubstr + 1);
            }
            matrix.push_back(lineMatrix);
        }
        file.close();
        int matrixRow = matrix.size();
        int matrixCol = matrix[0].size();
        for (int i = 0; i < matrixRow - 1; ++i)
        {
            vector<Transportation> lineMatrix;
            for (int j = 0; j < matrixCol - 1; ++j)
            {
                Transportation elementMatrix;
                elementMatrix.price = matrix[i][j];
                lineMatrix.push_back(elementMatrix);
            }
            transportationMatrix.push_back(lineMatrix);
            reserves.push_back(matrix[i][matrixCol - 1]);
        }

        for (int j = 0; j < matrixCol - 1; ++j)
        {
            needs.push_back(matrix[matrixRow - 1][j]);
        }

    }
};