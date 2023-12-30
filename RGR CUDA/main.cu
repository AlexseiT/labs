#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <cmath>
#include <fstream>

#include "GPUComputer.cuh"
int main()
{
    for (int i = 4; i < 11; ++i)
    {
        if (i != 4)
        {
            GPUComputer computer(i,pow(2, i));
            computer.Testing();
        }
      /*  else
        {
            GPUComputer computer(16, true);
            computer.Testing();
        }*/
    }
    return 0;
}