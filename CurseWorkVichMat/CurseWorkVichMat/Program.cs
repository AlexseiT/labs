using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CurseWorkVichMat {
    class Program
    {
        static void Main(string[] args)
        {
            Differential_Equation SDU = new Differential_Equation(0 , 0.8 , 1, 0.691149, 0, 2 , 0.05, 0.00001);
            SDU.Calculate();
        }
    }
}