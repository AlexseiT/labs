using System;
using System.Collections.Generic;
using System.IO;

namespace MathUniver
{
    internal class Program
    {
        static void Main(string[] args)
        {
            ElemFun[] equation = new ElemFun[] { new ElemFun(1, 1, 1), new ElemFun(1, 0, 1) };
            // 1 * x * y + 1 * y
            var termsX = new List<double>();
            double a = 0;
            double b = 1;
            double step = 0.1;

            for (double i = a; i < b; i += step)
            {
                termsX.Add(i);
            }

            double termY = 1;

            double[] answer = DifferentiationDoubleRecalc.RungeKutt(equation, termsX, termY, 0.01);

            PrintArray(answer);
        }
        static public void PrintMatrix<T>(T[,] matrix)
        {
            for (int i = 0; i < matrix.GetLength(0); i++)
            {
                for (int j = 0; j < matrix.GetLength(1); j++)
                {
                    Console.Write(matrix[i, j] + "\t");
                }
                Console.WriteLine();
            }
            Console.WriteLine();
        }
        static public void PrintArray<T>(T[] array)
        {
            for (int i = 0; i < array.Length; i++)
            {
                Console.Write(array[i] + "\t");
            }
            Console.WriteLine();
        }
    }
}