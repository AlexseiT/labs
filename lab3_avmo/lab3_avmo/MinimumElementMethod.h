#pragma once
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric>
#include "TransportTask.h"

using namespace std;

class MinimumElementMethod
{
public:
    TransportTask task;

    MinimumElementMethod()
    {
        task.ReadFileFillTask();
    }
    MinimumElementMethod(string filename)
    {
        task.ReadFileFillTask(filename);
    }
    void SolveTransportTask()
    {
        task.PrintTask();
        if (!task.CheckÑlosed())
        {
            if (task.ÑlosedType())
            {
                task.AddFictitiousSupplier();
            }
            else
            {
                task.AddFictitiousCustomer();
            }
            task.PrintTask();
        }
        int checkCounter = 0;
        while(!task.CheckSolution())
        {
            Index indexMinElement = task.FindMinimumFreePrice();
            int supply;

            if (task.needs[indexMinElement.j] >= task.reserves[indexMinElement.i])
            {
                supply = task.reserves[indexMinElement.i];
            }
            else
            {
                supply = task.needs[indexMinElement.j];
            }

            task.transportationMatrix[indexMinElement.i][indexMinElement.j].supply = supply;
            checkCounter++;
            task.needs[indexMinElement.j] -= supply;
            task.reserves[indexMinElement.i] -= supply;

            task.RefreshStatus();
            task.PrintTask();

        }
        task.CalculateCostTransportation();
        
        if (checkCounter != task.needs.size() + task.reserves.size() - 1)
        {
            task.CreateWay();
            task.PrintTask();
        }
    }
    int GetResult()
    {
        return task.GetZ();
    }
};